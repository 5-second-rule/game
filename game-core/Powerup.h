#pragma once
#include "game-core.h"
#include "StaticObject.h"

#include "engine-core/ICollidable.h"

#include "common/Vector4.h"
#include "common/Matrix4.h"

using namespace Common;

struct PowerupData {
	float position[3];
	float rotation[3];
	int trackIndex;
};

class GAMECOREDLL Powerup : public StaticObject, public ICollidable
{
protected:
	Vector4 position;
	Vector4 rotation;
	int trackIndex;
	float rotationDegrees;

public:
	Powerup(int objectType);
	~Powerup();

	Vector4 getPosition();
	int getTrackIndex();

	void place(int trackIndexAt);

	virtual void update(float dt);

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);

	// ICollidable Methods
	Common::Vector4 getGroupingParameter() const;
	bool collidesWith(const ICollidable*) const;
	virtual void handleCollision(std::shared_ptr<const Bounds>, float dt, int metadata);
	std::shared_ptr<const Bounds> getBounds() const;
	unsigned int getPriority() const;
};

