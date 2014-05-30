#include "MovingObject.h"

#include "MoveEvent.h"
#include "ActionType.h"
#include "Sounds.h"
#include "ObjectTypes.h"
#include "Game.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define MAX_SPEED 75
#define MAX_FORCE 100

const float MovingObject::max_speed = MAX_SPEED;
const float MovingObject::max_force = MAX_FORCE;

MovingObject::MovingObject(int objectType, Game* owner, bool follow, bool propulse)
	: BaseObject(objectType)
	, owner(owner)
{
	this->up = Vector(0.0f, 1.0f, 0.0f);
	this->heading = Vector(0.0f, 0.0f, 1.0f);
	this->mass = .1f;
	this->propulsion = 1.0f;
	this->friction = .2f;
	this->trackIndex = 0;
	this->trackVelocity = 1000;

	this->followTrack = follow;
	this->hasPropulsion = propulse;
}

MovingObject::MovingObject(int objectType, Game* owner)
	: MovingObject(objectType, owner, true, true) {}


MovingObject::~MovingObject() {}


Vector4 MovingObject::getHeading(){
	return this->heading;
}

float MovingObject::getSpeed(){
	return this->velocity.length();
}

Vector4 MovingObject::getVelocity() {
	return this->velocity;
}

Vector4 MovingObject::getUp() {
	return this->up;
}

void MovingObject::applyForce(const Vector4& force){
	this->force += force;
}

int MovingObject::getTrackIndex() {
	return this->trackIndex;
}

bool MovingObject::handleEvent(Event *evt){

	ActionEvent *actionEvt = Event::cast<ActionEvent>(evt);
	if (actionEvt == nullptr)
		return false;

	switch (ActionType(actionEvt->getActionType())) {
	case ActionType::MOVE:
	{
		MoveEvent *moveEvent = ActionEvent::cast<MoveEvent>(actionEvt);
		if (moveEvent == nullptr)
			return false;

		const float MOVE_FORCE = 10.0f;
		const float ROT_SCALE = 0.04f;
		const float BRAKE_SCALE = 0.5f;

		this->up = Matrix4::rotate(this->heading, moveEvent->direction.w * ROT_SCALE) * this->up;

		//rotate sideways
		this->heading = Matrix4::rotate(this->up, -moveEvent->direction.x * ROT_SCALE) * this->heading;

		//rotate up and down
		Matrix4 rot = Matrix4::rotate(Vector4::cross(up, heading), -moveEvent->direction.y * ROT_SCALE);
		this->heading = rot * heading;
		this->up = rot * up;

		this->propulsion = moveEvent->direction.z + 1.0f; // [-1,1] -> [0,2]

		return true;
		break;
	}
	case ActionType::SHOOT:
		owner->getEngineInstance()->sendEvent( new SoundEvent( static_cast<int>(Sounds::SHOOT), false, false ) );
		//TODO: create projectile and set it in motion
		break;
	default:
		break;
	}
	return false;
}

void MovingObject::update(float dt){
	BaseObject::update(dt);

	this->position += this->velocity * dt;

	Vector4 acceleration = this->force * (1 / this->mass);
	this->force = -(this->velocity * this->friction);

	this->velocity += acceleration*dt;

	// follow track
	TrackPath *track = owner->getTrackPath();
	this->trackIndex = track->locateIndex(this->position, this->trackIndex);

	const float TRACK_FORCE = 15.0f;
	const float HEADING_FORCE = 15.0f;

	if (this->followTrack) {
		Vector4 trackForce = track->nodes[this->trackIndex].normal * TRACK_FORCE;
		this->applyForce(trackForce);
	}

	if (this->hasPropulsion) {
		// propulsion in heading
		Vector4 headingForce = Vector4::normalize(this->heading) * HEADING_FORCE * propulsion;
		this->applyForce(headingForce);
	}

	// reset propulsion
	this->propulsion = 1.0f;
}

void MovingObject::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(MovingObjectData));
}

