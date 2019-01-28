#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Windows.h>

const int LEVEL_HEIGHT = 31;
const int LEVEL_WIDTH = 28;
const char NO_COLLISION_TILES[3] = { ' ','o','\xfa' };
const int GATE_X = 13;
const int GATE_Y = 12;

const char ALL_DIRS[4] = { 'w','a','s','d' };
const char ICONS[4] = { 'v','>','^','<' };
const char GHOST_ICON = 'M';
const char DEAD_GHOST_ICON = '"';

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

const int SUPER_MAX = 500;
const int ONE_UP_MAX = 13;
const int PELLET_MAX = 8;
const int PACMAN_MAX = 8;
const int GHOST_MAX = 10;
const int RUN_MAX = 16;
const int DEAD_MAX = 3;
const int MODE_MAX = 1000;

const int BLINKY = 0;
const int PINKY = 1;
const int INKY = 2;
const int CLYDE = 3;

#endif
