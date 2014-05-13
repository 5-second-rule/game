#include "RigidBody.h"
#include <cassert>

RigidBody::RigidBody()
{
	assert(ConfigSettings::configInstance()->getValue("default_mass", m_mass));
}


RigidBody::~RigidBody()
{
}

string RigidBody::toString(){
	stringstream buffer;
	buffer << "Position: " << m_position.toString() << endl;
	buffer << "Heading: " << m_heading.toString() << endl;
	buffer << "Side: " << m_side.toString() << endl;
	buffer << "Top: " << m_top.toString();
	return buffer.str();
}
