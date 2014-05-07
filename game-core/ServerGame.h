#pragma once

#include "game-core.h"
#include "Game.h"

class GAMECOREDLL ServerGame : public Game
{
private:
	float frameTime;

protected:
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	ServerGame(float frameTime);
	~ServerGame();

	void stop();

	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, const char* data );
};

