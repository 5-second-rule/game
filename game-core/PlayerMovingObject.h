#pragma once

#include "game-core.h"
#include "MovingObject.h"

struct PlayerMovingObjectData {
	bool dead;
	int boostCount;
	bool underTwentyFive;
	int releaseCount;
};

class GAMECOREDLL PlayerMovingObject : public MovingObject
{
protected:
	void checkBoost();
public:
	bool dead;
	
	int boostCount;
	bool underTwentyFive;
	int releaseCount;

	PlayerMovingObject(int objectType, Game* owner);
	virtual ~PlayerMovingObject();

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	virtual void handleCollision(std::shared_ptr<const Bounds>, float dt, int metadata);

	virtual int getCollisionMetadata() const;
	int getBoostCount();

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);
};

