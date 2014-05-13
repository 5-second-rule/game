#include "ServerGameInstance.h"
#include "MoveEvent.h"
#include "ShootEvent.h"
#include "ActionType.h"

#include "engine-core/ServerEngine.h"

ServerGameInstance::ServerGameInstance(float frameTime) {
	this->frameTime = frameTime;
}

ServerGameInstance::~ServerGameInstance() {
}

Engine * ServerGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	Engine* eng  = new ServerEngine(
		new World(),
		ctors,
		this->frameTime);
	eng->delegate = this;

	return eng;
}

void ServerGameInstance::run() {
	Handle h = createObject(ObjectTypes::Ecoli);
	this->setPosition(0, 0, 0, &h);
	MovingObject* obj = dynamic_cast<MovingObject*>(engineInstance->world->get(&h));
	assert(obj);

	GameInstance::run();
}

void ServerGameInstance::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}

ActionEvent* ServerGameInstance::MakeActionEvent( int actionType, unsigned int playerGuid, const char* data ) {
	ActionEvent* evt = nullptr;
	
	switch( ActionType( actionType ) ) {
		case ActionType::MOVE:
			evt = new MoveEvent(playerGuid, *(reinterpret_cast<const MoveEvent::MoveDirection*>(data)));
			break;
		case ActionType::SHOOT:
 			evt = new ShootEvent( playerGuid );
			break;
		case ActionType::USE:
			break;
		default:
			break;
	}

	return evt;
}

Handle ServerGameInstance::createObject(int p_object_type){
	IHasHandle* obj = engineInstance->objectCtors->invoke(p_object_type);
	engineInstance->world->allocateHandle(obj);
	engineInstance->world->insert(obj);
	return obj->getHandle();
}

void ServerGameInstance::setPosition(float x, float y, float z, Handle* objH){
	setPosition(Vector4(x, y, z), objH);
}

void ServerGameInstance::setPosition(Vector4 &pos, Handle* objH){
	GameObject* obj = dynamic_cast<GameObject*>(engineInstance->world->get(objH));
	assert(obj);
	obj->setPosition(pos);
}

void ServerGameInstance::createAI(Handle *objH){
	MovingObject* obj = dynamic_cast<MovingObject*>(engineInstance->world->get(objH));
	assert(obj);
	obj->createAI();
}

void ServerGameInstance::handleTerminal(){
	stringstream buffer;
	char c[256];
	string input;/*
	while (cin.getline(c, 256)){
		input = string(c);
		buffer.clear();
		buffer.str(input);
		buffer >> input;

		if (input == "print"){
			printCommand(buffer);
		}
		

	}*/
}

void ServerGameInstance::printCommand(stringstream &buffer){
	Handle handle;
	GameObject* obj;
	stringstream tmp;
	string str;
	int id;
	buffer >> str;
	if (str == "object_list"){
		cout << engineInstance->world->listOfObjects() << endl;
	}
	if (str == "-o"){
		while (buffer >> str){
			tmp.str(str);
			tmp >> id;
			obj = dynamic_cast<GameObject*>(getObject(engineInstance->world->findObjectById(id)));
			if (obj != nullptr)
				cout << obj->toString() << endl;
		}
	}
}