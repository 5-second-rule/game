#pragma once
#include "game-core.h"

#include "engine-core/BaseObject.h"
#include "engine-core/ICollidable.h"


#include "common/Vector4.h"
#include "common/Matrix4.h"
using namespace Common;

struct MovingObjectData {
	float position[3];
	float velocity[3];
	float force[3];
	float friction;
	float mass;
	float trackNormal[3];
	int trackIndex;
};

class GAMECOREDLL MovingObject : public BaseObject, public ICollidable
{
protected:
	Vector4 position;
	Vector4 velocity;
	Vector4 force;
	Vector4 trackNormal;
	float trackVelocity;
	
	float friction;
	float mass;

	static const float max_speed;
	static const float max_force;

	int trackIndex;
	bool followTrack;

public:
	MovingObject(int objectType);
	~MovingObject();

	Vector4 heading(); // A normalized vector giving the direction the object is heading
	float speed();
	Vector4 getPosition();
	Vector4 getTrackNormal();
	int getTrackIndex();

	void applyForce(const Vector4& force);

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);

	// ICollidable Methods
	Vector4* getGroupingParameter();
	bool collidesWith(ICollidable* target);
	void handleCollision(BoundingSphere bs, float dt);
	BoundingSphere getBounds();
	unsigned int getPriority();

};

