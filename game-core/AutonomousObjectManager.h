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

public:
	AutonomousObjectManager();
	~AutonomousObjectManager();
	virtual bool handleEvent(Event* evt);
	void setOffsetDefaultAI(AutonomousObject*);
	void setPursuitDefaultAI(AutonomousObject*);

	void update(float);

	void setTrack(TrackPath*);
};

