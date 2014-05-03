#include "RigidBody.h"


RigidBody::RigidBody()
{
	Utility::configInstance()->getValue("default_mass", m_mass);
	m_position.set(0, 0, 0);
}


RigidBody::~RigidBody()
{
}
