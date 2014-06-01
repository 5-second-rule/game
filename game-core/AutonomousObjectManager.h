#pragma once

#include <string>
#include <list>

#include "game-core.h"
#include "AutonomousObject.h"

class GAMECOREDLL AutonomousGroup {
	friend class AutonomousObjectManager;
private:
	list< Handle > autonomous_list;
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
	void setOffset(AutonomousObject*);

	void update(float);
};

