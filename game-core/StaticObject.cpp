#include "StaticObject.h"

#include "ObjectTypes.h"

StaticObject::StaticObject(int objectType) : BaseObject(objectType) {}

StaticObject::~StaticObject() {}

bool StaticObject::handleEvent(Event* evt) {
	return false;
}

Common::Vector4* StaticObject::getGroupingParameter() {
	return nullptr;
}

bool StaticObject::collidesWith(ICollidable* target) {
	return false;
}

void StaticObject::handleCollision(BoundingSphere bs, float dt) {}

BoundingSphere StaticObject::getBounds() {
	return{ Common::Vector4(), Common::Vector4(), 0, 99999999999.0f };
}

unsigned int StaticObject::getPriority() {
	return static_cast<unsigned int>(CollisionPriorities::Track);
}