#include "PlayerMovingObject.h"

#include "MoveEvent.h"
#include "ActionType.h"
#include "Sounds.h"
#include "CollisionMetadata.h"

PlayerMovingObject::PlayerMovingObject(int objectType, Game* owner)
	: MovingObject(objectType, owner)
{
	this->dead = false;

	this->boostCount = 100;
	this->underTwentyFive = false;
	this->releaseCount = 0;

	this->hasNewPowerup = false;
}


PlayerMovingObject::~PlayerMovingObject() {}

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

		this->hasNewPowerup = true;
	}
}

int PlayerMovingObject::getCollisionMetadata() const {
	return CollisionMetadata::PLAYER;
}

int PlayerMovingObject::getBoostCount()
{
	return this->boostCount;
}

void PlayerMovingObject::checkBoost()
{
	if (this->propulsion < 2)
	{
		//Increment boost
		this->boostCount += 1;

		if (this->boostCount > 100)
		{
			this->boostCount = 100;
		}

		if (this->underTwentyFive)
		{
			this->releaseCount++;
			if (this->boostCount > 25)
			{
				this->underTwentyFive = false;
				this->releaseCount = 0;
			}
		}
	}
	else {
		//Handle Decreasing Boost Logic

		if (this->releaseCount > 3 && this->underTwentyFive)
		{
			this->propulsion = 1;
		}
		else {

			this->boostCount -= 4;

			if (this->boostCount < 0)
			{
				this->boostCount = 0;
				this->propulsion = 1;
			}

			if (this->boostCount < 25)
			{
				this->underTwentyFive = true;
			}
		}
	}
}

bool PlayerMovingObject::handleEvent(Event *evt){

	float position[3] = { this->getPosition().x(), this->getPosition().y(), this->getPosition().z() };
	ActionEvent *actionEvt = Event::cast<ActionEvent>(evt);
	if (actionEvt == nullptr)
		return false;

	switch (ActionType(actionEvt->getActionType())) {
	case ActionType::MOVE:
	{
		MoveEvent *moveEvent = ActionEvent::cast<MoveEvent>(actionEvt);
		if (moveEvent == nullptr){
			return false;
		}

		const float MOVE_FORCE = 10.0f;
		const float ROT_SCALE = 0.08f;
		const float BRAKE_SCALE = 0.5f;

		const float UP_SCALE = 1.0f;
		const float LEFT_SCALE = 1.0f;

		this->propulsion = moveEvent->direction.z + 1.0f; // [-1,1] -> [0,2]

		this->checkBoost();

		//Point in direction of track and update up
		if (this->propulsion < 2) {
			TrackPath *track = Game::getGlobalInstance()->getTrackPath();

			this->heading = track->nodes[this->trackIndex].normal;
			this->heading.normalize();
			this->heading.set(3, 0);

			this->sideLeft = Vector4::cross(up, heading);
			this->sideLeft.normalize();

			this->up = Vector4::cross(heading, this->sideLeft);
			this->up.normalize();
			// finish updating in regards to track
			this->forceUp = this->up * (moveEvent->direction.y * UP_SCALE);

			// rotate around heading
			this->up = Matrix4::rotate(this->heading, moveEvent->direction.w * ROT_SCALE) * this->up;

			//rotate sideways
			this->heading = Matrix4::rotate(this->up, -moveEvent->direction.x * ROT_SCALE) * this->heading;

			//rotate up and down
			Matrix4 rot = Matrix4::rotate(this->sideLeft, moveEvent->direction.y * ROT_SCALE);
			this->heading = rot * heading;
			this->up = rot * up;
		}
		else
		{
			this->sideLeft = Vector4::cross(up, heading); //doing so sideLeft is set at least once
			this->sideLeft.normalize();

			this->forceUp = this->up * (moveEvent->direction.y * UP_SCALE); //needs to be set with old up
		}

		this->forceRight = this->sideLeft * (moveEvent->direction.x * LEFT_SCALE);

		return true;
		break;
	}
	case ActionType::SHOOT:
		owner->getEngineInstance()->sendEvent(new SoundEvent(static_cast<int>(Sounds::SHOOT), false, false, position));
		//TODO: create projectile and set it in motion
		break;
	default:
		break;
	}
	return false;
}


bool PlayerMovingObject::collidesWith( const ICollidable* target ) const
{
	if( this->dead )
	{
		return false;
	}

	return MovingObject::collidesWith( target );
}

unsigned int PlayerMovingObject::getPriority() const
{
	return static_cast<unsigned int>(CollisionPriorities::Player);
}

void PlayerMovingObject::reserveSize(IReserve& buffer) const {
	MovingObject::reserveSize(buffer);
	buffer.reserve(sizeof(PlayerMovingObjectData));
}

void PlayerMovingObject::fillBuffer(IFill& buffer) const {
	MovingObject::fillBuffer(buffer);
	PlayerMovingObjectData* data = reinterpret_cast<PlayerMovingObjectData*>(buffer.getPointer());

	data->dead = this->dead;
	data->boostCount = this->boostCount;
	data->releaseCount = this->releaseCount;
	data->underTwentyFive = this->underTwentyFive;

	buffer.filled();
}

void PlayerMovingObject::deserialize(BufferReader& reader) {
	MovingObject::deserialize(reader);

	const PlayerMovingObjectData* data = reinterpret_cast<const PlayerMovingObjectData*>(reader.getPointer());

	this->dead = data->dead;
	this->boostCount = data->boostCount;
	this->releaseCount = data->releaseCount;
	this->underTwentyFive = data->underTwentyFive;

	reader.finished(sizeof(PlayerMovingObjectData));
}
