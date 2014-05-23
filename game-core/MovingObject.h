#pragma once

#include "engine-core/BaseObject.h"
#include "engine-core/ICollidable.h"

#include "game-core.h"
#include "StateMachine.h"
#include "MovingObjectStates.h"
#include "Path.h"
#include "BehaviorType.h"

struct MovingObjectData {
	float up[3];
	float heading[3];

	float position[3];
	float velocity[3];
	float force[3];
	float drag_coefficient;
	float mass;

	int trackIndex;
};

class GAMECOREDLL MovingObject : public BaseObject, public ICollidable
{
protected:
	Vector4 up;
	Vector4 heading;

	Vector4 position;
	Vector4 velocity;
	Vector4 force;
	float trackVelocity;
	
	float mass;
	float drag_coefficient;
	StateMachine<MovingObject> *state_machine;
	bool tagged;

protected:
	Common::Vector4 tick_force;
	Common::Vector4 velocity;
	Common::Vector4 position;
	float max_speed;
	float max_force;

	int trackIndex;
	bool followTrack;

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
	Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	float speed();
	Vector4 getPosition();
	int getTrackIndex();

	// Get Methods
	Common::Vector4 getPosition();
	Common::Vector4 getVelocity();
	float getMaxSpeed();
	float getMaxForce();
	bool isTagged();

	void setPos(float x, float y, float z);

	// ISerializable Methods
	virtual void deserialize(BufferReader& reader);
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	void handleCollision(std::shared_ptr<const Bounds>, float dt);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;

	// Debug
	virtual std::string toString();
	virtual void print();
};
