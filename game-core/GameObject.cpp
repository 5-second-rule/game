#include "GameObject.h"

#include "MoveEvent.h"

GameObject::GameObject(int objectType) : BaseObject(objectType) {
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

void GameObject::handleEvent(Event * evt) {
	MoveEvent *moveEvent = dynamic_cast<MoveEvent *>(evt);
	if (moveEvent != nullptr) {
		switch (moveEvent->direction) {
			case MoveDirection::UP:
				this->position[1] += 0.1;
				break;
			case MoveDirection::DOWN:
				this->position[1] -= 0.1;
				break;
			case MoveDirection::RIGHT:
				this->position[0] += 0.1;
				break;
			case MoveDirection::LEFT:
				this->position[0] -= 0.1;
				break;
			default:
				break;
		}
	}
}