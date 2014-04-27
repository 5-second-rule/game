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
