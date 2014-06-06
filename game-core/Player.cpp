#include "Player.h"

#include "GameState.h"
#include "DeathCamera.h"

Player::Player(GameState* state) : Player(-1, state) {}

Player::Player(unsigned int guid, GameState* state) {
	this->data.guid = guid;
	this->data.selected = false;
	this->data.deathCount = 0;
	this->data.hasAdrenaline = false;
	this->gameState = state;
	for (int i = 0; i < 4; i++) {
		if (!this->gameState->isToonUsed(i)) {
			this->data.selection = i;
			break;
		}
	}

	this->data.dead = false;
}

Player::~Player() {
}

void Player::spawnMoveableObject() {

	PlayerMovingObject* m = new PlayerMovingObject(this->getSelection(), Game::getGlobalInstance());

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(m, HandleType::GLOBAL);
	w->insert(m);

	//bool movement = this->gameState->getState() == GameState::State::Game;
	m->setFollowTrack(false);
	m->setHasPropulsion(false);

	this->data.movingObject = m->getHandle();
}

void Player::spawnRotateCameraObject() {
	MovingObject* m = dynamic_cast<MovingObject*>(theWorld.get(this->data.movingObject));
	RotateCameraObject* c = new RotateCameraObject(m->getPosition(), m->getHeading(), m->getUp());

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(c, HandleType::GLOBAL);
	w->insert(c);

	this->data.rotateCameraObject = c->getHandle();
}

void Player::spawnDeathCamera() {
	DeathCamera* c = new DeathCamera(this->gameState->getHandle());

	World* w = Game::getGlobalInstance()->getEngineInstance()->getWorld();
	w->allocateHandle(c, HandleType::GLOBAL);
	w->insert(c);

	this->data.deathCamera = c->getHandle();
}

Handle Player::getMovingObject() {
	return this->data.movingObject;
}

Handle Player::getRotateCameraObject() {
	return this->data.rotateCameraObject;
}

void Player::addPowerup() {
	this->data.hasAdrenaline = true;
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

	PlayerMovingObject* m = dynamic_cast<PlayerMovingObject*>(
		Game::getGlobalInstance()
		->getEngineInstance()
		->getWorld()
		->get(this->data.movingObject)
		);

	m->dead = false;

	m->setPosition(track->nodes[newTrackIndex].point);
	m->setTrackIndex(newTrackIndex);

	m->setFollowTrack(true);
	m->setHasPropulsion(true);
}

void Player::die() {
	this->data.deathCount++;
	this->data.dead = true;
	this->data.respawnTimer = 0.0f;

	MovingObject* m = dynamic_cast<MovingObject*>(theWorld.get(this->data.movingObject));
	if (m != nullptr) {
		m->setHasPropulsion(false);
		m->setFollowTrack(false);
	}
}

void Player::update(float dt) {
	if (this->data.dead) {
		this->data.respawnTimer += dt;
		if (this->data.respawnTimer >= 5.0f) {
			this->data.dead = false;
			this->respawn();
		}
	}
}

void Player::updateSelection(int tempSelection) {
	this->data.selection = tempSelection;
}

int Player::getDeathCount() {
	return this->data.deathCount;
}

bool Player::isDead() {
	return this->data.dead;
}

int Player::getSelection() {
	return this->data.selection;
}

bool Player::isSelected() {
	return this->data.selected;
}

bool Player::hasAdrenaline() {
	return this->data.hasAdrenaline;
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
	case ActionType::SHOOT:
		if (this->data.hasAdrenaline) {
			this->data.hasAdrenaline = false;

			PlayerMovingObject* m = dynamic_cast<PlayerMovingObject*>(
				Game::getGlobalInstance()
				->getEngineInstance()
				->getWorld()
				->get(this->data.movingObject)
			);
			if (m != nullptr) {
				const float ADRENALINE_FORCE = 500.0f;
				Vector4 adrenalineForce = m->getHeading() * ADRENALINE_FORCE;
				m->applyForce(adrenalineForce);
			}
		}
		break;
	default:
		PlayerMovingObject* m = dynamic_cast<PlayerMovingObject*>(
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
	if (this->data.deathCount >= MAX_LIVES)
		return this->data.deathCamera;

	else if (this->gameState->getState() == GameState::Countdown)
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