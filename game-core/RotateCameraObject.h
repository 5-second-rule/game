#pragma once
#include "game-core.h"
#include "Game.h"

#include "engine-core/BaseObject.h"

#include "common/Vector4.h"
#include "common/Matrix4.h"

using namespace Common;

struct RotateCameraObjectData {
	float up[3];
	float heading[3];
	float target[3];
	double rotateAmt;
};

class GAMECOREDLL RotateCameraObject : public BaseObject
{
protected:
	Vector4 up;
	Vector4 heading;
	Vector4 target;
	double rotateAmt;

public:
	RotateCameraObject();
	RotateCameraObject(const Vector4& target, const Vector4& heading, const Vector4& up);
	virtual ~RotateCameraObject();

	const Vector4& getTarget();
	Vector4 getDelta();
	const Vector4& getUp();

	virtual bool handleEvent(Event* evt);
	virtual void update(float dt);

	// ISerializable Methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);
};

