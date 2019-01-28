#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

#include <mmsystem.h>

#include "Constants.h"

#include "Game.h"
#include "Pacman.h"
#include "SetConsoleAttributes.h"
#pragma comment(lib, "winmm.lib")

using namespace std;

Pacman::Pacman(Game *const g)
	: game(g) {
	hiScore = 0;
}

void Pacman::Move() {
	if (wait) {
		--wait;
	}
	else {
		GetDirection();
		if (TestForCollision() == false) {


			SetCursorPosition(yOld, xOld);
			cout << game->GetLevel(yOld, xOld);
			if (game->GetLevel(y, x) != ' ')
			{
				int scoreInc;
				if (game->GetLevel(y, x) == 'o')
				{
					PlaySound(TEXT("pacman_eatfruit"), NULL, SND_FILENAME | SND_ASYNC);
					scoreInc = 50;
					super = SUPER_MAX;
				}
				else
				{
					scoreInc = 10;
				}
				PrintScore(scoreInc);
				game->SetLevel(y, x, ' ');
				--left;
			}
			Show();
			dirOld = dir;
			wait = PACMAN_MAX;
		}
	}
}

void Pacman::GetDirection() {
	dir = 'x';

	if (_kbhit()) {

		dir = tolower(_getch());
	}
	if (!strchr(ALL_DIRS, dir))
	{


		dir = dirOld;
	}
}

bool Pacman::TestForCollision() {
	xOld = x;
	yOld = y;
	switch (dir) {
	case 'a':
		if (x == 0) {
			x = LEVEL_WIDTH - 1;
			icon = ICONS[1];
		}
		else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x - 1)))
		{
			--x;
			icon = ICONS[1];
		}
		break;
	case 'd':
		if (x == LEVEL_WIDTH - 1) {
			x = 0;
			icon = ICONS[3];
		}
		else if (strchr(NO_COLLISION_TILES, game->GetLevel(y, x + 1)))
		{
			++x;
			icon = ICONS[3];
		}
		break;
	case 'w':
		if (strchr(NO_COLLISION_TILES, game->GetLevel(y - 1, x)))
		{
			--y;
			icon = ICONS[0];
		}
		break;
	case 's':
		if (strchr(NO_COLLISION_TILES, game->GetLevel(y + 1, x)))
		{
			++y;
			icon = ICONS[2];
		}
	}
	if (x == xOld && y == yOld) {
		return true;
	}
	return false;
}

void Pacman::PrintScore(int scoreInc) {
	if (score / 10000 < (score + scoreInc) / 10000) {
		++lives;
		PrintLives();
	}
	score += scoreInc;
	SetTextColor(White);
	SetCursorPosition(-2, 0);
	if (score == 0) {
		cout << setw(7) << "00";
	}
	else {
		cout << setw(7) << score;
	}
	if (score > hiScore) {
		hiScore = score;
		cout << setw(11) << hiScore;
	}
}

void Pacman::PrintLives() {
	SetTextColor(color);
	SetCursorPosition(LEVEL_HEIGHT, 2);
	for (int i = 1; i < lives; ++i) {
		SetTextColor(Brown);
		cout << ICONS[1] << " ";
	}
	cout << " ";
}

void Pacman::PrintKillScore() {
	++killCount;
	int scoreInc = 200 * (int)pow(2, killCount - 1);
	int length = (int)floor(log10(scoreInc)) + 1;
	int killX = x - 1;
	if (x == 0) {
		killX = x;
	}
	if (x > LEVEL_WIDTH - length) {
		killX = LEVEL_WIDTH - length;
	}
	SetTextColor(White);
	SetCursorPosition(y, killX);
	cout << scoreInc;
	PrintScore(scoreInc);
	Sleep(750);
	SetCursorPosition(y, killX);
	for (int i = killX; i < killX + length; ++i) {
		SetTextColor(Blue);
		if (game->GetLevel(y, i) == char(250)) {
			SetTextColor(White);
		}
		if (game->GetLevel(y, i) == 'o') {
			SetTextColor(game->GetPelletColor());
		}
		cout << game->GetLevel(y, i);
	}
	Show();
}

void Pacman::Dead() {
	Sleep(1000);
	game->HideAll();
	for (int i = 0; i < 8; ++i) {
		icon = ICONS[i % 4];
		Show();
		Sleep(100);
	}
	Hide();
	Sleep(500);
	--lives;
	if (lives != 0) {
		PlaySound(TEXT("pacman_extrapac"), NULL, SND_FILENAME | SND_ASYNC);
		game->InitAll();
		game->ShowAll();
		PrintLives();
		game->PrintReady();
	}
	else {
		PlaySound(TEXT("pacman_death"), NULL, SND_FILENAME | SND_ASYNC);
		game->PrintGameOver();

	}
}

void Pacman::Show() {
	SetTextColor(Brown);
	SetCursorPosition(y, x);
	cout << icon;
}

void Pacman::Hide() {
	SetCursorPosition(y, x);
	cout << game->GetLevel(y, x);
}
