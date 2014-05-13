#pragma once

#include "..\..\engine\engine-core\BaseObject.h"
#include "..\..\engine\engine-core\World.h"

#include "game-core.h"
#include "RigidBody.h"

class GAMECOREDLL GameObject : public BaseObject
{
protected:
	RigidBody* m_body;

	virtual bool handleEvent(Event *evt);
	void update(float dt);
public:
	GameObject(int objectType);
	~GameObject();
	RigidBody* getBody();
	void setPosition(Vector4 &pos);
	virtual string toString();
};

