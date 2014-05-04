#include <iostream>

#include "MovingObject.h"

using namespace std;
MovingObject::MovingObject()
{
	Utility::configInstance()->getValue("default_friction", m_friction);
	Utility::configInstance()->getValue("default_max_speed", m_max_speed);
	Utility::configInstance()->getValue("default_max_force", m_max_force);

	stateMachine = new StateMachine<MovingObject>(this);
	stateMachine->SetCurrentState(Move::instance());
}


MovingObject::~MovingObject()
{
}


Vector4 MovingObject::heading(){
	return normalize(m_velocity);
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

bool MovingObject::onMessage(Event* evt){
	if (stateMachine->HandleMessage(*evt))
		return true;
	return GameObject::onMessage(evt);
}

void MovingObject::update(float dt){
	Vector4 acceleration;
	m_body->m_position += m_velocity * dt;
	acceleration = m_force * (1 / m_body->m_mass);
	m_force = -m_velocity * m_friction;
	m_velocity += acceleration*dt;
}

void MovingObject::print(){
	cout << "Position: " << m_body->m_position.toString() << endl;
	cout << "Speed: " << m_velocity.length() << endl;
	cout << "Force: " << m_force.toString() << endl;
}