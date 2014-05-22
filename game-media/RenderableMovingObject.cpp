#define _USE_MATH_DEFINES
#include "RenderableMovingObject.h"

#include <cmath>

RenderableMovingObject::RenderableMovingObject(int type, Transmission::Model* model)
	: MovingObject(type)
	, RenderableObject(model)
{}


RenderableMovingObject::~RenderableMovingObject() {}

void RenderableMovingObject::render() {
	this->setPosition(this->position.getPointer());
	if (this->heading != Vector4()) {
		// flatten heading into the XZ plane, and rotate that much in y.	
		Vector4 headingXZ = Vector(this->heading.x(), 0.0f, this->heading.z());
		float angle = Vector4::angle(headingXZ, Vector(0, 0, 1)) * (float)(180.0f / M_PI);
		angle *= this->heading.x() / abs(this->heading.x());

		this->setRotation(Vector4(0.0f, angle, 0.0f));
	}
	RenderableObject::render();
}