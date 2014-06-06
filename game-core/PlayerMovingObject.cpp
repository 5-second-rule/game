#include "PlayerMovingObject.h"

#include "CollisionMetadata.h"

PlayerMovingObject::PlayerMovingObject(int objectType, Game* owner)
	: MovingObject(objectType, owner)
{
	this->dead = false;
}


PlayerMovingObject::~PlayerMovingObject()
{
}

void PlayerMovingObject::update(float dt) {
	MovingObject::update(dt);

	TrackPath *track = Game::getGlobalInstance()->getTrackPath();

	int wallOfDeathLocation = Game::getGlobalInstance()->getWallOfDeath()->getTrackIndex();
	int space = track->nodes.size();
	int wallOfDeathTail = (wallOfDeathLocation + (space / 2)) % space;
	int comparativeIndex = this->trackIndex;

	bool projectForward = wallOfDeathTail > wallOfDeathLocation;
	if (projectForward) {
		comparativeIndex += comparativeIndex > wallOfDeathTail ? 0 : space;
		wallOfDeathLocation += space;
	}

	if (comparativeIndex < wallOfDeathLocation && comparativeIndex > wallOfDeathTail) {
		this->dead = true;
	}
}

void PlayerMovingObject::handleCollision(std::shared_ptr<const Bounds> bounds, float dt, int metadata) {
	MovingObject::handleCollision(bounds, dt, metadata);

	if (metadata == CollisionMetadata::POWERUP) {
		if( Game::getGlobalInstance()->getEngineInstance()->getDebugLevel() > 0 ) {
			cout << ">>>>>>>>>>>> power up" << endl;
		}

		const float TRACK_FORCE = 3000.0f;
		TrackPath *track = Game::getGlobalInstance()->getTrackPath();
		Vector4 trackForce = track->nodes[this->trackIndex].normal * TRACK_FORCE;
		this->applyForce(trackForce);
	}
}

int PlayerMovingObject::getCollisionMetadata() const {
	return CollisionMetadata::PLAYER;
}

void PlayerMovingObject::reserveSize(IReserve& buffer) const {
	MovingObject::reserveSize(buffer);
	buffer.reserve(sizeof(PlayerMovingObjectData));
}

void PlayerMovingObject::fillBuffer(IFill& buffer) const {
	MovingObject::fillBuffer(buffer);
	PlayerMovingObjectData* data = reinterpret_cast<PlayerMovingObjectData*>(buffer.getPointer());

	data->dead = this->dead;

	buffer.filled();
}

void PlayerMovingObject::deserialize(BufferReader& reader) {
	MovingObject::deserialize(reader);

	const PlayerMovingObjectData* data = reinterpret_cast<const PlayerMovingObjectData*>(reader.getPointer());

	this->dead = data->dead;

	reader.finished(sizeof(PlayerMovingObjectData));
}