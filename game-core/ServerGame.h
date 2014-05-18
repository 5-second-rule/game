#pragma once

#include <thread>
#include <mutex>

#include "game-core.h"
#include "Game.h"
#include "GameWorld.h"
#include "CommandLine.h"

class GAMECOREDLL CommandLine;
class GAMECOREDLL GameWorld;

class GAMECOREDLL ServerGame : public Game
{
private:
	float frameTime;
	CommandLine *cmd;
	std::stringstream cmd_buffer;
protected:
	virtual Engine * makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors );

public:
	std::mutex cmd_mtx;

	ServerGame(float frameTime);
	~ServerGame();

	void run();
	void stop();
	void update();
	void handleCmd();
};

