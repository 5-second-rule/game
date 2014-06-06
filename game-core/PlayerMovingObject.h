#pragma once

#include "game-core.h"
#include "MovingObject.h"

struct PlayerMovingObjectData {
	bool dead;
};

class GAMECOREDLL PlayerMovingObject : public MovingObject
{
public:
	bool dead;

	PlayerMovingObject(int objectType, Game* owner);
	~PlayerMovingObject();

	virtual void update(float dt);

	virtual void handleCollision(std::shared_ptr<const Bounds>, float dt, int metadata);

	virtual int getCollisionMetadata() const;

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);
};

