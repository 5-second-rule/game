#include "RenderablePowerup.h"


RenderablePowerup::RenderablePowerup(int type, Transmission::Model* model)
	: Powerup(type)
	, RenderableObject(model)
{
}

RenderablePowerup::~RenderablePowerup()
{
}

void RenderablePowerup::render() {
	IMoveable* move = this->getMoveable();
	move->setPosition(this->position);
	move->setRotation(this->rotation[0], this->rotation[1], this->rotation[2]);

	RenderableObject::render();
}
