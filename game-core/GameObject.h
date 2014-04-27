#include "engine-core\IHasHandle.h"
#include "engine-core\Handle.h"
#include "StateMachine.h"
#include "ObjectTypes.h"

#pragma once
class GameObject : public IHasHandle
{
private:
	int m_uniqueId;
	int m_handleIndex;
	Handle m_handle;
	enum ObjectTypes m_objectType;
	StateMachine< GameObject > *m_stateMachine;

	float m_position[3];
	float m_velocity[3];
	float m_acceleration[3];
	float m_force[3];

public:
	GameObject();
	virtual ~GameObject();
	Handle getHandle();
	void setHandle(Handle handle);
	enum ObjectTypes getObjectType();
};