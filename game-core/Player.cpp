#include "Player.h"

#include "GameState.h"

Player::Player(GameState* state) : Player(-1, state) {}

Player::Player(unsigned int guid, GameState* state) {
	this->data.guid = guid;
	this->data.selection = 0;
	this->data.selected = false;
	this->gameState = state;
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
	int nextToon;
	switch (ActionType(evt->getActionType())) {
	case ActionType::SELECT: {
		const SelectionEvent *selectionEvent = ActionEvent::cast<SelectionEvent>(evt);
		if (selectionEvent == nullptr) return;

		switch (selectionEvent->selection.action) {
		case SelectionEvent::Select:
			this->data.selected = true;
			this->gameState->useToon(this->data.selected);
			break;

		case SelectionEvent::Deselect:
			this->data.selected = false;
			this->gameState->unuseToon(this->data.selected);
			break;

		case SelectionEvent::Toggle:
			this->data.selected = !this->data.selected;
			this->gameState->toggleToonUsed(this->data.selected);
			break;

		case SelectionEvent::Prev:
			nextToon = this->data.selection;
			if (!this->isSelected()) {
				do {
					nextToon = (nextToon + 3) % 4;
				} while (this->gameState->isToonUsed(nextToon) && nextToon != this->data.selection);

				this->data.selection = nextToon;
			}
			break;

		case SelectionEvent::Next:
			nextToon = this->data.selection;
			if (!this->isSelected()) {
				do {
					nextToon = (nextToon + 1) % 4;
				} while (this->gameState->isToonUsed(nextToon) && nextToon != this->data.selection);

				this->data.selection = nextToon;
			}
			break;

		case SelectionEvent::Go:
			this->gameState->setState(GameState::Game);
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