#pragma once

#include "..\Common\Messaging\Telegram.h"
#include "..\Common\FSM\StateMachine.h"

#include "game-core.h"
#include "GameObject.h"
#include "MovingObjectStates.h"
#include "SteeringBehavior.h"

class GAMECOREDLL SteeringBehavior;

using namespace Utility;
class GAMECOREDLL MovingObject : public GameObject
{
	friend class SteeringBehavior;
private:
	Vector4 m_velocity;
	Vector4 m_force;
	float m_friction;
	float m_max_speed;
	float m_max_force;
	StateMachine<MovingObject> *stateMachine;
	SteeringBehavior* steering_behavior;

public:
	MovingObject();
	~MovingObject();
	// Heading(), side() and top() should return a base of the object local space
	Vector4 heading(); // A normalized vector giving the direction the object is heading
	Vector4 side();
	Vector4 top();
	float speed();
	void applyForce(Vector4 force);
	virtual void print();
	virtual void update(float dt);
	virtual bool onMessage(Event* evt);

};

