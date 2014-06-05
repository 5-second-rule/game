#pragma once
#include "game-core.h"
#include "Game.h"

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
	Vector4 headingVector;
	Vector4 sideLeft;
	Vector4 forceUp;
	Vector4 forceRight;

	Vector4 position;
	Vector4 velocity;
	Vector4 force;
	float trackVelocity;

	float propulsion;

	float friction;
	float mass;
	float max_speed;
	float max_force;
	float fluid_force;
	float heading_force;

	int trackIndex;

	bool followTrack;
	bool hasPropulsion;

public:
	MovingObject(int objectType, Game* owner);
	MovingObject(int objectType, Game* owner, bool follow, bool propulse);
	virtual ~MovingObject();
	virtual void initDefaultConfiguration();
	Game* owner;


	Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	float getSpeed();
	float getMaxForce();
	float getMaxSpeed();
	Vector4 getVelocity();
	Vector4 getPosition();
	int getTrackIndex();
	void setTrackIndex(int position);
	Vector4 getUp();
	Vector4 getSideLeft();
	Vector4 getForceUp();
	Vector4 getForceRight();

	void setPosition(const Vector4& position);
	void setDragCoeff(float);
	void setMaxSpeed(float);
	void setMaxForce(float);
	void setFollowTrack(bool);
	void setHasPropulsion(bool);
	void setFluidForce(float);

	void applyForce(const Vector4& force);

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	virtual std::string toString() const ;

	// ISerializable Methods
	virtual void deserialize(BufferReader& reader);
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	virtual void handleCollision(std::shared_ptr<const Bounds>, float dt, int metadata);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;

	static float forceByDistSq(float dist_sq, float maximum);
};
