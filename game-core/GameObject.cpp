#include "GameObject.h"


GameObject::GameObject() : BaseObject(0) {
	m_body = new RigidBody();
	world = nullptr;
}


GameObject::~GameObject() {
}

bool GameObject::onEvent( Event event ) {
	//TODO implement
	return false;
}

Vector4 GameObject::side() {
	//TODO implement
	return Vector4();
}

Vector4 GameObject::top() {
	//TODO implement
	return Vector4();
}