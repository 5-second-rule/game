#pragma once
#include "engine-core/BaseObject.h"
#include "engine-core/IRegisterPlayers.h"
#include "engine-renderer/RenderingEngine.h"
#include "game-media/RenderableGame.h"
#include "Player.h"

class GAMECOREDLL GameState : public BaseObject, public IRegisterPlayers
{
public:
	enum State { Load, Title, Selection, Game, Score, None = -1 };

protected:
	static State gameState;
	std::vector<Player *> players;
	bool unusedChars[4];
	RenderingEngine *engine;
	World *world;
	ConstructorTable<BaseObject> *objectCtors;

public:
	GameState();
	~GameState();
	void setState(int state);
	void setState(State state);
	State getState();
	virtual BaseObject * addPlayer(unsigned int playerGuid);
	virtual bool handleEvent(Event *evt);
};

