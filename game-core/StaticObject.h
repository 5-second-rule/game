#pragma once
#include "game-core.h"

#include "engine-core\BaseObject.h"
#include "engine-core\ICollidable.h"

class GAMECOREDLL StaticObject : public BaseObject {
public:
	StaticObject(int objectType);
	virtual ~StaticObject();
	virtual std::string toString();

	virtual bool handleEvent(Event* evt);

};

