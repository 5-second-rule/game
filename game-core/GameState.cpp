#include "GameState.h"

GameState::State GameState::gameState = State::None;

GameState::GameState() : BaseObject(11) {
	this->engine = Game::getGlobalInstance()->getEngineInstance();
	this->world = engine->getWorld();
	this->objectCtors = engine->getObjCtors();

	if (GameState::gameState == State::None) {
		this->setState(Selection);
	}

	for (int i = 0; i < 4; ++i) {
		this->unusedChars[i] = true;
	}
}

GameState::~GameState() {
	std::vector<Player *>::iterator it;
	for (it = players.begin(); it != players.end(); ++it) {
		delete (*it);
		*it = nullptr;
	}
}

void GameState::setState(int state) {
	GameState::setState((State) state);
}

void GameState::setState(State state) {
	IRegisterPlayers::state = state;
	BaseObject * obj = nullptr;

	GameState::gameState = state;
	std::vector<Player *>::iterator it;
	switch (state) {
	case (Selection) :
		obj = this->objectCtors->invoke(ObjectTypes::SelectionScreen);
		world->allocateHandle(obj, HandleType::GLOBAL);
		world->insert(obj);
		break;
	case (Game) :
		//obj = this->objectCtors->invoke(ObjectTypes::Track);
		//world->allocateHandle(obj, HandleType::GLOBAL);
		//world->insert(obj);

		//for (it = players.begin(); it != players.end(); ++it) {
		//	obj = this->objectCtors->invoke((*it)->getSelection());
		//	world->allocateHandle(obj, HandleType::GLOBAL);
		//	world->insert(obj);
		//}
		break;
	default:
		break;
	}
}

int GameState::getState() {
	return GameState::gameState;
}

std::vector<Player *> GameState::getPlayers() {
	return players;
}

BaseObject * GameState::addPlayer(unsigned int playerGuid) {
	BaseObject * obj = nullptr;
	int selection;
	int numPlayers = players.size();
	if (numPlayers >= 4) {
		return nullptr;
	}

	Player *player = new Player(playerGuid);
	switch (this->getState()) {
	case (Selection) :
		player->updateTempSelection(numPlayers);
		break;
	case (Game) :
		for (int i = 0; i < 4; ++i) {
			selection = i;
			if (this->unusedChars[i]) {
				player->makeSelection(selection);
				this->unusedChars[selection] = false;
				break;
			}

			//obj = this->objectCtors->invoke(selection);
			//world->allocateHandle(obj, HandleType::GLOBAL);
			//world->insert(obj);

		}
		break;
	default: break;
	}
	this->players.push_back(player);
}


bool GameState::handleEvent(Event *evt) {
	return false;
}