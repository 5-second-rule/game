#include "MovingObject.h"


MovingObject::MovingObject()
{
}


MovingObject::~MovingObject()
{
}


Vector4 MovingObject::heading(){
	return normalize(m_velocity);
}

float MovingObject::speed(){
	return m_velocity.length();
}