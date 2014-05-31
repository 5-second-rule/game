#include "GameState.h"

GameState::State GameState::gameState = State::None;

GameState::GameState() : BaseObject(ObjectTypes::State) {
	this->engine = Game::getGlobalInstance()->getEngineInstance();
	this->world = engine->getWorld();
	this->objectCtors = engine->getObjCtors();

	for (int i = 0; i < 4; ++i) {
		this->unusedChars[i] = true;
	}
}

GameState::~GameState() {
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

PlayerDelegate * GameState::addPlayer(unsigned int playerGuid) {
	int selection;
	int numPlayers = players.size();
	if (numPlayers >= 4) {
		return nullptr;
	}

	Player* player = new Player(playerGuid);
	switch (this->getState()) {
	case (Selection) :
		player->updateSelection(numPlayers);
		break;
	case (Game) :
		for (int i = 0; i < 4; ++i) {
			selection = i;
			if (this->unusedChars[i]) {
				player->updateSelection(selection);
				this->unusedChars[selection] = false;
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
		this->players.push_back(new Player());
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