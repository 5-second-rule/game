#include <windows.h>

#include "game-media/RenderableGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	RenderableGame *game = new RenderableGame(hInstance);
	game->init();
	game->run();
	delete game;
}

