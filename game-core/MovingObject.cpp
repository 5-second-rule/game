#include "MovingObject.h"

using namespace std;
using namespace Common;

MovingObject::MovingObject(int objectType) : BaseObject(objectType)
{
	assert(ConfigSettings::config->getValue("default_drag_coefficient", drag_coefficient));
	assert(ConfigSettings::config->getValue("default_max_speed", max_speed));
	assert(ConfigSettings::config->getValue("default_max_force", max_force));
	assert(ConfigSettings::config->getValue("default_mass", mass));

	state_machine = new StateMachine<MovingObject>(this);
	state_machine->setCurrentState(Move::instance());
}

MovingObject::~MovingObject() {}

void MovingObject::applyForce(Vector4 &force){
	tick_force += force;
}

bool MovingObject::handleEvent(Event* evt){
	if (state_machine->handleEvent(evt))
		return true;
	return false;
}

void MovingObject::update(float dt){
	state_machine->update();

	// Update de physics
	force -= velocity * drag_coefficient;
	force += tick_force;
	Vector4 acceleration = force * (1 / this->mass);
	velocity += acceleration*dt;
	this->position += velocity * dt;

	if (velocity.length() > 0.00001){
		// Update the object local space base
		heading = velocity;
		side = Vector4::perp(heading);
		top = Vector4::cross(heading, side);

		heading.normalize();
		side.normalize();
		top.normalize();
}

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

	buffer.filled();

}

void MovingObject::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const MovingObjectData* data = reinterpret_cast<const MovingObjectData*>(reader.getPointer());

	this->position = Common::Point(data->position[0], data->position[1], data->position[2]);
	this->velocity = Common::Vector(data->velocity[0], data->velocity[1], data->velocity[2]);
	this->force = Common::Vector(data->force[0], data->force[1], data->force[2]);

	this->drag_coefficient = data->drag_coefficient;
	this->mass = data->mass;

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

Vector4 MovingObject::getFront(){
	// TODO
	return Vector4(0, 0, 1);
	//return heading;
}

Vector4 MovingObject::getTop(){
	// TODO
	return Vector4(0, 1, 0);
	//return top;
}

Vector4 MovingObject::getSide(){
	// TODO
	return Vector4(1, 0, 0);
	//return side;
}

Vector4 MovingObject::getPosition(){
	return position;
}

Vector4 MovingObject::getVelocity(){
	return velocity;
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

float MovingObject::speed(){
	return velocity.length();
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