void MovingObject::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	MovingObjectData* data = reinterpret_cast<MovingObjectData*>(buffer.getPointer());

	data->up[0] = this->up[0];
	data->up[1] = this->up[1];
	data->up[2] = this->up[2];

	data->heading[0] = this->heading[0];
	data->heading[1] = this->heading[1];
	data->heading[2] = this->heading[2];

	data->position[0] = this->position[0];
	data->position[1] = this->position[1];
	data->position[2] = this->position[2];

	data->velocity[0] = this->velocity[0];
	data->velocity[1] = this->velocity[1];
	data->velocity[2] = this->velocity[2];

	data->force[0] = this->force[0];
	data->force[1] = this->force[1];
	data->force[2] = this->force[2];

	data->friction = friction;
	data->mass = mass;

	data->trackIndex = this->trackIndex;

	buffer.filled();
}

void MovingObject::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const MovingObjectData* data = reinterpret_cast<const MovingObjectData*>(reader.getPointer());

	this->up = Common::Vector(data->up[0], data->up[1], data->up[2]);
	this->heading = Common::Vector(data->heading[0], data->heading[1], data->heading[2]);

	this->position = Common::Point(data->position[0], data->position[1], data->position[2]);
	this->velocity = Common::Vector(data->velocity[0], data->velocity[1], data->velocity[2]);
	this->force = Common::Vector(data->force[0], data->force[1], data->force[2]);

	this->friction = data->friction;
	this->mass = data->mass;
	
	this->trackIndex = data->trackIndex;

	reader.finished(sizeof(MovingObjectData));
}

Vector4 MovingObject::getPosition() {
	return this->position;
}

Vector4 MovingObject::getGroupingParameter() const {
	return Vector(0.0f, 0.0f, (float)this->trackIndex);
}

bool MovingObject::collidesWith(const ICollidable* target) const {
	std::shared_ptr<const Bounds> bounds = target->getBounds();

	if (bounds->type == BoundsType::Sphere) {
		std::cout << "Wall Check" << std::endl;
		std::shared_ptr<const BoundingSphere> bs = std::static_pointer_cast<const BoundingSphere>(bounds);
		std::shared_ptr<const BoundingSphere> me = std::static_pointer_cast<const BoundingSphere>(this->getBounds());

		float distance = (me->radius + bs->radius);
		return ((bs->position - me->position).lengthSquared() <= distance * distance);
	}
	else return false;
}

void MovingObject::handleCollision(std::shared_ptr<const Bounds> bounds, float dt) {
	// play sound for collision, this will probably play twice and needs to be handled :(
	owner->getEngineInstance()->sendEvent( new SoundEvent( static_cast<int>(Sounds::COLLIDE), false, false ) );

	std::shared_ptr<const BoundingSphere> me = std::static_pointer_cast<const BoundingSphere>(this->getBounds());

	if (bounds->type == BoundsType::Sphere) {
		std::shared_ptr<const BoundingSphere> bs = std::static_pointer_cast<const BoundingSphere>(bounds);

		Vector4 n1 = me->velocity * (me->mass - bs->mass);
		Vector4 n2 = bs->velocity * (2 * bs->mass);
		Vector4 numerator = n1 + n2;
		float denominator = me->mass + bs->mass;

		this->velocity = numerator * (1.0f / denominator);
	} else {
		TrackPath *track = Game::getGlobalInstance()->getTrackPath();

		Vector4 trackPos = track->nodes[this->trackIndex].point - this->position;
		Vector4 wallNormal = Vector4::normalize(trackPos);

		float mag = this->velocity.dot(-wallNormal);
		this->velocity += wallNormal * (1.7f * mag);

		//TODO: replace 100 with track radius
		this->position = track->nodes[this->trackIndex].point - (wallNormal * (100.0f - me->radius));
	}
	
}

std::shared_ptr<const Bounds> MovingObject::getBounds() const {
	BoundingSphere* bounds = new BoundingSphere();

	assert(bounds->type == BoundsType::Sphere);
	bounds->position = this->position;
	bounds->velocity = this->velocity;
	bounds->radius = 5.0f;
	bounds->mass = this->mass;

	return shared_ptr<const Bounds>(bounds);
}

unsigned int MovingObject::getPriority() const {
	return static_cast<unsigned int>(CollisionPriorities::Object);
}

void MovingObject::setPosition(const Vector4& pos) {
	this->position = pos;
}