#Makefile for snake 
CC = g++
CFLAGS = -std=c++11 -lncurses
default: snake 
snake:	Snake.cpp Snake.h Source.cpp
	$(CC) $(CFLAGS) -o snake.out Snake.cpp Source.cpp
clean:
	$(RM) snake *.o *~

