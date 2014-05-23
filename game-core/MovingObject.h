#pragma once
#include "game-core.h"

#include "engine-core/BaseObject.h"
#include "engine-core/ICollidable.h"


#include "common/Vector4.h"
#include "common/Matrix4.h"
using namespace Common;

struct MovingObjectData {
	float up[3];
	float heading[3];

	float position[3];
	float velocity[3];
	float force[3];

	float friction;
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
	
	float friction;
	float mass;

	static const float max_speed;
	static const float max_force;

	int trackIndex;
	bool followTrack;

public:
	MovingObject(int objectType);
	~MovingObject();

	Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	float speed();
	Vector4 getPosition();
	int getTrackIndex();

	void applyForce(const Vector4& force);

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	void handleCollision(std::shared_ptr<const Bounds>, float dt);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;

};

