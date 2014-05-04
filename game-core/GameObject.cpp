#include "GameObject.h"


GameObject::GameObject() : BaseObject(0) {
	m_body = new RigidBody();
	world = nullptr;
}


GameObject::~GameObject() {
}

bool GameObject::onMessage( Event* evt ) {
	return false;
}

RigidBody* GameObject::getBody() {
	return nullptr;
}