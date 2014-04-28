#include <cstring>

#include "GameObject.h"

GameObject::GameObject(){
	m_stateMachine = new StateMachine< GameObject >(this);
}

GameObject::~GameObject(){

}

Handle GameObject::getHandle(){
	return Handle();
}

void GameObject::setHandle(Handle p_handle){
	m_handle = p_handle;
}

enum ObjectTypes GameObject::getObjectType()
{
	return m_objectType;
}


void GameObject::dehydrate( char *dst, size_t &size, size_t dstSize ) {
	
	//TODO throw exception
	if( dstSize < sizeof( struct GameObjectHeader ) )
		return;

	struct GameObjectHeader *hdr = reinterpret_cast<struct GameObjectHeader *>(dst);

	hdr->index = m_handle.index;
	hdr->id = m_handle.id;
	memcpy( hdr->position, m_position, sizeof( float ) * 3 );
	memcpy( hdr->velocity, m_velocity, sizeof( float ) * 3 );
	memcpy( hdr->acceleration, m_acceleration, sizeof( float ) * 3 );
	memcpy( hdr->force, m_force, sizeof( float ) * 3 );

	size = sizeof( struct GameObjectHeader );
}

void GameObject::rehydrate( char *data ) {}

void GameObject::update( int dt ) {}