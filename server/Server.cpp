// Server.cpp : Defines the entry point for the console application.
//
#include <csignal>
#include <iostream>

#include "game-core/ServerGameInstance.h"
#include "../engine/engine-core/ConfigSettings.h"

using namespace std;

// function prototypes
void SignalHandler( int signal );

// constants
const float DT = 1.0f / 30.0f; // delta time between loops in sec

//globals
ServerGameInstance *gameInstance;

int main(int argc, char* argv[])
{
	cout << "Initializing Server... Please Wait!\n";
	gameInstance = new ServerGameInstance(DT);
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