#include "RotateCameraObject.h"

#include <chrono>

#include "ObjectTypes.h"
#include "Game.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define M_PI 3.14159265358979323846
#define ROTATE_INC 0.1

RotateCameraObject::RotateCameraObject() : BaseObject(ObjectTypes::RotateCamera)
{
	this->up = Vector(0.0f, 1.0f, 0.0f);
	this->heading = Vector(0.0f, 0.0f, 1.0f);
	this->sideLeft = Vector(-1.0f, 0.0f, 0.0f);
	this->rotateAmt = 0;
	this->cameraChangeVec = Vector(0.0f, 0.0f, 1.0f);
}

RotateCameraObject::~RotateCameraObject() {}


Vector4 RotateCameraObject::getHeading(){
	return this->heading;
}

Vector4 RotateCameraObject::getUp() {
	return this->up;
}

void RotateCameraObject::setPosition(const Vector4& pos) {
	this->position = pos;
}

Vector4 RotateCameraObject::getSideLeft() {
	return this->sideLeft;
}

void RotateCameraObject::update(float dt){
	BaseObject::update(dt);

	rotateAmt += ROTATE_INC * dt;

	if (rotateAmt >=0 && rotateAmt <= M_PI)
	{
		double x(0.0), y(0.0), z(0.0);
		double cosAngle = cos(rotateAmt);
		double sinAngle = sin(rotateAmt);

		x = cosAngle;
		z = sinAngle;

		this->cameraChangeVec = Vector4(x, y, z, 1.0);
	}
}

Vector4 RotateCameraObject::getCameraChangeVec() {
	return this->cameraChangeVec;
}

bool RotateCameraObject::handleEvent(Event *evt){
	return false;
}