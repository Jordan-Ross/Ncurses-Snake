//Snake game made in C++ with ncurses
//Copyright 2015 Jordan Ross
#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include "Snake.h"

void Snake::initValues() {
    TailvaluesR = new int[HEIGHT * WIDTH + 1];
    TailvaluesC = new int[HEIGHT * WIDTH + 1];
    playing = true;
    specialexists = false;
    specialbonus = 0;
    score = 0;
    length = 3;
    direction = 4;
}

void Snake::play(int Speed, AI_status ai) {
    AI = ai;
    SPEED = Speed;
    initValues();
    srand(time(NULL)); //Seed rng

    initscr(); //Curses makescreen
    initMap(); //Init map function with curses
    curs_set(0); //Makes cursor invisible
    noecho();  //Doesn't echo the char
    cbreak();  //Turn off line buffering
    nodelay(stdscr, 1);  //Don't wait before returning 

    TailvaluesR[2] = HEIGHT / 2;
    TailvaluesC[2] = WIDTH / 2;

    makeItem(FOOD);

    while (playing) {
        playing = move();
        score = ((length - 3) * 1000) + (specialbonus * 5000);
        mvprintw(HEIGHT, 0, "WASD to move | Score: %i", score);
        refresh(); //Curses refresh
    }
    endwin(); //Curses end
    printf("Final Score: %i\n", score);
    if (SPECIAL_ENABLED) printf("Special Count: %i\n", specialbonus);
    delete TailvaluesC;
    delete TailvaluesR;
}

bool Snake::move() {
    static int delay = 3;  //this delays if needed (beginning, after getting food)

    if (direction == 1 || direction == 3) SLEEP(SPEED * 1.7); //Sleep more going up/down
    else SLEEP(SPEED);

    if (AI == slow || AI == fast) direction = aiInput();
    else direction = playerInput();

    if (delay == 0) { //Removes the last element
        mvaddch(TailvaluesR[0], TailvaluesC[0], ' ');
    }
    else delay--;

    for (int k = 0; k < length-1; k++) {  //Shifts all elements in Tail down (last clear) 
        TailvaluesR[k] = TailvaluesR[k+1]; //row
        TailvaluesC[k] = TailvaluesC[k+1]; //col
    }

    switch (direction) { //Move head in direction
        case 10:
            return false; //Stop playing
        case 1:
            (TailvaluesR[length - 1])--; //HeadRow--
            break;
        case 2:
            (TailvaluesC[length - 1])--; //HeadCol--
            break;
        case 3:
            (TailvaluesR[length - 1])++; //HeadRow++
            break;
        case 4:        
            (TailvaluesC[length - 1])++; //HeadCol++
            break;
    } 

    switch (mvinch(TailvaluesR[length - 1], TailvaluesC[length - 1])) {
        case '-':
        case '|': //Game is lost (Wall)  
        case SNAKE: //Game is lost (Self)
            return false;
        case FOOD: //Food was got
            length = length + 1;
            for (int k = length-1; k > 1; k--) {
                TailvaluesR[k] = TailvaluesR[k-1];
                TailvaluesC[k] = TailvaluesC[k-1];
            }
            makeItem(FOOD);
            if (specialexists) { //Remove special when food is got
                mvaddch(specialpos[0], specialpos[1], ' '); 
                specialexists = false;
            }
            if ((rand() % 30 == 1) && (SPECIAL_ENABLED)) { //1 in 30 chance for special item when adding food
                makeItem(SPECIAL); 
                specialexists = true;
            }
            break;
        case SPECIAL: //Special was got
            (specialbonus)++;
            break;
        case ' ':
            break;
    }
    mvaddch(TailvaluesR[length - 1], TailvaluesC[length - 1], SNAKE); //add the new head
    return true;
}

void Snake::makeItem(char item) {
    int r = 0;
    int c = 0;
    while (mvinch(r,c) != ' ' || (r == TailvaluesR[length-1] && c == TailvaluesC[length-1])) { 
        //Often the head hasn't been placed yet, so make sure the food isn't going where the new head will be.
        r = rand() % (HEIGHT-2) + 1;
        c = rand() % (WIDTH-2) + 1;
    }
    mvaddch(r, c, item); //Add item at random location
    if (item == SPECIAL) { //Set position of special 
        specialpos[0] = r;
        specialpos[1] = c;
    }
}

int Snake::playerInput() { //wasd = nwse = 1234
    char i; 
    int newdirection; 
    //fseek(stdin,0,SEEK_END); //Attempts to flush output
    //fflush(stdin); //Doesn't work on curses
    i = getch(); //Curses get char
    flushinp();
    switch(i) {
        case 'w':
            newdirection = 1;
            break;
        case 'a':
            newdirection = 2;
            break;
        case 's':
            newdirection = 3;
            break;
        case 'd':
            newdirection = 4;
            break;
        case 'q': //quit
            newdirection = 10;
            break;
        default:
            newdirection = direction;
            break;
    }
    if (abs(newdirection - direction) != 2) return newdirection;
    else return direction;
}

void Snake::initMap() {
    int r, c;
    char ch;
    for (r = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++) {
            if ((r == 0 && c == 0) || (r == 0 && c == WIDTH - 1)
                    || (r == HEIGHT - 1 && c == 0) || (r == HEIGHT - 1 && c == WIDTH - 1))
                ch = '+';
            else if (r == 0 || r == HEIGHT - 1)
                ch = '-';
            else if (c == 0 || c == WIDTH - 1)
                ch = '|';
            else 
                ch = ' ';
            mvaddch(r,c,ch);
        }
    }
}

//Optimal AI (Slower, but always eats all food)
int Snake::aiInput() { 
    int Rtemp = TailvaluesR[length - 1];
    int Ctemp = TailvaluesC[length - 1];

    static int newdir = 3;
    static int next = 0;

    if (next > 0) {
        newdir = next;
        next = 0;
    }
    else if (Rtemp == 1) { //Very top
        newdir = 4; //Hits top, go right
        next = 3; //Next go down
    }
    else if (Ctemp == 1) {
        newdir = 1;
    }
    else if (Rtemp == HEIGHT - 2) { //At the very bottom
        newdir = 2; //All the way left
    }
    else if (Ctemp == WIDTH-2) { //At the very right
        newdir = 3; //All the way down at the end
    }
    else if (Rtemp == HEIGHT-3) { //One above the bottom space
        newdir = 4; //Hits bottom, go right 
        next = 1; //Next go up
    }

    return newdir;
}

