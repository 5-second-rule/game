#pragma once

#include "..\Common\Messaging\Telegram.h"
#include "..\Common\FSM\StateMachine.h"

#include "game-core.h"
#include "PhysicsObject.h"
#include "MovingObjectStates.h"
#include "SteeringBehavior.h"

class GAMECOREDLL SteeringBehavior;

using namespace Utility;
class GAMECOREDLL MovingObject : public PhysicsObject
{
	friend class SteeringBehavior;
private:
	Vector4 m_velocity;
	Vector4 m_force;
	float m_friction;
	float m_max_speed;
	float m_max_force;
	StateMachine<MovingObject> *state_machine;
	SteeringBehavior* steering_behavior;

public:
	MovingObject(int objectType);
	~MovingObject();
	// Heading(), side() and top() should return a base of the object local space
	Vector4 heading(); // A normalized vector giving the direction the object is heading
	Vector4 front();
	Vector4 side();
	Vector4 top();
	float speed();
	void applyForce(Vector4 force);
	virtual void print();
	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);
};

