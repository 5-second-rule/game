#pragma once


#include "game-core.h"
#include "GameObject.h"
#include "StateMachine.h"
#include "MovingObjectStates.h"
#include "Path.h"
#include "SteeringBehavior.h"
#include "BehaviorType.h"

class GAMECOREDLL SteeringBehavior;

using namespace Common;
class GAMECOREDLL MovingObject :
	public GameObject,
	public IFollowPath
{
	friend class SteeringBehavior;
private:
	Vector4 m_velocity;
	Vector4 m_force;
	Vector4 m_tick_force;
	float m_drag_coefficient;
	float m_max_speed;
	float m_max_force;
	StateMachine<MovingObject> *m_state_machine;
	SteeringBehavior* m_steering_behavior;
	Path* m_path;
	WayPoint m_current_way_point;

public:
	MovingObject(int objectType);
	~MovingObject();
	// Heading(), side() and top() should return a base of the object local space
	Vector4 heading(); // A normalized vector giving the direction the object is heading
	Vector4 front();
	Vector4 side();
	Vector4 top();
	float speed();
	void applyForce(Vector4 &force);
	void createAI();
	virtual string toString();
	virtual void print();
	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);
	void setMaxSpeed(float);
	void setDragCoeff(float);
	void setMaxForce(float);

	/* Steering Behavior methods */
	void setOnSteeringBehavior(BehaviorType);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle *pray);
	void setEvade(Handle *predator);

	/* Path follow methods */
	WayPoint getCurrentWayPoint();
	void setCurrentWayPoint(WayPoint);
	void setNextWayPoint();
};