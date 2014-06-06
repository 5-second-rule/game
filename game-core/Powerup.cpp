#include "Powerup.h"

#include "MoveEvent.h"
#include "ActionType.h"
#include "Sounds.h"

#include "ObjectTypes.h"

#include "Game.h"

#include "CollisionMetadata.h"
#include "TrackPath.h"
#include "Game.h"

Powerup::Powerup(int objectType) : StaticObject(objectType) {
	this->trackIndex = 0;
	this->rotationDegrees = static_cast<float>(rand() % 360);
	this->timeToLiveAgain = 0;
}

Powerup::~Powerup() {
}

Vector4 Powerup::getPosition() {
	return this->position;
}

int Powerup::getTrackIndex() {
	return this->trackIndex;
}

void Powerup::update(float dt) {
	if (this->timeToLiveAgain > 0) {
		this->timeToLiveAgain -= dt;
	}

	this->rotationDegrees = static_cast<float>(fmod(this->rotationDegrees + dt, 360));
	this->rotation = Vector4(0, this->rotationDegrees, 0);
}

void Powerup::place(int trackIndexAt) {
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();
	PathNode node = track->nodes[trackIndexAt];

	// TODO place off center
	this->position = node.point;
	this->trackIndex = trackIndexAt;
}

void Powerup::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(PowerupData));
}

void Powerup::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	PowerupData* data = reinterpret_cast<PowerupData*>(buffer.getPointer());

	data->position[0] = this->position[0];
	data->position[1] = this->position[1];
	data->position[2] = this->position[2];

	data->rotation[0] = this->rotation[0];
	data->rotation[1] = this->rotation[1];
	data->rotation[2] = this->rotation[2];

	data->trackIndex = this->trackIndex;

	data->timeToLive = this->timeToLiveAgain;

	buffer.filled();
}

void Powerup::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const PowerupData* data = reinterpret_cast<const PowerupData*>(reader.getPointer());

	this->position = Common::Point(data->position[0], data->position[1], data->position[2]);
	this->rotation = Common::Point(data->rotation[0], data->rotation[1], data->rotation[2]);
	this->trackIndex = data->trackIndex;

	this->timeToLiveAgain = data->timeToLive;

	reader.finished(sizeof(PowerupData));
}

Vector4 Powerup::getGroupingParameter() const {
	return Vector(0.0f, 0.0f, (float)this->trackIndex);
}

bool Powerup::collidesWith(const ICollidable* target) const {
	if (this->timeToLiveAgain > 0) {
		return false;
	}

	std::shared_ptr<const Bounds> bounds = target->getBounds();

	if (bounds->type == BoundsType::Sphere) {
		std::shared_ptr<const BoundingSphere> bs = std::static_pointer_cast<const BoundingSphere>(bounds);
		std::shared_ptr<const BoundingSphere> me = std::static_pointer_cast<const BoundingSphere>(this->getBounds());

		float distance = (me->radius + bs->radius);
		return ((bs->position - me->position).lengthSquared() <= distance * distance);
	}
	else return false;
}

void Powerup::handleCollision(std::shared_ptr<const Bounds> bounds, float dt, int metadata) {
	if (metadata == CollisionMetadata::PLAYER) {
		this->timeToLiveAgain = 3;
		return;
	}
}

std::shared_ptr<const Bounds> Powerup::getBounds() const {
	BoundingSphere* bounds = new BoundingSphere();

	assert(bounds->type == BoundsType::Sphere);
	bounds->position = this->position;
	bounds->velocity = Vector4();
	bounds->radius = 10.0f;
	bounds->mass = 0.0f;

	return shared_ptr<const Bounds>(bounds);
}

unsigned int Powerup::getPriority() const {
	return static_cast<unsigned int>(CollisionPriorities::Object);
}

int Powerup::getCollisionMetadata() const {
	return CollisionMetadata::POWERUP;
}