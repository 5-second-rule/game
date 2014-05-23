#pragma once

#include <thread>
#include <mutex>

#include "game-core.h"
#include "Game.h"
#include "CommandLine.h"

class GAMECOREDLL ServerGame : public Game
{
private:
	float frameTime;
	Handle *cmd;
protected:
	virtual Engine * makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors );

public:
	std::mutex cmd_mtx;

	ServerGame(float frameTime);
	~ServerGame();

	virtual void init();

	void stop();
	void update();
	void handleCmd();
};

