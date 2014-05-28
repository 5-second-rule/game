#pragma once

#include "game-core.h"
#include "Game.h"
#include "GameState.h"

class GAMECOREDLL ServerGame : public Game {
private:
	float frameTime;
	GameState *gameState;

protected:
	virtual Engine * makeEngineInstance(ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors);

public:
	ServerGame(float frameTime);
	~ServerGame();

	virtual void init();

	void stop();
};

