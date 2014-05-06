#include "PhysicsObject.h"
#include "GameInstance.h"
#include "MoveEvent.h"

PhysicsObject::PhysicsObject(int objectType) : BaseObject(objectType) {
	m_body = new RigidBody();
	world = nullptr;
}


PhysicsObject::~PhysicsObject() {
}

RigidBody* PhysicsObject::getBody() {
	return nullptr;
}

void PhysicsObject::update(float dt){
	BaseObject::update(dt);
}

bool PhysicsObject::handleEvent(Event * evt) {
	return BaseObject::handleEvent(evt);
}

void PhysicsObject::reserveSize(IReserve& buffer) {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(float[3]) * 2);
}

void PhysicsObject::fillBuffer(IFill& buffer) {
	BaseObject::fillBuffer(buffer);
	char* buf = buffer.getPointer();
	
	memcpy(buf, position, sizeof(float[3]));
	memcpy(buf + sizeof(float[3]), force, sizeof(float[3]));

	buffer.filled();
}

void PhysicsObject::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const char* buf = reader.getPointer();

	memcpy(position, buf, sizeof(float[3]));
	memcpy(force, buf + sizeof(float[3]), sizeof(float[3]));

	reader.finished(sizeof(float[3]) * 2);
}