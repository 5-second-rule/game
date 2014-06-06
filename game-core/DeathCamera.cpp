#include "DeathCamera.h"

#include "ObjectTypes.h"
#include "TrackPath.h"
#include "Game.h"

DeathCamera::DeathCamera(Handle gameState)
	: BaseObject(ObjectTypes::DeathCam)
	, gameState(gameState)
{}

DeathCamera::~DeathCamera() {}

Vector4 DeathCamera::getPosition() {
	return this->position;
}

Vector4 DeathCamera::getTarget() {
	return this->target;
}

void DeathCamera::update(float dt) {
	// get leaderboard position as target
	int leaderIndex = this->getGameState()->getLeaderboard()[0].playerPosition;
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();

	this->target = track->nodes[leaderIndex].point;

	// add tube normal to get position
	this->position = this->target + track->nodes[leaderIndex].normal * 10.0f;
}

GameState* DeathCamera::getGameState() {
	return dynamic_cast<GameState*>(theWorld.get(this->gameState));
}

void DeathCamera::reserveSize(IReserve& buffer) const {
	this->gameState.reserveSize(buffer);
	buffer.reserve(sizeof(DeathCameraData));
}
void DeathCamera::fillBuffer(IFill& buffer) const {
	this->gameState.fillBuffer(buffer);
	DeathCameraData* data = reinterpret_cast<DeathCameraData*>(buffer.getPointer());

	memcpy(data->target, this->target.getPointer(), sizeof(float[3]));
	memcpy(data->position, this->position.getPointer(), sizeof(float[3]));

	buffer.filled();
}
void DeathCamera::deserialize(BufferReader& buffer) {
	this->gameState.deserialize(buffer);
	const DeathCameraData* data = reinterpret_cast<const DeathCameraData*>(buffer.getPointer());

	this->target.set(data->target[0], data->target[1], data->target[2], 1.0f);
	this->position.set(data->position[0], data->position[1], data->position[2], 1.0f);

	buffer.finished(sizeof(DeathCameraData));
}


