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

	float position[3];
};

class GAMECOREDLL RotateCameraObject : public BaseObject
{
protected:
	Vector4 up;
	Vector4 heading;
	Vector4 sideLeft;

	Vector4 cameraChangeVec;
	double rotateAmt;

	Vector4 position;

public:
	RotateCameraObject();
	virtual ~RotateCameraObject();
	Game* owner;

	Vector4 getHeading(); // A normalized vector giving the direction the object is heading
	Vector4 getPosition();
	Vector4 getUp();
	Vector4 getSideLeft();

	Vector4 getCameraChangeVec(); // A normalized vector giving the direction the camera's position should be changed by

	virtual bool handleEvent(Event* evt);

	void setPosition(const Vector4& position);

	virtual void update(float dt);

	virtual std::string toString();

};

