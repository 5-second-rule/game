#pragma once
#include "game-core.h"

#include "engine-core\BaseObject.h"
#include "engine-core\ICollidable.h"

class GAMECOREDLL StaticObject : public BaseObject, public ICollidable {
public:
	StaticObject(int objectType);
	~StaticObject();

	virtual bool handleEvent(Event* evt);

	Common::Vector4* getGroupingParameter();
	bool collidesWith(ICollidable* target);
	void handleCollision(BoundingSphere bs, float dt);
	BoundingSphere getBounds();
	unsigned int getPriority();
};

