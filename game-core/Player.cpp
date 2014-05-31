#include "Player.h"

Player::Player() : Player(-1) {}

Player::Player(unsigned int guid) {
	this->data.guid = guid;
	this->data.selection = 0;
	this->data.selected = false;
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

void Player::updateSelection(int tempSelection) {
	this->data.selection = tempSelection;
}

int Player::getDeathCount() {
	return this->data.deathCount;
}

int Player::getSelection() {
	return this->data.selection;
}

bool Player::isSelected() {
	return this->data.selected;
}

unsigned int Player::getGuid() {
	return this->data.guid;
}

void Player::handleEvent(ActionEvent *evt) {


	switch (ActionType(evt->getActionType())) {
	case ActionType::SELECT: {
		const SelectionEvent *selectionEvent = ActionEvent::cast<SelectionEvent>(evt);
		if (selectionEvent == nullptr) return;

		switch (selectionEvent->selection.action) {
		case SelectionEvent::Select:
			this->data.selected = true;
			break;

		case SelectionEvent::Deselect:
			this->data.selected = false;
			break;

		case SelectionEvent::Toggle:
			this->data.selected = !this->data.selected;
			break;

		case SelectionEvent::Prev:
			if(!this->isSelected())
				this->data.selection = (this->data.selection - 1) % 4;
			break;
		case SelectionEvent::Next:
			if (!this->isSelected())
				this->data.selection = (this->data.selection + 1) % 4;
			break;
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