#pragma once

#include "engine-core/World.h"

#include "game-core.h"
#include "ServerGame.h"

class GAMECOREDLL ServerGame;

class GAMECOREDLL GameWorld : public World
{
private:
	ServerGame *server;
protected:

public:
	GameWorld(ServerGame*);
	~GameWorld();

	virtual void update( float dt );
};

