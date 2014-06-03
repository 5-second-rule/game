#include <cstdlib>
#include <sstream>

#include "AutonomousObjectManager.h"

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

AutonomousObjectManager::AutonomousObjectManager() : BaseObject(ObjectTypes::AIManager) {}

AutonomousObjectManager::~AutonomousObjectManager() {}

void AutonomousObjectManager::setTrack(TrackPath *p_track_path){
	this->path = p_track_path;
}

bool AutonomousObjectManager::handleEvent(Event* evt){
	return false;
}

void AutonomousObjectManager::setOffsetDefaultAI(AutonomousObject *obj){
	obj->setMaxSpeed(10);
	obj->setMaxForce(10);
	obj->setFollowTrack(true);
	obj->setFluidForce(0.0f);
}

void AutonomousObjectManager::setPursuitDefaultAI(AutonomousObject *obj){
	obj->setFollowTrack(false);
	obj->setHasPropulsion(false);
	obj->setMaxSpeed(20.0f);
}

void AutonomousObjectManager::update(float dt){
	BaseObject::update(dt);
	static bool offset = false;
	vector<Handle> players = theEngine.getPlayers();
	for (vector<Handle>::iterator it = players.begin(); it != players.end(); ++it){
		MovingObject *mObj = dynamic_cast<MovingObject*>(theWorld.get(*it));
		if (mObj != nullptr && find(this->players.begin(), this->players.end(), *it) == this->players.end()){
			AutonomousGroup group(*it);
			for (int i = 0; i < 20; ++i){
				AutonomousObject *aObj = new AutonomousObject(ObjectTypes::RedBlood);
				this->setPursuitDefaultAI(aObj);
				aObj->setPosition(Vector4(200, 0, 0));
				group.autonomous_list.push_back(aObj->getHandle());
			}

			group.atual_index = 0;
			this->players.push_back(group);
		}
	}

	for (list<AutonomousGroup>::iterator it = this->players.begin(); it != this->players.end(); ++it){
		MovingObject *pray = dynamic_cast<MovingObject*>(theWorld.get(it->owner));

		if (pray != nullptr){
			if (pray->getTrackIndex() != it->atual_index){
				int perc = rand() % 101;
				it->atual_index = pray->getTrackIndex();
				if (perc < 5){
					Handle handle = it->autonomous_list.front();
					AutonomousObject *aObj = dynamic_cast<AutonomousObject*>(theWorld.get(handle));

					// Avoid change the position of an object that is in front of the object doing a dot product check
					if ((aObj->getPosition() - pray->getPosition()).dot(path->nodes[it->atual_index].normal) < 0){
						it->autonomous_list.pop_front();

						if (aObj == nullptr){
							aObj = new AutonomousObject(ObjectTypes::Ecoli);
							handle = aObj->getHandle();
						}

						aObj->setPosition(path->nodes[(pray->getTrackIndex() + 2000) % path->nodes.size()].point);
						aObj->setPursuit(pray->getHandle());
						//aObj->setOnSteeringBehavior(BehaviorType::wander);

						it->autonomous_list.push_back(handle);
					}
				}
				/*else if (perc < 6 && !offset){
				cout << "chupa";
				Vector4 p = path->nodes[(pray->getTrackIndex() + 2000) % path->nodes.size()].point;
				AutonomousObject *aObj1 = new AutonomousObject(ObjectTypes::Ecoli);
				AutonomousObject *aObj2 = new AutonomousObject(ObjectTypes::Ecoli);
				AutonomousObject *aObj3 = new AutonomousObject(ObjectTypes::Ecoli);
				AutonomousObject *aObj4 = new AutonomousObject(ObjectTypes::Ecoli);
				AutonomousObject *aObj5 = new AutonomousObject(ObjectTypes::Ecoli);
				this->setOffset(aObj1);
				this->setOffset(aObj2);
				this->setOffset(aObj3);
				this->setOffset(aObj4);
				this->setOffset(aObj5);
				aObj1->setPos(Vector4(p.x() + cos(rand()) * 5, p.y() + cos(rand()) * 5, p.z() + cos(rand()) * 5));
				aObj2->setPos(Vector4(p.x() + cos(rand()) * 5, p.y() + cos(rand()) * 5, p.z() + cos(rand()) * 5));
				aObj3->setPos(Vector4(p.x() + cos(rand()) * 5, p.y() + cos(rand()) * 5, p.z() + cos(rand()) * 5));
				aObj4->setPos(Vector4(p.x() + cos(rand()) * 5, p.y() + cos(rand()) * 5, p.z() + cos(rand()) * 5));
				aObj5->setPos(Vector4(p.x() + cos(rand()) * 5, p.y() + cos(rand()) * 5, p.z() + cos(rand()) * 5));
				aObj1->setOffsetPursuit(pray->getHandle(), Vector4(0, 0, 5));
				aObj2->setOffsetPursuit(pray->getHandle(), Vector4(0, 0, -5));
				aObj3->setOffsetPursuit(pray->getHandle(), Vector4(5, 0, 0));
				aObj4->setOffsetPursuit(pray->getHandle(), Vector4(-5, 0, 0));
				aObj5->setOffsetPursuit(pray->getHandle(), Vector4(0, 5, 0));
				offset = true;
				}*/
			}
		}
		else {
			cout << "Removing Tube entity!";
			this->players.remove(*it);
			it = this->players.begin();
		}
	}
}
