#include <cstdlib>
#include <sstream>

#include "AutonomousObjectManager.h"
#include "GameState.h"

#define WHITE_PER_PLAYER 4
#define RED_PER_PLAYER 10

AutonomousEntity::AutonomousEntity(Handle p_handle, bool p_loop){
	this->handle = p_handle;
	this->loop = p_loop;
}

AutonomousEntity::AutonomousEntity(Handle p_handle) : AutonomousEntity(p_handle, false) {}

AutonomousGroup::AutonomousGroup(Handle handle){
	MovingObject *obj = dynamic_cast<MovingObject*>(theWorld.get(handle));
	if (obj == nullptr)
		throw runtime_error("null pointer at AutonomousGroup");
	owner = handle;
	atual_index = obj->getTrackIndex();
}

bool AutonomousGroup::operator==(const AutonomousGroup &entity) const{
	return this->owner.index == entity.owner.index;
}

string AutonomousGroup::toString() const{
	stringstream buffer;
	buffer << owner.toString();
	return buffer.str();
}

AutonomousObjectManager::AutonomousObjectManager(TrackPath *p_track_path, GameState *p_game_state) :
	BaseObject(ObjectTypes::AIManager)
{
	this->path = p_track_path;
	this->gameState = p_game_state;
}

AutonomousObjectManager::~AutonomousObjectManager() {}

bool AutonomousObjectManager::handleEvent(Event* evt){
	return false;
}

void AutonomousObjectManager::setOffsetPursuitDefaultAI(AutonomousObject *obj){
	obj->setMaxSpeed(10);
	obj->setMaxForce(10);
	obj->setFollowTrack(false);
}

void AutonomousObjectManager::setPursuitDefaultAI(AutonomousObject *obj){
	obj->setFollowTrack(false);
	obj->setHasPropulsion(false);
	obj->setMaxSpeed(30.f);
	obj->setMaxForce(20.0f);
}

void AutonomousObjectManager::setDefaultRedBlood(MovingObject *obj){
	obj->setFollowTrack(false);
	obj->setHasPropulsion(false);
}

static Vector4 pointNoise(Vector4 &point){
	static float radius = 60.0f;
	return Vector4(point.x() + radius * (rand() % 100), point.y() + radius * (rand() % 100), point.z() + radius * (rand() % 100));
}

void AutonomousObjectManager::update(float dt){
	BaseObject::update(dt);
	vector<Handle> players = this->gameState->getPlayersHandle();
	for (vector<Handle>::iterator it = players.begin(); it != players.end(); ++it){
		MovingObject *mObj = dynamic_cast<MovingObject*>(theWorld.get(*it));
		if (mObj != nullptr && find(this->players.begin(), this->players.end(), *it) == this->players.end()){
			AutonomousGroup group(*it);
			for (int i = 0; i < WHITE_PER_PLAYER; ++i){
				AutonomousObject *aObj = new AutonomousObject(ObjectTypes::WhiteBlood);
				theWorld.allocateHandle(aObj, HandleType::GLOBAL);
				theWorld.insert(aObj);
				this->setPursuitDefaultAI(aObj);
				aObj->setPursuit(mObj->getHandle());
				aObj->setTrackIndex((i * 300 + 1000) % this->path->nodes.size());
				aObj->setPosition(pointNoise(this->path->nodes[(i * 300 + 1000) % this->path->nodes.size()].point));
				group.white_blood.push_back(AutonomousEntity(aObj->getHandle(), false));
			}
			for (int i = 0; i < RED_PER_PLAYER; ++i){
				AutonomousObject *aObj = new AutonomousObject(ObjectTypes::RedBlood);
				theWorld.allocateHandle(aObj, HandleType::GLOBAL);
				theWorld.insert(aObj);
				this->setDefaultRedBlood(aObj);
				aObj->setOnSteeringBehavior(BehaviorType::wander);
				aObj->setTrackIndex((i * 300 + 1000) % this->path->nodes.size());
				aObj->setPosition(pointNoise(this->path->nodes[(i * 300 + 1000) % this->path->nodes.size()].point));
				group.red_blood.push_back(AutonomousEntity(aObj->getHandle(), false));
			}

			group.atual_index = 0;
			this->players.push_back(group);
		}
	}

	for (list<AutonomousGroup>::iterator it = this->players.begin(); it != this->players.end(); ++it){
		MovingObject *pray = dynamic_cast<MovingObject*>(theWorld.get(it->owner));

		if (pray != nullptr){
			if (pray->getTrackIndex() != it->atual_index){
				if (it->atual_index > pray->getTrackIndex()){
					for (std::list<AutonomousEntity>::iterator entity_it = it->white_blood.begin();
						entity_it != it->white_blood.end();
						++entity_it)
					{
						entity_it->loop = false;
					}

					for (std::list<AutonomousEntity>::iterator entity_it = it->red_blood.begin();
						entity_it != it->red_blood.end();
						++entity_it)
					{
						entity_it->loop = false;
					}
				}
				it->atual_index = pray->getTrackIndex();
				int perc = rand() % 101;
				if (perc < 15){
					AutonomousEntity entity = it->white_blood.front();
					AutonomousObject *aObj = dynamic_cast<AutonomousObject*>(theWorld.get(entity.handle));
					Vector4 dif = aObj->getPosition() - pray->getPosition();
					int destiny_index = (it->atual_index + 2000) % path->nodes.size();

					// Avoid change the position of an object that is in front of the object doing a dot product check
					if ((!entity.loop) &&
						(aObj->getTrackIndex() < pray->getTrackIndex()) &&
						(dif.dot(path->nodes[it->atual_index].normal) < 0 && dif.lengthSquared() > 10000.0f) ||
						(dif.lengthSquared() > 1000000.0f))
					{
						it->white_blood.pop_front();
						aObj->setPosition(pointNoise(path->nodes[destiny_index].point));
						aObj->setTrackIndex(destiny_index);
						aObj->setVelocity(Vector4(0, 0, 0));

						if (destiny_index < it->atual_index)
							entity.loop = true;

						it->white_blood.push_back(entity);
					}
					else {
						it->white_blood.pop_front();
						it->white_blood.push_back(entity.handle);
					}
				}
				else if (perc < 30){
					AutonomousEntity entity = it->red_blood.front();
					AutonomousObject *aObj = dynamic_cast<AutonomousObject*>(theWorld.get(entity.handle));
					Vector4 dif = aObj->getPosition() - pray->getPosition();
					int destiny_index = (it->atual_index + 500) % path->nodes.size();

					// Avoid change the position of an object that is in front of the object doing a dot product check
					if ((!entity.loop) &&
						(aObj->getTrackIndex() < pray->getTrackIndex()) &&
						(dif.dot(path->nodes[it->atual_index].normal) < 0 && dif.lengthSquared() > 10000.0f) ||
						(dif.lengthSquared() > 1000000.0f))
					{
						it->red_blood.pop_front();
						aObj->setPosition(pointNoise(path->nodes[destiny_index].point));
						aObj->setTrackIndex(destiny_index);

						if (destiny_index < it->atual_index)
							entity.loop = true;

						it->red_blood.push_back(entity);
					}
					else {
						it->red_blood.pop_front();
						it->red_blood.push_back(entity.handle);
					}
				}
			}
		}
		else {
			cout << "Removing Tube entity!";
			this->players.remove(*it);
			it = this->players.begin();
		}
	}
}
