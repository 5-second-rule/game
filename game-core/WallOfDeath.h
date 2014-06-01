#pragma once

#include "game-core.h"

#include "engine-core/BaseObject.h"

#include "common/Vector4.h"
#include "common/Matrix4.h"
using namespace Common;

struct WallOfDeathData {
	int trackIndex;
};

class GAMECOREDLL WallOfDeath : public BaseObject
{
protected:
	int defaultVelocity;
	int trackIndex;
public:
	WallOfDeath();
	~WallOfDeath();

	int getTrackIndex();

	virtual void update(float dt);
	virtual bool handleEvent(Event* evt);

	void reset();

	std::string toString();

	// ISerializable Methods
	virtual void reserveSize(IReserve&) const;
	virtual void fillBuffer(IFill&) const;

	virtual void deserialize(BufferReader& buffer);
};

