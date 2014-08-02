#pragma once
#include "game-core.h"
#include "engine-core/BaseObject.h"
#include "engine-core/IRegisterPlayers.h"
#include "engine-core/Engine.h"
#include "game-core/Game.h"
#include "Player.h"
#include "Leaderboard.h"
#include "Deathboard.h"

#define MAX_LIVES 5

class GAMECOREDLL GameState : public BaseObject, public IRegisterPlayers
{
public:
	enum State { Load, Title, Selection, Countdown, Game, Score, None = -1 };

protected:
	bool countdownSound;
	float counter;
	int countdownFlag;

	static State gameState;
	std::vector<Player*> players;
	std::vector<LeaderboardEntry> leaderboard;
	std::vector<DeathboardEntry> deathboard;
	bool toonUsed[4];
	BaseObject * selScreen;
	Engine *engine;
	World *world;
	::Game *game;
	ConstructorTable<BaseObject> *objectCtors;

	struct GameStateData {
		int state;
		unsigned int numPlayers;
		int countdownFlag;
	};

public:
	GameState( ::Game* game );
	~GameState();
	
	bool handleEvent(Event *evt);
	void update(float dt);

	void setState(State state);
	int getState();
	std::vector<Handle> getPlayersHandle();
	bool isToonUsed(int toon);
	void useToon(int toon);
	void unuseToon(int toon);
	void toggleToonUsed(int toon);

	std::string toString() const;

	std::vector<Player*> getPlayers();
	virtual PlayerDelegate* addPlayer(unsigned int playerGuid);
	int getCountdownFlag();

	std::vector<LeaderboardEntry> getLeaderboard();
	std::vector<DeathboardEntry> getDeathboard();
	void sortDeathboard();
	void placeInDeathOrder(int i);
	bool destroySelectionScreen();
	
	// ISerialize Methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);
};

