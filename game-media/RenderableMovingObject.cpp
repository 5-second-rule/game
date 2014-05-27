#define _USE_MATH_DEFINES
#include "RenderableMovingObject.h"

#include <cmath>

RenderableMovingObject::RenderableMovingObject(int type, Transmission::Model* model)
	: MovingObject(type, nullptr)
	, RenderableObject(model)
{}


RenderableMovingObject::~RenderableMovingObject() {}

void RenderableMovingObject::render() {
	this->setPosition(this->position.getPointer());
	if (this->heading != Vector4()) {
		// flatten heading into the XZ plane, and rotate that much in y. (top down)	
		Vector4 headingXZ = Vector(this->heading.x(), 0.0f, this->heading.z());
		float yangle = Vector4::angle(headingXZ, Vector(0, 0, -1)) * (float)(180.0f / M_PI);

		if (this->heading.x() != 0) {
			yangle *= this->heading.x() / abs(this->heading.x());
		}

		/*
		// flatten heading into the YZ plan, and rotate that much in x. (from side)
		Vector4 headingYZ = Vector(0.0f, this->heading.y(), this->heading.z());
		float xangle = Vector4::angle(headingYZ, Vector(0, 0, -1)) * (float) (180.0f / M_PI);
		if (this->heading.y() != 0) {
			xangle *= this->heading.y() / abs(this->heading.y());
		}
		*/

		this->setRotation(Vector4(0.0f, -yangle, 0.0f));
	}
	RenderableObject::render();
}