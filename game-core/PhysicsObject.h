#pragma once

#include "..\Common\Messaging\Telegram.h"

#include "..\..\engine\engine-core\BaseObject.h"
#include "..\..\engine\engine-core\World.h"

#include "game-core.h"
#include "RigidBody.h"

class GAMECOREDLL PhysicsObject : public BaseObject
{
protected:
	RigidBody* m_body;
	World* world;

	float position[3];
	float force[3];


	virtual bool handleEvent(Event *evt);
	void update(float dt);
public:
	PhysicsObject(int objectType);
	~PhysicsObject();
	RigidBody* getBody();

	virtual void reserveSize(IReserve&);
	virtual void fillBuffer(IFill&);

	virtual void deserialize(BufferReader& buffer);
};

