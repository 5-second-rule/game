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

RotateCameraObject::RotateCameraObject()
	: RotateCameraObject(Vector(0,0,0), Vector(0,0,0), Point(0,0,0))
{}

RotateCameraObject::RotateCameraObject(const Vector4& target, const Vector4& heading, const Vector4& up)
	: BaseObject(ObjectTypes::RotateCamera)
	, target(target)
	, rotateAmt(0)
	, heading(Vector4::normalize(heading))
	, up(Vector4::normalize(up))
{
	this->target[3] = 1.0f;
	this->heading[3] = 0.0f;
	this->up[3] = 0.0f;
}

RotateCameraObject::~RotateCameraObject() {}

const Vector4& RotateCameraObject::getTarget() {
	return this->target;
}

Vector4 RotateCameraObject::getDelta() {
	Vector4 delta = Vector4::normalize((Matrix4::rotate(up, rotateAmt) * heading) * (cos(rotateAmt) * 0.5 + 0.5));
	delta[3] = 0;
	return delta;
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

void RotateCameraObject::reserveSize(IReserve& buffer) const{
	BaseObject::reserveSize(buffer);

	buffer.reserve(sizeof(RotateCameraObjectData));
}

void RotateCameraObject::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);

	RotateCameraObjectData* data = reinterpret_cast<RotateCameraObjectData*>(buffer.getPointer());

	memcpy(data->up, this->up.getPointer(), sizeof(float[3]));
	memcpy(data->heading, this->heading.getPointer(), sizeof(float[3]));
	memcpy(data->target, this->target.getPointer(), sizeof(float[3]));
	data->rotateAmt = this->rotateAmt;

	buffer.filled();
}
void RotateCameraObject::deserialize(BufferReader& buffer) {
	BaseObject::deserialize(buffer);

	const RotateCameraObjectData* data = reinterpret_cast<const RotateCameraObjectData*>(buffer.getPointer());
	
	this->up.set(data->up[0], data->up[1], data->up[2], 0.0f);
	this->heading.set(data->heading[0], data->heading[1], data->heading[2], 0.0f);
	this->target.set(data->target[0], data->target[1], data->target[2], 1.0f);
	this->rotateAmt = data->rotateAmt;

	buffer.finished(sizeof(RotateCameraObjectData));

};