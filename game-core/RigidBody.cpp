#include "RigidBody.h"
#include <cassert>

RigidBody::RigidBody()
{
	assert(Utility::configInstance()->getValue("default_mass", m_mass));
}


RigidBody::~RigidBody()
{
}
