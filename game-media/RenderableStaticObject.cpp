#include "RenderableStaticObject.h"

RenderableStaticObject::RenderableStaticObject(int type, Transmission::Model* model)
	: StaticObject(type),
	RenderableObject(model)
{}

RenderableStaticObject::~RenderableStaticObject() {}
