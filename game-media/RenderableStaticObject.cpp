#include "RenderableStaticObject.h"

RenderableStaticObject::RenderableStaticObject() 
  : StaticObject(-1), 
  RenderableObject(nullptr)
{}

RenderableStaticObject::RenderableStaticObject(int type, Transmission::Model* model)
	: StaticObject(type),
	RenderableObject(model)
{}
>>>>>>> master


RenderableStaticObject::~RenderableStaticObject() {}
