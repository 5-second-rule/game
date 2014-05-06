#include "GameObject.h"
#include "GameInstance.h"
#include "MoveEvent.h"

GameObject::GameObject(int objectType) : BaseObject(objectType) {
	m_body = new RigidBody();
	world = nullptr;
}


GameObject::~GameObject() {
}

RigidBody* GameObject::getBody() {
	return nullptr;
}

void GameObject::update(float dt){
	BaseObject::update(dt);
}

bool GameObject::handleEvent(Event * evt) {
	return BaseObject::handleEvent(evt);
}

void GameObject::reserveSize(IReserve& buffer) {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(float[3]) * 2);
}

void GameObject::fillBuffer(IFill& buffer) {
	BaseObject::fillBuffer(buffer);
	char* buf = buffer.getPointer();
	
	memcpy(buf, position, sizeof(float[3]));
	memcpy(buf + sizeof(float[3]), force, sizeof(float[3]));

	buffer.filled();
}

void GameObject::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const char* buf = reader.getPointer();

	memcpy(position, buf, sizeof(float[3]));
	memcpy(force, buf + sizeof(float[3]), sizeof(float[3]));

	reader.finished(sizeof(float[3]) * 2);
}