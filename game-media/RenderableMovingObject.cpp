#include "RenderableMovingObject.h"


RenderableMovingObject::RenderableMovingObject(int type, Transmission::Model* model)
	: MovingObject(type)
	, RenderableObject(model)
{}


RenderableMovingObject::~RenderableMovingObject() {}

void RenderableMovingObject::render() {
	this->setPosition(this->position.getPointer());
	RenderableObject::render();
}