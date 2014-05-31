#pragma once

#include "game-core.h"
#include "Game.h"

class GAMECOREDLL ServerGame : public Game
{
private:
	float frameTime;

protected:
	virtual Engine * makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors );

public:
	ServerGame(float frameTime);
	~ServerGame();

	virtual void init();

	void initPowerups();

	void stop();
};

