#pragma once
#include "game-core.h"
#include "Game.h"

#include "engine-core/BaseObject.h"
#include "engine-core/ICollidable.h"

#include "common/Vector4.h"

using namespace Common;

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
	Common::Vector4 up;
	Common::Vector4 heading;
	Common::Vector4 position;
	Common::Vector4 force;
	Common::Vector4 tick_force;
	Common::Vector4 velocity;

	float trackVelocity;
	float propulsion;
	float mass;

	bool follow_track;
	int trackIndex;

	float max_speed;
	float max_force;
	float fluid_force;
	float drag_coefficient;
public:
	MovingObject(int objectType, Game* owner);
	~MovingObject();
	Game *owner;
	virtual void init();

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	// Set Methods
	void setMaxSpeed(float);
	void setDragCoeff(float);
	void setMaxForce(float);
	void setTickForce(float x, float y, float z);
	void setForce(float x, float y, float z);
	bool setFlag(std::string, bool value);
	void setPos(float x, float y, float z);
	void setPos(Common::Vector4 v);
	void setFluidForce(float f);

	// Get Methods
	Common::Vector4 getPosition();
	Common::Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	Common::Vector4 getVelocity();
	int getTrackIndex();
	float speed();
	float getMaxSpeed();
	float getMaxForce();
	float getSpeed();
	Vector4 getUp();

	void applyForce(const Vector4& force);

	static float forceByDist(float dist, float maximum);

	// ISerializable Methods
	virtual void deserialize(BufferReader& reader);
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

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
