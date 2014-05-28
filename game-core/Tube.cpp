#include <list>

#include "Tube.h"

#include "MovingObject.h"
#include "AutonomousObject.h"
#include "ObjectTypes.h"
#include "Game.h"

TubeEntity::TubeEntity(Handle handle){
	MovingObject *obj = dynamic_cast<MovingObject*>(m_getObject(handle));
	if (obj == nullptr)
		throw runtime_error("null pointer at TubeEntity");
	owner = handle;
	atual_index = obj->getTrackIndex();
}

bool TubeEntity::operator==(const TubeEntity entity) const{
	return this->owner.index == entity.owner.index;
}

bool TubeEntity::operator<(const TubeEntity entity) const{
	return this->owner.index < entity.owner.index;
}

string TubeEntity::toString() const{
	stringstream buffer;
	buffer << owner.toString();
	return buffer.str();
}


Tube::Tube() : StaticObject(ObjectTypes::Track) {
	path = Game::getGlobalInstance()->getTrackPath();
}

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

void Tube::update(float dt){
	list<Handle> players = m_getEngine()->getPlayers();
	for (list<Handle>::iterator it = players.begin(); it != players.end(); ++it){
		if (this->players.find(TubeEntity(*it)) == this->players.end())
			this->players.insert(TubeEntity(*it));
	}

	for (set<TubeEntity>::iterator it = this->players.begin(); it != this->players.end(); ++it){
		MovingObject *mObj = dynamic_cast<MovingObject*>(m_getObject(it->owner));
		
		if (mObj != nullptr){
			if (mObj->getTrackIndex() != it->atual_index){
				TubeEntity n(it->owner);
				n.atual_index = mObj->getTrackIndex();
				if (Common::randInt(0, 100) < 1){
					AutonomousObject *aObj = new AutonomousObject(ObjectTypes::Ecoli, Game::getGlobalInstance());
					m_getWorld()->allocateHandle(aObj, HandleType::GLOBAL);
					m_getWorld()->insert(aObj);
					aObj->setPos(this->path->nodes[(n.atual_index + 100) % this->path->nodes.size()].point);
					aObj->setFlag("follow_track", false);
					aObj->setOnSteeringBehavior(BehaviorType::wander);
					cout << "created!" << endl;
				}
			}
		}
		else {
			cout << "Player is null!";
		}

	}
	

}