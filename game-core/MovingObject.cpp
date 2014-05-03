#include <iostream>

#include "MovingObject.h"

using namespace std;
MovingObject::MovingObject()
{
	Utility::configInstance()->getValue("default_friction", m_friction);
	Utility::configInstance()->getValue("default_max_speed", m_max_speed);
	Utility::configInstance()->getValue("default_max_force", m_max_force);
}


MovingObject::~MovingObject()
{
}


Vector4 MovingObject::heading(){
	return normalize(m_velocity);
}

float MovingObject::speed(){
	return m_velocity.length();
}

bool MovingObject::onEvent(Event event){
	
	return GameObject::onEvent(event);
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