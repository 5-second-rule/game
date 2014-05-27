#define _USE_MATH_DEFINES
#include "RenderableMovingObject.h"

#include <cmath>

RenderableMovingObject::RenderableMovingObject(int type, Transmission::Model* model)
	: MovingObject(type)
	, RenderableObject(model)
{}


RenderableMovingObject::~RenderableMovingObject() {}

void RenderableMovingObject::render() {

	IMoveable* move = this->getMoveable();
	move->setPosition(this->position);

	if (this->heading != Vector4() && this->heading != Vector(0.0f, 0.0f, -1.0f)) {

		// reset rotation
		move->setRotation(0, 0, 0);

		// rotate the z vector to face the new heading
		move->rotate(
			Vector4::cross(this->heading, Vector(0.0f, 0.0f, -1.0f)),
			Vector4::angle(this->heading, Vector(0.0f, 0.0f, -1.0f))
		);

		// calculate where Y is now pointing
		Vector4 newY = move->getRotation() * Vector(0.0f, 1.0f, 0.0f);
		if (newY != up) {
			move->rotate(
				Vector4::cross(up, newY),
				Vector4::angle(up, newY)
			);
		}

	}
	RenderableObject::render();
}