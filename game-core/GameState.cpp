#include "GameState.h"

GameState::State GameState::gameState = State::None;

GameState::GameState() : BaseObject(ObjectTypes::State) {
	this->engine = Game::getGlobalInstance()->getEngineInstance();
	this->world = engine->getWorld();
	this->objectCtors = engine->getObjCtors();

	for (int i = 0; i < 4; ++i) {
		this->toonUsed[i] = false;
	}
}

GameState::~GameState() {
}

void GameState::update(float dt) {
	switch (this->getState()) {
	case Selection: {
		if (this->players.size() < 4) break;

		bool allReady = true;
		for (size_t i = 0; i < this->players.size(); ++i) {
			allReady &= this->players[i]->isSelected();
		}

		if (allReady) this->setState(Game);
		break;
	}
	case Game:
		//todo if theres a winner, change state
		break;
	}
}

void GameState::setState(State state) {
	BaseObject * obj = nullptr;

	GameState::gameState = state;
	std::vector<Player>::iterator it;
	switch (state) {
	case (Selection) :
		obj = this->objectCtors->invoke(ObjectTypes::SelectionScreen);
		world->allocateHandle(obj, HandleType::GLOBAL);
		world->insert(obj);
		break;
	case (Game) :

		obj = this->objectCtors->invoke(ObjectTypes::Track);
		world->allocateHandle(obj, HandleType::GLOBAL);
		world->insert(obj);

		// tell each player to create a MovingObject they manage
		for (auto it = players.begin(); it != players.end(); ++it) {
			(*it)->spawnMoveableObject();
		}
		break;
	default:
		break;
	}
}

int GameState::getState() {
	return GameState::gameState;
}

std::vector<Player*> GameState::getPlayers() {
	return players;
}

bool GameState::isToonUsed(int toon) {
	return toonUsed[toon];
}

void GameState::useToon(int toon) {
	toonUsed[toon] = true;
}

void GameState::unuseToon(int toon) {
	toonUsed[toon] = false;
}

void GameState::toggleToonUsed(int toon) {
	toonUsed[toon] = !toonUsed[toon];
}

PlayerDelegate * GameState::addPlayer(unsigned int playerGuid) {
	int selection;
	int numPlayers = players.size();
	if (numPlayers >= 4) {
		return nullptr;
	}

	Player* player = new Player(playerGuid, this);
	switch (this->getState()) {
	case (Selection) :
		player->updateSelection(numPlayers);
		break;
	case (Game) :
		for (int i = 0; i < 4; ++i) {
			selection = i;
			if (this->toonUsed[i]) {
				player->updateSelection(selection);
				this->toonUsed[selection] = false;
				break;
			}

			player->spawnMoveableObject();

		}
		break;
	default: break;
	}
	this->players.push_back(player);

	return player;
}


void GameState::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(GameStateData));
	for (unsigned int i = 0; i < players.size(); ++i) {
		players[i]->reserveSize(buffer);
	}
}

void GameState::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	GameStateData * data = reinterpret_cast<GameStateData*>(buffer.getPointer());
	data->state = gameState;
	data->numPlayers = players.size();
	buffer.filled();
	for (unsigned int i = 0; i < players.size(); ++i) {
		players[i]->fillBuffer(buffer);
	}
	
}

void GameState::deserialize(BufferReader& buffer) {
	BaseObject::deserialize(buffer);
	const GameStateData *data = reinterpret_cast<const GameStateData*>(buffer.getPointer());
	this->gameState = (State) data->state;
	while (data->numPlayers > this->players.size()) {
		this->players.push_back(new Player(this));
	}

	while (data->numPlayers < this->players.size()) {
		this->players.pop_back();
	}

	buffer.finished(sizeof(GameStateData));

	for (unsigned int i = 0; i < data->numPlayers; ++i) {
		players[i]->deserialize(buffer);
	}	
}

bool GameState::handleEvent(Event* evt) {
	return false;
}