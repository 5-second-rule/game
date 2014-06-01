#include "StaticObject.h"

#include "ObjectTypes.h"

StaticObject::StaticObject(int objectType) : BaseObject(objectType) {}

StaticObject::~StaticObject() {}

std::string StaticObject::toString() {
	return	BaseObject::toString() + "\r\nType: " + std::to_string(this->getType());
}

bool StaticObject::handleEvent(Event* evt) {
	return false;
}