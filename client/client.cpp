#include <windows.h>

#include "game-media/RenderableGameInstance.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	RenderableGameInstance *game = new RenderableGameInstance(hInstance);
	game->init();
	game->run();
	delete game;
}

