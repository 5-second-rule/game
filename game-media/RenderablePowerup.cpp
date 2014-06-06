#include "RenderablePowerup.h"

#include "game-core\ObjectTypes.h"

RenderablePowerup::RenderablePowerup(int type, Transmission::Model* model)
	: Powerup(type)
	, RenderableObject(model)
{
	if (type == ObjectTypes::Adrenaline && model != nullptr) {
		this->getMoveable()->setScale(4);
	}
}

RenderablePowerup::~RenderablePowerup()
{
}

void RenderablePowerup::render() {
	IMoveable* move = this->getMoveable();
	move->setPosition(this->position);
	move->setRotation(this->rotation[0], this->rotation[1], this->rotation[2]);

	if (this->timeToLiveAgain <= 0) {
		RenderableObject::render();
	}
}
