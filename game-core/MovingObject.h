#pragma once

#include "../../common/common/4D/Matrix4.h"

#include "game-core.h"
#include "GameObject.h"
#include "StateMachine.h"
#include "MovingObjectStates.h"
#include "SteeringBehavior.h"

class GAMECOREDLL SteeringBehavior;

using namespace Common;
class GAMECOREDLL MovingObject : public GameObject
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

