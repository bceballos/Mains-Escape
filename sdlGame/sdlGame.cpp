#include <iostream>
#include "SDL.h"
#include "hGameEngine.h"
#include "hLog.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	Game game = Game();

	if (game.init()) {
		while (game.gameRunning) {
			game.state = Game::GameState::MENU;
			game.runMenu();
			srand(time(0));
			game.run();
			game.state = Game::GameState::SCORE;
			game.endScoreScreen();
		}
	}

	game.clean();
	
	return 0;
}
