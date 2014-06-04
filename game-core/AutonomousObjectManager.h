#pragma once

#include <string>
#include <list>
#include <vector>

#include "game-core.h"
#include "AutonomousObject.h"
#include "GameState.h"

class GAMECOREDLL AutonomousGroup {
	friend class AutonomousObjectManager;
private:
	std::list< Handle > autonomous_list;
	std::list< Handle > red_blood;
	Handle owner;
	int atual_index;

public:
	AutonomousGroup(Handle);

	bool operator==(const AutonomousGroup&) const;

	std::string toString() const;
};

class GAMECOREDLL AutonomousObjectManager :
	public BaseObject
{
private:
	std::list<AutonomousGroup> players;
	TrackPath *path;
	GameState *gameState;

public:
	AutonomousObjectManager(TrackPath *p_track_path, GameState *p_game_state);
	~AutonomousObjectManager();
	virtual bool handleEvent(Event* evt);
	void setOffsetPursuitDefaultAI(AutonomousObject*);
	void setPursuitDefaultAI(AutonomousObject*);
	void setDefaultRedBlood(MovingObject*);

	void update(float);
};
