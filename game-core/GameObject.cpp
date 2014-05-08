#include "GameObject.h"
#include "GameInstance.h"
#include "MoveEvent.h"

GameObject::GameObject(int objectType) : BaseObject() {
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