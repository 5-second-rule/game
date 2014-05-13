#pragma once

#include "game-core.h"

class GAMECOREDLL RigidBody
{
public:
	Vector4 m_position;
	Vector4 m_heading;
	Vector4 m_side;
	Vector4 m_top;
	float m_mass;
	RigidBody();
	~RigidBody();
	string toString();
};

