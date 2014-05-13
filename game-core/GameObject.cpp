#include "GameObject.h"
#include "GameInstance.h"
#include "MoveEvent.h"

GameObject::GameObject(int objectType) : BaseObject() {
	m_body = new RigidBody();
}

GameObject::~GameObject() {
	delete m_body;
}

RigidBody* GameObject::getBody() {
	return nullptr;
}

void GameObject::update(float dt){
	BaseObject::update(dt);
}

bool GameObject::handleEvent(Event *evt) {
	return BaseObject::handleEvent(evt);
}

string GameObject::toString(){
	stringstream buffer;
	buffer << BaseObject::toString() << endl;
	buffer << m_body->toString();
	return buffer.str();
}

void GameObject::setPosition(Vector4 &pos){
	m_body->m_position = Vector4(pos);
}
