#include "RigidBody.h"


RigidBody::RigidBody()
{
	Utility::configInstance()->getValue("default_mass", m_mass);
}


RigidBody::~RigidBody()
{
}
