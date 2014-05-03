#pragma once

#include "game-core.h"
#include "..\..\engine\Common\4D\Vector4.h"
#include "..\..\engine\engine-core\ConfigSettings.h"

using namespace Utility;
class GAMECOREDLL RigidBody
{
public:
	Vector4 m_position;
	float m_mass;
	RigidBody();
	~RigidBody();
};

