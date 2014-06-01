#include "Tube.h"

#include "ObjectTypes.h"
#include "Game.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

Tube::Tube() : StaticObject(ObjectTypes::Track) {}

Tube::~Tube() {}

Common::Vector4 Tube::getGroupingParameter() const {
	return Common::Vector4();
}

bool Tube::collidesWith(const ICollidable* c) const {
	std::shared_ptr<const Bounds> bounds = c->getBounds();

	if (bounds->type == BoundsType::Sphere) {
		std::shared_ptr<const BoundingSphere> bs = std::static_pointer_cast<const BoundingSphere>(bounds);

		TrackPath *track = Game::getGlobalInstance()->getTrackPath();
		Common::Vector4 trackPoint = track->nodes[(int)c->getGroupingParameter().z()].point;
		
		float distance = (bs->position - trackPoint).length() + bs->radius;

		return distance > 100.0f; // track->nodes[c->getGroupingParameter.z()].radius
	}
	else return false;
}

void Tube::handleCollision(std::shared_ptr<const Bounds>, float dt) {}

std::shared_ptr<const Bounds> Tube::getBounds() const {
	return shared_ptr<const Bounds>(new Bounds());
}

unsigned int Tube::getPriority() const {
	return static_cast<unsigned int>(CollisionPriorities::Track);
}
