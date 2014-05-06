#include <iostream>

#include "MovingObject.h"

using namespace std;
MovingObject::MovingObject(int objectType) : PhysicsObject(objectType)
{
	assert(Utility::configInstance()->getValue("default_friction", m_friction));
	assert(Utility::configInstance()->getValue("default_max_speed", m_max_speed));
	assert(Utility::configInstance()->getValue("default_max_force", m_max_force));

	state_machine = new StateMachine<MovingObject>(this);
	steering_behavior = new SteeringBehavior(this);
	steering_behavior->wanderOn();
	state_machine->SetCurrentState(Move::instance());
}


MovingObject::~MovingObject()
{
}


Vector4 MovingObject::heading(){
	return normalize(m_velocity);
}

Vector4 MovingObject::front(){
	return Vector4(1, 0, 0);
}

Vector4 MovingObject::top(){
	return Vector4(0, 0, 1);
}

Vector4 MovingObject::side(){
	return Vector4(0, 1, 0);
}

float MovingObject::speed(){
	return m_velocity.length();
}

void MovingObject::applyForce(Vector4 force){
	m_force += force;
}

bool MovingObject::handleEvent(Event* evt){
	if (state_machine->handleEvent(evt))
		return true;
	return PhysicsObject::handleEvent(evt);
}

void MovingObject::update(float dt){
	PhysicsObject::update(dt);
	Vector4 acceleration;
	m_body->m_position += m_velocity * dt;
	acceleration = m_force * (1 / m_body->m_mass);
	m_force = steering_behavior->calculate() - m_velocity * m_friction;
	m_velocity += acceleration*dt;
	position[0] = m_body->m_position.get(0);
	position[1] = m_body->m_position.get(1);
	position[2] = m_body->m_position.get(2);

}

void MovingObject::print(){
	cout << "Position: " << m_body->m_position.toString() << endl;
	cout << "Speed: " << m_velocity.length() << endl;
	cout << "Force: " << m_force.toString() << endl;
}