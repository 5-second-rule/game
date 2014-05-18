#pragma once
#include "game-core.h"

#include "engine-core/BaseObject.h"

#include "../../common/common/Matrix4.h"
using namespace Common;

struct MovingObjectData {
	float position[3];
	float velocity[3];
	float force[3];
	float friction;
	float mass;
};

class GAMECOREDLL MovingObject : public BaseObject
{
protected:
	Vector4 position;
	Vector4 velocity;
	Vector4 force;
	
	float friction;
	float mass;

	static const float max_speed;
	static const float max_force;

public:
	MovingObject(int objectType);
	~MovingObject();

	Vector4 heading(); // A normalized vector giving the direction the object is heading
	float speed();

	void applyForce(const Vector4& force);

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	void setPos(float x, float y, float z);

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);
};

