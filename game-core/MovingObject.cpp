#include <iostream>

#include "MovingObject.h"

using namespace std;
MovingObject::MovingObject(int objectType) : GameObject(objectType)
{
	assert(ConfigSettings::configInstance()->getValue("default_drag_coefficient", m_drag_coefficient));
	assert(ConfigSettings::configInstance()->getValue("default_max_speed", m_max_speed));
	assert(ConfigSettings::configInstance()->getValue("default_max_force", m_max_force));

	m_state_machine = new StateMachine<MovingObject>(this);
	m_state_machine->SetCurrentState(Move::instance());

	m_path = Path::instance();
	setCurrentWayPoint(m_path->begin());
	m_path->loopOn();
	m_path->print();
	createAI();
	m_steering_behavior->followPathOn();
	//m_steering_behavior->wanderOn();
}


MovingObject::~MovingObject()
{
}


Vector4 MovingObject::heading(){
	return Common::Vector4::normalize(m_velocity);
}

Vector4 MovingObject::front(){
	return Vector4(0, 0, 1);
	//return m_body->m_heading;
}

Vector4 MovingObject::top(){
	return Vector4(0, 1, 0);
	//return m_body->m_top;
}

Vector4 MovingObject::side(){
	return Vector4(1, 0, 0);
	//return m_body->m_side;
}

float MovingObject::speed(){
	return m_velocity.length();
}

void MovingObject::applyForce(Vector4 &force){
	m_tick_force += force;
}

bool MovingObject::handleEvent(Event* evt){
	if (m_state_machine->handleEvent(evt))
		return true;
	return GameObject::handleEvent(evt);
}

void MovingObject::update(float dt){
	Vector4 acceleration;

	if (m_steering_behavior)
		m_force += m_steering_behavior->calculate();
	m_force -= m_velocity * m_drag_coefficient;
	m_force += m_tick_force;
	acceleration = m_force * (1 / m_body->m_mass);
	m_velocity += acceleration*dt;
	m_body->m_position += m_velocity * dt;

	position[0] = m_body->m_position.get(0);
	position[1] = m_body->m_position.get(1);
	position[2] = m_body->m_position.get(2);

	if (m_velocity.length() > 0.00001){
		m_body->m_heading = m_velocity;
		m_body->m_side = Vector4::perp(m_body->m_heading);
		m_body->m_top = Vector4::cross(m_body->m_heading, m_body->m_side);

		m_body->m_heading.normalize();
		m_body->m_side.normalize();
		m_body->m_top.normalize();
	}

	// Reset the forces to the next update
	m_force.set(0, 0, 0, 0);
	m_tick_force.set(0, 0, 0, 0);
	GameObject::update(dt);
}

string MovingObject::toString(){
	stringstream buffer;
	buffer << GameObject::toString() << endl;
	buffer << "Speed: " << m_velocity.length() << endl;
	buffer << "Force: " << m_force.toString();
	return buffer.str();
}

void MovingObject::print(){
	cout << toString();
}

void MovingObject::createAI(){
	m_steering_behavior = new SteeringBehavior(this);
}

void MovingObject::setDragCoeff(float p_drag_coefficient){
	m_drag_coefficient = p_drag_coefficient;
}

void MovingObject::setMaxSpeed(float p_max_speed){
	m_max_speed = p_max_speed;
}

void MovingObject::setMaxForce(float p_max_force){
	m_max_force = p_max_force;
}

void MovingObject::setPursuit(Handle *pray){
	if (m_steering_behavior == nullptr)
		createAI();
	m_steering_behavior->pursuitOn(pray);
}

void MovingObject::setEvade(Handle *predator){
	if (m_steering_behavior == nullptr)
		createAI();
	m_steering_behavior->pursuitOn(predator);
}

void MovingObject::setOnSteeringBehavior(BehaviorType behavior){
	if (m_steering_behavior == nullptr)
		createAI();
	if (behavior == BehaviorType::arrive)
		m_steering_behavior->arriveOn();
	else if (behavior == BehaviorType::flee)
		m_steering_behavior->fleeOn();
	else if (behavior == BehaviorType::seek)
		m_steering_behavior->seekOn();
	else if (behavior == BehaviorType::wander)
		m_steering_behavior->wanderOn();
}

void MovingObject::setOffSteeringBehavior(BehaviorType behavior){
	if (m_steering_behavior == nullptr)
		createAI();
	if (behavior == BehaviorType::arrive)
		m_steering_behavior->arriveOff();
	else if (behavior == BehaviorType::flee)
		m_steering_behavior->fleeOff();
	else if (behavior == BehaviorType::seek)
		m_steering_behavior->seekOff();
	else if (behavior == BehaviorType::wander)
		m_steering_behavior->wanderOff();
}

WayPoint MovingObject::getCurrentWayPoint(){
	return m_current_way_point;
}

void MovingObject::setCurrentWayPoint(WayPoint p){
	m_current_way_point = p;
}

void MovingObject::setNextWayPoint(){
	cout << "changed";
	m_path->setNextWayPoint(this);
}