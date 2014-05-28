// Server.cpp : Defines the entry point for the console application.
//
#include <csignal>
#include <iostream>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "game-core/ServerGame.h"
#include "../engine/engine-core/ConfigSettings.h"

using namespace std;

// function prototypes
void SignalHandler( int signal );

// constants
const float DT = 1.0f / 30.0f; // delta time between loops in sec

//globals
ServerGame *gameInstance;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


	cout << "Initializing Server... Please Wait!\n";
	gameInstance = new ServerGame(DT);
	gameInstance->init();
	signal( SIGINT, SignalHandler );
	signal( SIGTERM, SignalHandler );

	cout << "Server Running...\n\n";

	gameInstance->run();
	
	cout << "Server is Stopping...\n\n";
	delete gameInstance;
	return 0;
}

void SignalHandler( int signal )
{
	gameInstance->stop();
}