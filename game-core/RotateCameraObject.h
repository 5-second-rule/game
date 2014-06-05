#pragma once
#include "game-core.h"
#include "Game.h"

#include "engine-core/BaseObject.h"

#include "common/Vector4.h"
#include "common/Matrix4.h"

using namespace Common;

struct RotateCameraObjectData {
	float heading[3];
	float target[3];
	double rotateAmt;
};

class GAMECOREDLL RotateCameraObject : public BaseObject
{
protected:
	const Vector4 up;
	const Vector4 heading;
	const Vector4 target;
	double rotateAmt;

public:
	RotateCameraObject(const Vector4& target, const Vector4& heading, const Vector4& up);
	virtual ~RotateCameraObject();

	const Vector4& getTarget();
	const Vector4& getDelta();
	const Vector4& getUp();

	virtual bool handleEvent(Event* evt);
	virtual void update(float dt);
};

