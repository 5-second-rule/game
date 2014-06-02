#pragma once

#include "game-core.h"
#include "MovingObject.h"

class GAMECOREDLL PlayerMovingObject : public MovingObject
{
public:
	PlayerMovingObject(int objectType, Game* owner);
	~PlayerMovingObject();

	virtual void update(float dt);

	virtual void handleCollision(std::shared_ptr<const Bounds>, float dt, int metadata);

	virtual int getCollisionMetadata() const;
};
