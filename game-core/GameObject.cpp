#include "GameObject.h"


GameObject::GameObject() : BaseObject(0)
{
	m_body = new RigidBody();
	world = nullptr;
}


GameObject::~GameObject()
{
}
