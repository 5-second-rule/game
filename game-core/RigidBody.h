#pragma once

#include "game-core.h"
#include "../../common/common/4D/Matrix4.h"
#include "../../engine/engine-core/ConfigSettings.h"

using namespace Common;
class GAMECOREDLL RigidBody
{
public:
	Vector4 m_position;
	float m_mass;
	RigidBody();
	~RigidBody();
};

