#include "PlayerMovingObject.h"

#include "CollisionMetadata.h"

PlayerMovingObject::PlayerMovingObject(int objectType, Game* owner)
	: MovingObject(objectType, owner)
{
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
		cout << "you died" << endl;
	}
	else {
		cout << "you're at : " << this->trackIndex << endl;
	}
}

void PlayerMovingObject::handleCollision(std::shared_ptr<const Bounds> bounds, float dt, int metadata) {
	MovingObject::handleCollision(bounds, dt, metadata);

	if (metadata == CollisionMetadata::POWERUP) {
		cout << ">>>>>>>>>>>> power up" << endl;
	}
}

int PlayerMovingObject::getCollisionMetadata() const {
	return CollisionMetadata::PLAYER;
}
