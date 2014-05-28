#pragma once

#include <set>
#include <string>

#include "TrackPath.h"
#include "StaticObject.h"

class TubeEntity{
	friend class Tube;
private:
	list<Handle> autonomous_list;
	Handle owner;
	int atual_index;

public:
	TubeEntity(Handle);

	bool operator==(const TubeEntity) const;
	bool operator<(const TubeEntity) const;
	
	std::string toString() const;
};

class GAMECOREDLL Tube : public StaticObject, public ICollidable
{
private:
	std::set<TubeEntity> players;
	TrackPath *path;
public:
	Tube();
	~Tube();

	void update(float dt);

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	void handleCollision(std::shared_ptr<const Bounds>, float dt);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;
};

