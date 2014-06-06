#pragma once

#include "game-core.h"
#include "Game.h"
#include "GameState.h"
#include "AutonomousObjectManager.h"

class GAMECOREDLL ServerGame : public Game {
private:
	float frameTime;
	GameState *gameState;
	AutonomousObjectManager *AI_manager;

protected:
	virtual Engine * makeEngineInstance(ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors);

public:
	ServerGame(float frameTime);

	virtual void init();
	void stop();
};

