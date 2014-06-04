#include <cstdlib>
#include <sstream>

#include "AutonomousObjectManager.h"
#include "GameState.h"

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
	obj->setFollowTrack(true);
	obj->setFluidForce(0.0f);
}

void AutonomousObjectManager::setPursuitDefaultAI(AutonomousObject *obj){
	obj->setFollowTrack(false);
	obj->setHasPropulsion(false);
	obj->setMaxSpeed(70.0f);
	obj->setMaxForce(40.0f);
}

void AutonomousObjectManager::setDefaultRedBlood(MovingObject *obj){
	obj->setFollowTrack(false);
	obj->setHasPropulsion(false);
}

void AutonomousObjectManager::update(float dt){
	BaseObject::update(dt);
	static bool offset = false;
	vector<Handle> players = this->gameState->getPlayersHandle();
	for (vector<Handle>::iterator it = players.begin(); it != players.end(); ++it){
		MovingObject *mObj = dynamic_cast<MovingObject*>(theWorld.get(*it));
		if (mObj != nullptr && find(this->players.begin(), this->players.end(), *it) == this->players.end()){
			AutonomousGroup group(*it);
			for (int i = 0; i < 30; ++i){
				AutonomousObject *aObj = new AutonomousObject(ObjectTypes::WhiteBlood);
				this->setPursuitDefaultAI(aObj);
				aObj->setPosition(Vector4(20000, 0, 0));
				group.autonomous_list.push_back(aObj->getHandle());
			}
			for (int i = 0; i < 10; ++i){
				AutonomousObject *mObj = new AutonomousObject(ObjectTypes::RedBlood, Game::getGlobalInstance());
				this->setDefaultRedBlood(mObj);
				mObj->setPosition(Vector4(20000, 0, 0));
				group.red_blood.push_back(mObj->getHandle());
			}
			cout << (this->path->nodes[0].point - this->path->nodes[2000].point).length() << endl;

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
					Vector4 dif = aObj->getPosition() - pray->getPosition();
					// Avoid change the position of an object that is in front of the object doing a dot product check
					if ((dif.dot(path->nodes[it->atual_index].normal) < 0 && dif.lengthSquared() > 10000.0f)||
						dif.lengthSquared() > 4000000){
						it->autonomous_list.pop_front();
						//cout << "move" << endl;
						//cout << pray->getPosition().toString() << endl;
						//cout << pray->getTrackIndex() << endl;
						aObj->setPosition(path->nodes[(pray->getTrackIndex() + 1000) % path->nodes.size()].point);
						aObj->setPursuit(pray->getHandle());
						//aObj->setOnSteeringBehavior(BehaviorType::wander);

						it->autonomous_list.push_back(handle);
					}
					else {
						cout << aObj->getPosition().toString() << endl;
						cout << dif.length() << endl;
					}
				}

				else if (perc < 10){
					Handle handle = it->red_blood.front();
					AutonomousObject *aObj = dynamic_cast<AutonomousObject*>(theWorld.get(handle));
					Vector4 dif = aObj->getPosition() - pray->getPosition();

					// Avoid change the position of an object that is in front of the object doing a dot product check
					if ((dif.dot(path->nodes[it->atual_index].normal) < 0 && dif.lengthSquared() > 10000.0f) ||
						dif.lengthSquared() > 4000000){
						it->red_blood.pop_front();

						aObj->setPosition(path->nodes[(pray->getTrackIndex() + 2000) % path->nodes.size()].point);
						aObj->setOnSteeringBehavior(BehaviorType::wander);

						it->red_blood.push_back(handle);
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
