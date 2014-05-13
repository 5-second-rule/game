#pragma once
#include "game-core.h"

class GAMECOREDLL Transformation
{
public:
	Transformation();
	~Transformation();

	//--------------------- PointToWorldSpace --------------------------------
	//
	//  Transforms a point from the agent's local space into world space
	//------------------------------------------------------------------------
	static Vector4 pointToWorldSpace(Vector4 &point,
		Vector4 &agent_side,
		Vector4 &agend_top,
		Vector4 &agend_heading,
		Vector4 &agent_position);

	//--------------------- vectorToWorldSpace --------------------------------
	//
	//  Transforms a vector from the agent's local space into world space
	//------------------------------------------------------------------------
	static Vector4 vectorToWorldSpace(Vector4 &vec,
		Vector4 &AgentSide,
		Vector4 &AgentTop,
		Vector4 &AgentHeading);

	//--------------------- pointToLocalSpace --------------------------------
	//
	//  Transforms a point into world space to agent's local space
	//------------------------------------------------------------------------
	static Vector4 pointToLocalSpace(Vector4 &point,
		Vector4 &agent_side,
		Vector4 &agend_top,
		Vector4 &agend_heading,
		Vector4 &agent_position);

	//--------------------- VectorToLocalSpace --------------------------------
	//
	//------------------------------------------------------------------------
	static Vector4 vectorToLocalSpace(Vector4 &vec,
		Vector4 &AgentSide,
		Vector4 &AgentTop,
		Vector4 &AgentHeading);
};