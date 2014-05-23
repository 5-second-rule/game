#include "MovingObject.h"

#include "MoveEvent.h"
#include "ActionType.h"

#include "ObjectTypes.h"

#include "Game.h"

MovingObject::MovingObject(int objectType) : BaseObject(objectType)
{
	this->up = Vector(0.0f, 1.0f, 0.0f);
	this->heading = Vector(0.0f, 0.0f, 1.0f);
	this->trackIndex = 0;
	this->followTrack = true;
	this->trackVelocity = 1000;
	assert(ConfigSettings::config->getValue("default_drag_coefficient", drag_coefficient));
	assert(ConfigSettings::config->getValue("default_max_speed", max_speed));
	assert(ConfigSettings::config->getValue("default_max_force", max_force));
	assert(ConfigSettings::config->getValue("default_mass", mass));

	state_machine = new StateMachine<MovingObject>(this);
	state_machine->setCurrentState(Move::instance());
}

MovingObject::~MovingObject() {}

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

		const float MOVE_FORCE = 5.0f;
		const float ROT_SCALE = 0.05f;

		//rotate sideways
		this->heading = Matrix4::rotate(this->up, moveEvent->direction.x * ROT_SCALE) * heading;

		//rotate up and down
		Matrix4 rot = Matrix4::rotate(Vector4::cross(up, heading), moveEvent->direction.z * ROT_SCALE);
		this->heading = rot * heading;
		this->up = rot * up;

		this->force = heading * moveEvent->direction.y * MOVE_FORCE;

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
	state_machine->update();

	if (followTrack) {
		TrackPath *track = Game::getGlobalInstance()->getTrackPath();
		this->trackIndex = track->locateIndex(this->position, this->trackIndex);

		const float TRACK_FORCE = 20.0f;
		Vector4 force = track->nodes[this->trackIndex].normal * TRACK_FORCE;
		this->applyForce(force);
	}

	// Update de physics
	force -= velocity * drag_coefficient;
	force += tick_force;
	Vector4 acceleration = force * (1 / this->mass);
	velocity += acceleration*dt;
	this->position += velocity * dt;

	// Reset the forces to the next update
	force.set(0, 0, 0, 0);
	tick_force.set(0, 0, 0, 0);
	BaseObject::update(dt);
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

	data->drag_coefficient = drag_coefficient;
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

	this->drag_coefficient = data->drag_coefficient;
	this->mass = data->mass;

	this->trackIndex = data->trackIndex;

	reader.finished(sizeof(MovingObjectData));
}

void MovingObject::setPos(float x, float y, float z){
	position.set(0, x);
	position.set(1, y);
	position.set(2, z);
}

void MovingObject::setDragCoeff(float p_drag_coefficient){
	drag_coefficient = p_drag_coefficient;
}

void MovingObject::setMaxSpeed(float p_max_speed){
	max_speed = p_max_speed;
}

void MovingObject::setMaxForce(float p_max_force){
	max_force = p_max_force;
}

void MovingObject::setTickForce(float x, float y, float z){
	tick_force.set(x, y, z, 0);
}

void MovingObject::setForce(float x, float y, float z){
	force.set(x, y, z, 0);
}

void MovingObject::setTag(bool tag){
	this->tagged = tag;
}

Vector4 MovingObject::getHeading(){
	return Vector4::normalize(this->velocity);
}

Vector4 MovingObject::getPosition(){
	return position;
}

Vector4 MovingObject::getVelocity(){
	return velocity;
}

float MovingObject::speed(){
	return this->velocity.length();
}

float MovingObject::getMaxForce(){
	return max_force;
}

float MovingObject::getMaxSpeed(){
	return max_speed;
}

bool MovingObject::isTagged(){
	return tagged;
}

string MovingObject::toString(){
	stringstream buffer;
	buffer << this->getHandle().toString() << endl;
	buffer << "Speed: " << velocity.length() << endl;
	buffer << "Force: " << force.toString();
	return buffer.str();
}

void MovingObject::print(){
	cout << toString();
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