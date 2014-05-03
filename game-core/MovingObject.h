#pragma once

#include "game-core.h"
#include "GameObject.h"
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
	SteeringBehavior* steering_behavior;

public:
	MovingObject();
	~MovingObject();
	Vector4 heading(); // A normalized vector giving the direction the object is heading
	float speed();
	virtual void print();
	virtual void update(float dt);
	virtual bool onEvent(Event event);

};

