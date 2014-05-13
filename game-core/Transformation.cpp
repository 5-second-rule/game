#include "Transformation.h"

Transformation::Transformation()
{
}


Transformation::~Transformation()
{
}

Vector4 Transformation::pointToWorldSpace(Vector4 &point,
	Vector4 &agent_side,
	Vector4 &agent_top,
	Vector4 &agent_heading,
	Vector4 &agent_position){

	point.set(3, 1);
	agent_side.set(3, 0);
	agent_top.set(3, 0);
	agent_heading.set(3, 0);
	agent_position.set(3, 1);
	
	Matrix4 matTransformation(agent_side, agent_top, agent_heading, agent_position);
	return matTransformation.multiply(point);
}

Vector4 Transformation::vectorToWorldSpace(Vector4 &vec,
	Vector4 &agent_heading,
	Vector4 &agent_side,
	Vector4 &agent_top)
{
	vec.set(3, 1);
	agent_heading.set(3, 0);
	agent_side.set(3, 0);
	agent_top.set(3, 0);

	// rotation
	Matrix4 rotationMatrix;
	rotationMatrix.setLines(agent_side, agent_top, agent_heading, Vector4(0, 0, 0, 1));
	return rotationMatrix.multiply(vec);
}

Vector4 Transformation::pointToLocalSpace(Vector4 &point,
	Vector4 &agent_heading,
	Vector4 &agent_side,
	Vector4 &agent_top,
	Vector4 &agent_position){

	point.set(3, 1);
	agent_heading.set(3, 0);
	agent_side.set(3, 0);
	agent_top.set(3, 0);
	agent_position.set(3, 1);

	Matrix4 matTransformation(agent_side, agent_top, agent_heading, -agent_position);
	return matTransformation.multiply(point);
}

Vector4 Transformation::vectorToLocalSpace(Vector4 &vec,
	Vector4 &agent_heading,
	Vector4 &agent_side,
	Vector4 &agent_top)
{
	vec.set(3, 0);
	agent_heading.set(3, 0);
	agent_side.set(3, 0);
	agent_top.set(3, 0);

	// rotation
	Matrix4 rotationMatrix(agent_side, agent_top, agent_heading, Vector4(0, 0, 0, 1));
	return rotationMatrix.multiply(vec);
}
