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
	friend class State<MovingObject>;
private:
	Common::Vector4 force;
	Common::Vector4 tick_force;
	Common::Vector4 heading;
	Common::Vector4 top;
	Common::Vector4 side;
	float mass;
	float drag_coefficient;
	StateMachine<MovingObject> *state_machine;
	bool tagged;

protected:
	Common::Vector4 velocity;
	Common::Vector4 position;
	float max_speed;
	float max_force;
public:
	MovingObject(int objectType);
	~MovingObject();
	// Heading(), side() and top() should return a base of the object local space
	Common::Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	Common::Vector4 getFront();
	Common::Vector4 getSide();
	Common::Vector4 getTop();
	float speed();
	void applyForce(Common::Vector4 &force);
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
	Common::Vector4 getPosition();
	Common::Vector4 getVelocity();
	float getMaxSpeed();
	float getMaxForce();
	bool isTagged();

	// ISerializable Methods
	virtual void deserialize(BufferReader& reader);
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	// Debug
	virtual std::string toString();
	virtual void print();
};
