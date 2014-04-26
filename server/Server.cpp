// Server.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <csignal>

#include "game-core/ServerGameInstance.h"

using namespace std;

// function prototypes
void SignalHandler( int signal );

// constants
const int dt = 3333; // delta time between loops

//globals
ServerGameInstance *gameInstance;

int main(int argc, char* argv[])
{
	cout << "Initializing Server... Please Wait!\n";
	gameInstance = new ServerGameInstance(dt);
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