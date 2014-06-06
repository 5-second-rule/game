#define _USE_MATH_DEFINES
#include "RenderablePlayerMovingObject.h"
#include "game-core\ObjectTypes.h"

#include <cmath>

RenderablePlayerMovingObject::RenderablePlayerMovingObject(int type, Transmission::Model* model)
: PlayerMovingObject(type, nullptr)
, RenderableObject(model)
{
	if (model != nullptr)
	{
		if (type == ObjectTypes::ChickenPox && model != nullptr) {
			this->getMoveable()->setScale(4.5);
		}
		if (type == ObjectTypes::Ecoli && model != nullptr) {
			this->getMoveable()->setScale(1.5);
		}
		if (type == ObjectTypes::Malaria && model != nullptr) {
			this->getMoveable()->setScale(1.5);
		}
		if (type == ObjectTypes::Syphillis && model != nullptr) {
			this->getMoveable()->setScale(1.5);
		}
	}
}


RenderablePlayerMovingObject::~RenderablePlayerMovingObject() {}

void RenderablePlayerMovingObject::render() {
	if (!this->dead)
	{
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
}