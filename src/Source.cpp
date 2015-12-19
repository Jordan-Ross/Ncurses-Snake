//Snake game made in C++ with ncurses
//Copyright 2015 Jordan Ross
#include <iostream>
#include <string>
#include "Snake.h"

int main() {
	Snake snake;

	std::string num;
	int speed;
	char choice;

	bool AI;
	std::cout << "Use AI? (y/n)";
	choice = std::cin.get();
	if (choice == 'y' || choice == 'Y')
		AI = true;
	else AI = false;

	speed = 40;
	while (1) {
		std::cin.sync();
		std::cout << "============================================================\n";
		std::cout << "Enter a speed (1-9, default: " << (100 - speed) / 10 << "): ";
		num = std::cin.get();
		if (num[0] == '\n' || isalpha(num[0])) snake.play(speed, AI);
		else {
			speed = 100 - std::stoi(num) * 10;
			snake.play(speed, AI);
		}
		std::cin.sync();
		printf("Play again? (y/n): ");
		choice = std::cin.get();
		if (choice == 'y' || choice == 'Y' || choice == '\n')  {
			continue;
		}
		else return 0;
	}
}

