#pragma once

#include "game-core.h"
#include "Game.h"
#include "GameState.h"
#include "AutonomousObjectManager.h"
#include "engine-core\CommandLine.h"

class GAMECOREDLL ServerGame : public Game {
private:
	float frameTime;
	GameState *gameState;
	AutonomousObjectManager *AI_manager;

protected:
	virtual Engine * makeEngineInstance(ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors);

public:
	ServerGame(float frameTime);
	void restart();
	virtual void init();
	void stop();
};

class Restart : public Command
{
private:
	ServerGame* game;
public:
	Restart( ServerGame* game ) : game( game ) {}
	void execute( std::string args );
};
