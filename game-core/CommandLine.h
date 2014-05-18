#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

#include "game-core.h"
#include "MovingObject.h"
#include "ServerGame.h"

class GAMECOREDLL ServerGame;

class GAMECOREDLL CommandLine
{
private:
	ServerGame *owner;
	thread *input_thread;

public:
	CommandLine(ServerGame *owner, std::mutex *cmd_mtx, std::stringstream *cmd_buffer);
	~CommandLine();

	static void cmdLoop(std::mutex *cmd_mtx, std::stringstream *cmd_buffer);
	void handleCmd(std::string cmd);
	void help();
	void setHelp();
	void printHelp();
	void invalidCommand();
	void set(std::stringstream &buffer);
	void print(std::stringstream &buffer);
	MovingObject *findObjectById(int);

};


