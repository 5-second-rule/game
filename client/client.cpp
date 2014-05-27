#include <windows.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#include "game-media/RenderableGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	RenderableGame *game = new RenderableGame(hInstance);
	game->init();
	game->run();
	delete game;
}

