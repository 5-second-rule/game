#pragma once

#include "engine-core/BaseObject.h"

#include "game-core.h"
#include "StateMachine.h"
#include "MovingObjectStates.h"
#include "Path.h"
#include "SteeringBehavior.h"
#include "BehaviorType.h"

class GAMECOREDLL SteeringBehavior;

struct MovingObjectData {
	float position[3];
	float velocity[3];
	float force[3];
	float drag_coefficient;
	float mass;
};

class GAMECOREDLL MovingObject :
	public BaseObject,
	public IFollowPath
{
	friend class SteeringBehavior;
	friend class State<MovingObject>;
private:
	Vector4 force;
	Vector4 tick_force;
	Vector4 heading;
	Vector4 top;
	Vector4 side;
	float mass;
	float drag_coefficient;
	float max_speed;
	float max_force;
	StateMachine<MovingObject> *state_machine;
	SteeringBehavior* steering_behavior;
	bool tagged;

protected:
	Vector4 velocity;
	Vector4 position;
public:
	MovingObject(int objectType);
	~MovingObject();
	// Heading(), side() and top() should return a base of the object local space
	Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	Vector4 getFront();
	Vector4 getSide();
	Vector4 getTop();
	float speed();
	void applyForce(Vector4 &force);
	void createAI();
	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	// Set Methods
	void setMaxSpeed(float);
	void setDragCoeff(float);
	void setMaxForce(float);
	void setTickForce(float x, float y, float z);
	void setForce(float x, float y, float z);
	void setTag(bool tag);

	// Get Methods
	Vector4 getPosition();
	bool isTagged();

	// ISerializable Methods
	virtual void deserialize(BufferReader& reader);
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	// Steering Behavior methods
	void setOnSteeringBehavior(BehaviorType);
	void setOffSteeringBehavior(BehaviorType);
	void setPursuit(Handle &pray);
	void setEvade(Handle &predator);

	// Debug
	virtual string toString();
	virtual void print();
};
