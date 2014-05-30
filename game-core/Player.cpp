#include "Player.h"

Player::Player() {
	this->data.guid = -1;
	this->data.tempSelection = 0;
	this->data.selection = -1;
}

Player::Player(unsigned int guid) {
	this->data.guid = guid;
	this->data.tempSelection = 0;
	this->data.selection = -1;
}

Player::~Player() {
}

void Player::spawnMoveableObject() {
	MovingObject* m = new MovingObject(this->getSelection(), Game::getGlobalInstance());

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(m, HandleType::GLOBAL);
	w->insert(m);

	this->data.movingObject = m->getHandle();
}

void Player::die() {
	this->data.deathCount++;
}

void Player::updateTempSelection(int tempSelection) {
	this->data.tempSelection = tempSelection;
}

void Player::makeSelection(int selection) {
	this->data.selection = selection;
}

int Player::getDeathCount() {
	return this->data.deathCount;
}

int Player::getTempSelection() {
	return this->data.tempSelection;
}

int Player::getSelection() {
	return this->data.selection;
}

unsigned int Player::getGuid() {
	return this->data.guid;
}

void Player::handleEvent(ActionEvent *evt) {


	switch (ActionType(evt->getActionType())) {
	case ActionType::SELECT: {
		const SelectionEvent *selectionEvent = ActionEvent::cast<SelectionEvent>(evt);
		if (selectionEvent == nullptr) return;

		if (selectionEvent->selection.selectChar) {
			this->data.selection = this->data.tempSelection;
		}

		if (selectionEvent->selection.unselectChar) {
			this->data.selection = -1;
		}

		if (selectionEvent->selection.toggleSelect) {
			if (this->data.selection != -1) {
				this->data.selection = this->data.tempSelection;
			} else {
				this->data.selection = -1;
			}
		}

		if (selectionEvent->selection.selectionDirection < 0) {
			this->data.tempSelection = (this->data.tempSelection + 3) % 4;
		} else if (selectionEvent->selection.selectionDirection > 0) {
			this->data.tempSelection = (this->data.tempSelection + 1) % 4;
		}

		break;
	}
	default:
		MovingObject* m = dynamic_cast<MovingObject*>(
			Game::getGlobalInstance()
			->getEngineInstance()
			->getWorld()
			->get(this->data.movingObject)
		);

		if(m != nullptr) m->handleEvent(evt);
		break;
	}
}

Handle Player::cameraTarget() {
	//return this->movableObject->getHandle();
	return Handle();
}

void Player::reserveSize(IReserve& buffer) const {
	buffer.reserve(sizeof(PlayerData));
}

void Player::fillBuffer(IFill& buffer) const {
	PlayerData * data = reinterpret_cast<PlayerData*>(buffer.getPointer());
	*data = this->data;
	buffer.filled();
}

void Player::deserialize(BufferReader& buffer) {
	const PlayerData *data = reinterpret_cast<const PlayerData*>(buffer.getPointer());
	this->data = *data;
	buffer.finished(sizeof(PlayerData));
}