#pragma once

#include "..\Common\Messaging\Telegram.h"

#include "..\..\engine\engine-core\BaseObject.h"
#include "..\..\engine\engine-core\World.h"

#include "game-core.h"
#include "RigidBody.h"

class GAMECOREDLL GameObject : public BaseObject
{
protected:
	RigidBody* m_body;
	World* world;

public:
	GameObject();
	~GameObject();
	RigidBody* getBody();
	virtual bool onMessage(Event* evt);
};

