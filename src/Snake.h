//Snake game made in C++ with ncurses
//Copyright 2015 Jordan Ross

#ifdef _WIN32
#include <Windows.h>
#define SLEEP(t) Sleep(t)
#elif __linux__
#include <unistd.h>
#define SLEEP(t) usleep(t*1000)
#endif

enum AI_status {off, slow, fast};

class Snake {
    public:
        void play(int, AI_status);
    private:
        enum Settings {
            HEIGHT = 20, //Must be at least 6
            WIDTH = 48, //Must be a multiple of 2, greater than 10 (for AI)
            SNAKE = '#',
            FOOD = '*',
            SPECIAL = '@',

            SPECIAL_ENABLED = true
        };


        int *TailvaluesR;
        int *TailvaluesC;

        int SPEED;
        AI_status AI;

        bool playing;
        int length;
        int direction;

        int specialpos[2];
        bool specialexists;
        int specialbonus;
        int score;

        void initValues();
        void initMap();
        bool move();
        void makeItem(char);
        int playerInput();
        int aiInput();
};

