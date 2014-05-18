#include "ServerGame.h"
#include "MoveEvent.h"
#include "ShootEvent.h"
#include "ActionType.h"

#include "engine-core/ServerEngine.h"

ServerGame::ServerGame(float frameTime) {
	this->frameTime = frameTime;

	cmd = new CommandLine(this, &cmd_mtx, &cmd_buffer);
}

ServerGame::~ServerGame() {
}

Engine * ServerGame::makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors ) {

	Engine* eng  = new ServerEngine(
		new GameWorld(this),
		objectCtors,
		eventCtors,
		this->frameTime);

	return eng;
}

void ServerGame::run(){
	Game::run();
}

void ServerGame::update(){
	handleCmd();
}

void ServerGame::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}

void ServerGame::handleCmd(){
	std::string str;
	cmd_mtx.lock();
	while (getline(cmd_buffer, str)){
		cmd->handleCmd(str);
		cout << endl << ">>";
	}
	cmd_buffer.clear();
	cmd_mtx.unlock();
}
