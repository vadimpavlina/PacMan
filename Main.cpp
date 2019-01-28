#include "Game.h"

void main()
{
	system("mode con cols=150 lines=41");
	Game* game = new Game();
	game->Go();
	delete game;
}
