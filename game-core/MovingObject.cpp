#include "MovingObject.h"

#include "MoveEvent.h"
#include "ActionType.h"

#include "ObjectTypes.h"

#define MAX_SPEED 100
#define MAX_FORCE 100

const float MovingObject::max_speed = MAX_SPEED;
const float MovingObject::max_force = MAX_FORCE;

MovingObject::MovingObject(int objectType)
	: BaseObject(objectType)
{
	this->mass = .1f;
	this->friction = .1f;
}


MovingObject::~MovingObject() {}


Vector4 MovingObject::heading(){
	return Vector4::normalize(this->velocity);
}

float MovingObject::speed(){
	return this->velocity.length();
}

void MovingObject::applyForce(const Vector4& force){
	this->force += force;
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

		Vector4 force(moveEvent->direction.x * MOVE_FORCE,
			moveEvent->direction.y * MOVE_FORCE,
			moveEvent->direction.z * MOVE_FORCE
			);

		this->applyForce(force);
		return true;
		break;
	}
	case ActionType::SHOOT:
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

	Vector4 acceleration = force * (1 / this->mass);
	this->force = -(this->velocity * this->friction);

	this->velocity += acceleration*dt;

}

void MovingObject::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(MovingObjectData));
}

void MovingObject::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	MovingObjectData* data = reinterpret_cast<MovingObjectData*>(buffer.getPointer());

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

	buffer.filled();
}

void MovingObject::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const MovingObjectData* data = reinterpret_cast<const MovingObjectData*>(reader.getPointer());

	this->position = Common::Point(data->position[0], data->position[1], data->position[2]);
	this->velocity = Common::Vector(data->velocity[0], data->velocity[1], data->velocity[2]);
	this->force = Common::Vector(data->force[0], data->force[1], data->force[2]);

	this->friction = data->friction;
	this->mass = data->mass;

	reader.finished(sizeof(MovingObjectData));
}

Vector4 MovingObject::getPosition() {
	return this->position;
}

Vector4* MovingObject::getGroupingParameter() {
	return &this->position;
}

bool MovingObject::collidesWith(ICollidable* target) {
	BoundingSphere bs = target->getBounds();
	BoundingSphere me = this->getBounds();

	float distance = (me.radius + bs.radius);
	return ((bs.position - me.position).lengthSquared() <= distance * distance);
}

void MovingObject::handleCollision(BoundingSphere bs, float dt) {
	BoundingSphere me = this->getBounds();

	//Vector4 direction = me.position - bs.position;
	//float distance = bs.radius + me.radius - direction.length();

	//v1 = (u1 * (m1-m2) + 2 * m2 * u2 ) / (m1 + m2)


	Vector4 n1 = me.velocity * (me.mass - bs.mass);
	Vector4 n2 = bs.velocity * (2 * bs.mass);
	Vector4 numerator = n1 + n2;
	float denominator = me.mass + bs.mass;

	this->velocity = numerator * (1.0f / denominator);

	
}

BoundingSphere MovingObject::getBounds() {
	return{ this->position, this->velocity, 6.0f, this->mass };
}

unsigned int MovingObject::getPriority() {
	return static_cast<unsigned int>(CollisionPriorities::Object);
}