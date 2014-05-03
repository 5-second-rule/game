#pragma once

#include "game-core.h"
#include "..\..\engine\Common\4D\Vector4.h"

using namespace Utility;
class GAMECOREDLL RigidBody
{
public:
	Vector4 position;
	double mass;
	RigidBody();
	~RigidBody();
};

