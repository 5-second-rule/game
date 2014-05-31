#pragma once
#include "game-core.h"
#include "engine-core/BaseObject.h"
#include "engine-core/IRegisterPlayers.h"
#include "engine-core/Engine.h"
#include "game-core/Game.h"
#include "Player.h"

class GAMECOREDLL GameState : public BaseObject, public IRegisterPlayers
{
public:
	enum State { Load, Title, Selection, Game, Score, None = -1 };

protected:
	static State gameState;
	std::vector<Player*> players;
	bool toonUsed[4];
	Engine *engine;
	World *world;
	ConstructorTable<BaseObject> *objectCtors;

	struct GameStateData {
		int state;
		unsigned int numPlayers;
	};

public:
	GameState();
	~GameState();
	
	bool handleEvent(Event *evt);
	void update(float dt);

	void setState(State state);
	int getState();
	bool isToonUsed(int toon);
	void useToon(int toon);
	void unuseToon(int toon);
	void toggleToonUsed(int toon);

	std::vector<Player*> getPlayers();
	virtual PlayerDelegate* addPlayer(unsigned int playerGuid);
	
	// ISerialize Methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);
};

