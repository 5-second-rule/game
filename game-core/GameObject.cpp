#include "GameObject.h"
#include "GameInstance.h"
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
	ActionEvent *actionEvt = dynamic_cast<ActionEvent *>(evt);
	if( actionEvt != nullptr ) {
		if( ActionType( actionEvt->actionType ) == ActionType::MOVE ) {
			MoveEvent *moveEvent = dynamic_cast<MoveEvent *>(evt);
			if( moveEvent != nullptr ) {
				switch( moveEvent->direction ) {
					case MoveDirection::UP:
						this->position[1] += 0.05;
						break;
					case MoveDirection::DOWN:
						this->position[1] -= 0.05;
						break;
					case MoveDirection::RIGHT:
						this->position[0] += 0.05;
						break;
					case MoveDirection::LEFT:
						this->position[0] -= 0.05;
						break;
					case MoveDirection::FORWARD:
						this->position[2] += 0.1;
						break;
					case MoveDirection::BACK:
						this->position[2] -= 0.1;
						break;
					default:
						break;
				}
			}
		} else if( ActionType( actionEvt->actionType ) == ActionType::SHOOT ) {
			// create projectile and set it in motion
		}
	}
}