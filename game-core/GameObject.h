#include "engine-core\IHasHandle.h"
#include "engine-core\Handle.h"
#include "StateMachine.h"

#pragma once
class GameObject : public IHasHandle
{
private:
	int m_uniqueId;
	int m_handleIndex;
	Handle m_handle;
	StateMachine< GameObject > *m_stateMachine;

public:
	GameObject();
	virtual ~GameObject();
	Handle getHandle();
	void setHandle(Handle handle);
};