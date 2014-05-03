#pragma once

#include "game-core.h"
#include "..\..\engine\engine-core\BaseObject.h"
#include "..\..\engine\engine-core\World.h"
#include "RigidBody.h"

class GAMECOREDLL GameObject
{
protected:
	RigidBody* body;
	World* world;

public:
	GameObject();
	~GameObject();
	RigidBody* getBody();
	Vector4 side();
	Vector4 top();
};

