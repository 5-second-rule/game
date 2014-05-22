// Server.cpp : Defines the entry point for the console application.
//
#include <csignal>
#include <iostream>

#include "game-core/ServerGame.h"
#include "game-core/CommandLine.h"
#include "engine-core/ConfigSettings.h"

using namespace std;

// function prototypes
void SignalHandler( int signal );

// constants
const float DT = 1.0f / 30.0f; // delta time between loops in sec

//globals
ServerGame *gameInstance;

int main(int argc, char* argv[])
{
	cout << "Initializing Server... Please Wait!\n";
	gameInstance = new ServerGame(DT);
	gameInstance->init();

	CommandLine *cmd = new CommandLine(&cin, &cout);
	getWorld()->allocateHandle(cmd, HandleType::LOCAL);
	getWorld()->insert(cmd);

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