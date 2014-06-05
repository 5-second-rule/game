#define _USE_MATH_DEFINES
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

#define ROTATE_INC 0.1

RotateCameraObject::RotateCameraObject(const Vector4& target, const Vector4& heading, const Vector4& up)
	: BaseObject(ObjectTypes::RotateCamera)
	, target(target)
	, rotateAmt(0)
	, heading(Vector4::normalize(heading))
	, up(Vector4::normalize(up))
{}

RotateCameraObject::~RotateCameraObject() {}

const Vector4& RotateCameraObject::getTarget() {
	return this->target;
}
const Vector4& RotateCameraObject::getDelta() {
	return (Matrix4::rotate(up, rotateAmt) * heading) * (cos(rotateAmt) * 0.5 + 0.5);
}
const Vector4& RotateCameraObject::getUp() {
	return up;
}

void RotateCameraObject::update(float dt) {
	BaseObject::update(dt);

	if (rotateAmt < M_PI) rotateAmt += ROTATE_INC * dt;

}

bool RotateCameraObject::handleEvent(Event *evt){
	return false;
}