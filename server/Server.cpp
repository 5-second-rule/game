// Server.cpp : Defines the entry point for the console application.
//
#include <csignal>
#include <iostream>
#include "game-core/ServerGame.h"
#include "../engine/engine-core/ConfigSettings.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



using namespace std;

// function prototypes
void SignalHandler( int signal );

// constants
const float DT = 1.0f / 30.0f; // delta time between loops in sec

//globals
ServerGame *gameInstance;

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

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