// Server.cpp : Defines the entry point for the console application.
//
#include <chrono>
#include <queue>
#include <iostream>
#include <thread>
#include <csignal>

#include "CommsProcessor.h"

using namespace std::chrono;
using namespace std::this_thread;

// function prototypes
void processUpdates( queue<QueueItem> &updateQ );
void updateWorld( int dt );
void SignalHandler( int signal );

// constants
const int dt = 3333; // delta time between loops
const char *testData = "This is the latest edition of the world from your local neighborhood server\n";

//globals
static bool running = true; //global so signal handler has access

int main(int argc, char* argv[])
{
	cout << "Initializing Server... Please Wait!\n";
	int elapsedCount = 0;
	queue<QueueItem> updateQ;
	CommsProcessor commsProcessor( SERVER );
	commsProcessor.setHandoffQ( &updateQ );
	signal( SIGINT, SignalHandler );
	signal( SIGTERM, SignalHandler );

	cout << "Server Running...\n\n";
	while( running )
	{
		// get start time
		steady_clock::time_point start = steady_clock::now();

		// if there are updates process them
		while( !updateQ.empty() )
			processUpdates(updateQ);

		// update world
		updateWorld( dt );

		// send update of world to clients
		commsProcessor.sendUpdates( testData, strlen( testData ) );

		// once a second send announce message
		if( elapsedCount == 30 )
		{
			elapsedCount = 0;
			commsProcessor.sendAnnouce();
		}

		// get end time
		steady_clock::time_point end = steady_clock::now();

		// sleep for remainder of dt
		sleep_for( microseconds( dt ) - duration_cast<microseconds>(end - start) );
	}

	cout << "Server is Stopping...\n\n";
	return 0;
}

void processUpdates( queue<QueueItem>& updateQ )
{
	static char tmpBuf[65536];
	QueueItem item = updateQ.front();
	memcpy( tmpBuf, item.data, item.len );
	tmpBuf[item.len] = '\0';
	delete [] item.data;
	cout << tmpBuf;
	updateQ.pop();
}

void updateWorld( int dt )
{
	return;
}

void SignalHandler( int signal )
{
	running = false;
}