#pragma once
#include "game-core.h"
#include "..\..\engine\Common\4D\Vector4.h"
#include "..\..\engine\Common\4D\Matrix4.h"

using namespace Utility;
class GAMECOREDLL Transformation
{
public:
	Transformation();
	~Transformation();

	//--------------------- PointToWorldSpace --------------------------------
	//
	//  Transforms a point from the agent's local space into world space
	//------------------------------------------------------------------------
	static Vector4 pointToWorldSpace(const Vector4 &point,
		const Vector4 &agent_heading,
		const Vector4 &agend_side,
		const Vector4 &agend_top,
		const Vector4 &agent_position);

	static float **rotationMatrix(const Vector4 &i,
		const Vector4 &j,
		const Vector4 &k);
};