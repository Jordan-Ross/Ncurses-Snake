//Snake game made in C++ with ncurses
//Copyright 2015 Jordan Ross
#include <iostream>
#include <string>
#include <string.h>
#include "Snake.h"

std::string help = 
"\nSnake game in ncurses \n\
    -h  help (display this screen) \n\
    -s	speed (1-9, default 6) \n\
    -a	use fast AI \n\
    -A	use perfect AI (slow) \n\
    -r	prompt for restart \n";

AI_status useAI = off;
bool repeat = true;
int speed = 40;

void parseArgs(int argc, const char** argv) {
    for (int arg = 1; arg < argc; arg++) {
        if (!strcmp(argv[arg], "-h")) {
	    std::cout << help;
	    //TODO: exit here
	}
	else if (!strcmp(argv[arg], "-s")) {
	    speed = std::stoi(argv[++arg]);
	    speed = 100 - speed * 10;
	}		
	else if (!strcmp(argv[arg], "-a")) {
	    useAI = fast;
	}
	else if (!strcmp(argv[arg], "-A")) {
	    useAI = slow;
	}
	else if (!strcmp(argv[arg], "-r")) {
	    repeat = false;;
        }
    }
}

int main(int argc, const char** argv) {
    Snake snake;

    parseArgs(argc, argv);

    while (1) {
        snake.play(speed, useAI);
    }
}

