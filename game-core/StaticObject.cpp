#include "StaticObject.h"

#include "ObjectTypes.h"

StaticObject::StaticObject(int objectType) : BaseObject(objectType) {}

StaticObject::~StaticObject() {}

bool StaticObject::handleEvent(Event* evt) {
	return false;
}