//Snake game made in C++ with ncurses
//Copyright 2015 Jordan Ross

#ifdef _WIN32
#include <Windows.h>
#define SLEEP(t) Sleep(t)
#elif __linux__
#include <unistd.h>
#define SLEEP(t) usleep(t*1000)
#endif

class Snake {
public:
	void play(int, bool);
private:
	enum Settings {
		HEIGHT = 20, //Must be at least 6
		WIDTH = 48, //Must be a multiple of 2, greater than 10 (for AI)
		//SPEED = 45, //Actually the length of the pause in ms (lower = faster)
		SNAKE = '#',
		FOOD = '*',
		SPECIAL = '@',

		SPECIAL_ENABLED = true
	};

	int *TailvaluesR;
	int *TailvaluesC;

	int SPEED;
	bool AI;

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

