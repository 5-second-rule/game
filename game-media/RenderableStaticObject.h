#pragma once
#include "game-core\StaticObject.h"
#include "engine-renderer\RenderableObject.h"
#include "RenderableGame.h"

class RenderableStaticObject :
	public StaticObject, public RenderableObject
{
public:
	RenderableStaticObject(int type, Transmission::Model* m);
	virtual ~RenderableStaticObject();
};

