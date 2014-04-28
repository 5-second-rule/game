#pragma once

#include "engine-core\IHasHandle.h"
#include "engine-core\Handle.h"
#include "engine-core\ISerializable.h"
#include "engine-core\IUpdatable.h"
#include "StateMachine.h"
#include "ObjectTypes.h"

struct GameObjectHeader {
	/*	Array of bytes contains tagged data, one after another
	------------------------------------------------------------------------
	| index | id | position[3] | velocity[3] | accleration[3] | force[3]
	------------------------------------------------------------------------
	*/
	int index;
	unsigned int id;
	float position[3];
	float velocity[3];
	float acceleration[3];
	float force[3];
};

class GameObject : public IHasHandle, public ISerializable, public IUpdatable {
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
	void setHandle( Handle handle );
	enum ObjectTypes getObjectType();

	// ISerializable Methods
	virtual void dehydrate( char  *dst, size_t &size, size_t dstSize );
	virtual void rehydrate( char *data );

	// IUpdateable Methods
	virtual void update( int dt );
};