#include "Transformation.h"

Transformation::Transformation()
{
}


Transformation::~Transformation()
{
}

Vector4 Transformation::pointToWorldSpace(const Vector4 &point,
	const Vector4 &agent_front,
	const Vector4 &agent_side,
	const Vector4 &agent_top,
	const Vector4 &agent_position){
	Vector4 tmp(point);
	tmp.set(3, 1);

	Matrix4 matTransformation = Matrix4::identity();
	matTransformation = matTransformation * rotationMatrix(agent_front, agent_side, agent_top);
	matTransformation = matTransformation * translationMatrix(agent_position);
	return matTransformation.multiply(tmp);
}

Matrix4 Transformation::rotationMatrix(const Vector4 &i,
	const Vector4 &j,
	const Vector4 &k){
	float m[4][4] = { { 0 } };

	m[0][0] = i.x(); m[0][1] = j.x(); m[0][2] = k.x(); m[0][3] = 0;
	m[1][0] = i.y(); m[1][1] = j.y(); m[1][2] = k.y(); m[1][3] = 0;
	m[2][0] = i.z(); m[2][1] = j.z(); m[2][2] = k.z(); m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

	return Matrix4(m);
}

Matrix4 Transformation::translationMatrix(const Vector4 &origin){
	float m[4][4] = { { 0 } };

	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	m[0][3] = -origin[0];
	m[1][3] = -origin[1];
	m[2][3] = -origin[2];

	return Matrix4(m);
}

