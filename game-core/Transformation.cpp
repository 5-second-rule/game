#include "Transformation.h"

Transformation::Transformation()
{
}


Transformation::~Transformation()
{
}

Vector4 Transformation::pointToWorldSpace(const Vector4 &point,
	const Vector4 &agent_heading,
	const Vector4 &agent_side,
	const Vector4 &agent_top,
	const Vector4 &agent_position){
	Matrix4 matTransformation;
	float **m = rotationMatrix(agent_heading, agent_side, agent_top);
	m[3][0] = point.x(); m[3][1] = point.y(); m[3][2] = point.z();

	for (int i = 0; i < 4; ++i)
	for (int j = 0; j < 4; ++j)
		matTransformation.set(i, j, m[i][j]);

	return matTransformation.multiply(point);
}

float **Transformation::rotationMatrix(const Vector4 &i,
	const Vector4 &j,
	const Vector4 &k){
	float **m = new float*[4];
	for (int a = 0; a < 4; ++a)
		m[a] = new float[4];
	m[0][0] = i.x(); m[0][1] = i.y(); m[0][2] = i.z(); m[0][3] = 0;
	m[0][0] = j.x(); m[0][1] = j.y(); m[0][2] = j.z(); m[0][3] = 0;
	m[0][0] = k.x(); m[0][1] = k.y(); m[0][2] = k.z(); m[0][3] = 0;
	m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 1;

	return m;
}

