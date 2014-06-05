#include "Player.h"

#include "GameState.h"

Player::Player(GameState* state) : Player(-1, state) {}

Player::Player(unsigned int guid, GameState* state) {
	this->data.guid = guid;
	this->data.selected = false;
	this->gameState = state;
	for (int i = 0; i < 4; i++) {
		if (!this->gameState->isToonUsed(i)) {
			this->data.selection = i;
			break;
		}
	}
}

Player::~Player() {
}

void Player::spawnMoveableObject() {
	PlayerMovingObject* m = new PlayerMovingObject(this->getSelection(), Game::getGlobalInstance());

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(m, HandleType::GLOBAL);
	w->insert(m);

	this->data.movingObject = m->getHandle();
}

void Player::spawnRotateCameraObject() {
	RotateCameraObject* c = new RotateCameraObject();

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(c, HandleType::GLOBAL);
	w->insert(c);

	this->data.rotateCameraObject = c->getHandle();
}

Handle Player::getMovingObject() {
	return this->data.movingObject;
}

Handle Player::getRotateCameraObject() {
	return this->data.rotateCameraObject;
}

void Player::respawn() {
	int wwodPosition = Game::getGlobalInstance()->getWallOfDeath()->getTrackIndex();
	int leaderIndex = this->gameState->getLeaderboard()[0].playerPosition;

	TrackPath *track = Game::getGlobalInstance()->getTrackPath();

	int trackSize = track->nodes.size();
	if (wwodPosition > leaderIndex) {
		leaderIndex += trackSize;
	}

	int newTrackIndex = ((leaderIndex + wwodPosition) / 2) % trackSize;

	MovingObject* m = dynamic_cast<MovingObject*>(
		Game::getGlobalInstance()
		->getEngineInstance()
		->getWorld()
		->get(this->data.movingObject)
		);

	m->setPosition(track->nodes[newTrackIndex].point);
	m->setTrackIndex(newTrackIndex);
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
			this->gameState->useToon(this->data.selection);
			break;

		case SelectionEvent::Deselect:
			this->data.selected = false;
			this->gameState->unuseToon(this->data.selection);
			break;

		case SelectionEvent::Toggle:
			this->data.selected = !this->data.selected;
			this->gameState->toggleToonUsed(this->data.selection);
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
			this->gameState->setState(GameState::Countdown);
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
	if (this->gameState->getState() == GameState::Countdown)
		return this->data.rotateCameraObject;
		
	else if(this->gameState->getState() == GameState::Game)
		return this->data.movingObject;
	else
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