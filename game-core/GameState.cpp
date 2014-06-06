#include "GameState.h"
#include "Powerup.h"
#include "Sounds.h"

GameState::State GameState::gameState = State::None;

GameState::GameState( ::Game* game ) : BaseObject( ObjectTypes::State ) {
	this->game = game;
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
		// update leaderboard, maybe move to new function
		TrackPath *track = this->game->getTrackPath();
		int smallestPos = -1;
		int largestPos = -1;

		PlayerMovingObject* playerObjs[4];

		for (size_t i = 0; i < this->players.size(); i++) {
			playerObjs[i] = dynamic_cast<PlayerMovingObject*>(
				this->world->get(this->players[i]->cameraTarget()));

			if (playerObjs[i] != nullptr) {
				if (playerObjs[i]->dead) {
					playerObjs[i]->dead = false;
					this->players[i]->die();
					this->players[i]->respawn();
					cout << "player #" << i << " has died" << endl;
				}

				int trackIndex = playerObjs[i]->getTrackIndex();

				if (smallestPos == -1 || smallestPos > trackIndex) {
					smallestPos = trackIndex;
				}

				if (largestPos == -1 || largestPos < trackIndex) {
					largestPos = trackIndex;
				}
			}
		}

		bool midLapRollover = static_cast<size_t>(largestPos - smallestPos) > (track->nodes.size() / 2);
		int dividingLine = largestPos - (track->nodes.size() / 2);
		
		int positions[4];
		for (size_t i = 0; i < this->players.size(); i++) {
			if (playerObjs[i] != nullptr) {
				positions[i] = playerObjs[i]->getTrackIndex();
				if (midLapRollover && positions[i] < dividingLine) {
					positions[i] += track->nodes.size();
				}
			}
			else {
				positions[i] = midLapRollover ? smallestPos : dividingLine;
			}
		}

		for (size_t i = 0; i < this->players.size(); i++) {
			for (size_t j = i; j < this->players.size(); j++) {
				LeaderboardEntry iEntry = leaderboard[i];
				iEntry.playerPosition = positions[iEntry.playerIndex];
				leaderboard[i] = iEntry;

				LeaderboardEntry jEntry = leaderboard[j];
				if (positions[jEntry.playerIndex] > iEntry.playerPosition) {
					LeaderboardEntry tmp = leaderboard[i];
					leaderboard[i] = leaderboard[j];
					leaderboard[j] = tmp;
				}
			}
		}

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
		this->selScreen = this->objectCtors->invoke(ObjectTypes::SelectionScreen);
		world->allocateHandle(this->selScreen, HandleType::GLOBAL);
		world->insert(this->selScreen);
		break;
	case (Game) :
	{
		// remove selection screen from world
		world->remove( &this->selScreen->getHandle() );
		this->selScreen = nullptr;

		obj = this->objectCtors->invoke( ObjectTypes::Track );
		world->allocateHandle( obj, HandleType::GLOBAL );
		world->insert( obj );

		this->game->wallOfDeath = dynamic_cast<WallOfDeath *>(this->objectCtors->invoke( ObjectTypes::Wwod ));
		if( this->game->wallOfDeath == nullptr ) {
			throw std::runtime_error( "Error creating wall of death." );
		}

		world->allocateHandle( this->game->wallOfDeath, HandleType::GLOBAL );
		this->world->insert( this->game->wallOfDeath );

		this->game->wallOfDeath->reset();
		this->game->wallOfDeath->setLeaderboard(&this->leaderboard);

		int numberOfPowerups = 12;
		int range = this->game->getTrackPath()->nodes.size();
		for( int i = 1; i < numberOfPowerups; i++ ) {
			Powerup * powerup = static_cast<Powerup*>(this->objectCtors->invoke( ObjectTypes::Adrenaline ));
			powerup->place( i * (range / numberOfPowerups) );

			this->world->allocateHandle( powerup, HandleType::GLOBAL );
			this->world->insert( powerup );
		}

		// tell each player to create a MovingObject they manage
		for( auto it = players.begin(); it != players.end(); ++it ) {
			(*it)->spawnMoveableObject();
		}

		float dummyLocation[3] = { 0, 0, 0 };
		this->game->getEngineInstance()->sendEvent(new SoundEvent(static_cast<int>(Sounds::SOUNDTRACK), true, false, dummyLocation));

		break;
	}
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
		//player->updateSelection(numPlayers);
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

	this->leaderboard.push_back({ numPlayers, 0 });
	this->players.push_back(player);

	return player;
}


void GameState::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(GameStateData));
	for (unsigned int i = 0; i < players.size(); ++i) {
		players[i]->reserveSize(buffer);
	}

	for (unsigned int i = 0; i < players.size(); ++i) {
		buffer.reserve(sizeof(LeaderboardEntry));
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

	for (unsigned int i = 0; i < players.size(); ++i) {
		LeaderboardEntry * entry = reinterpret_cast<LeaderboardEntry*>(buffer.getPointer());
		(*entry) = leaderboard[i];
		buffer.filled();
	}
}

void GameState::deserialize(BufferReader& buffer) {
	BaseObject::deserialize(buffer);
	const GameStateData *data = reinterpret_cast<const GameStateData*>(buffer.getPointer());
	this->gameState = (State) data->state;
	while (data->numPlayers > this->players.size()) {
		this->players.push_back(new Player(this));
		this->leaderboard.push_back(LeaderboardEntry());
	}

	while (data->numPlayers < this->players.size()) {
		this->players.pop_back();
		this->leaderboard.pop_back();
	}

	buffer.finished(sizeof(GameStateData));

	for (unsigned int i = 0; i < data->numPlayers; ++i) {
		players[i]->deserialize(buffer);
	}

	for (unsigned int i = 0; i < data->numPlayers; ++i) {
		const LeaderboardEntry *entry = reinterpret_cast<const LeaderboardEntry*>(buffer.getPointer());
		leaderboard[i] = *entry;
		buffer.finished(sizeof(LeaderboardEntry));
	}
}

bool GameState::handleEvent(Event* evt) {
	return false;
}

std::string GameState::toString() {
	return	BaseObject::toString() + "\r\nType: GameState";
}

std::vector<LeaderboardEntry> GameState::getLeaderboard() {
	return this->leaderboard;
}

std::vector<Handle> GameState::getPlayersHandle(){
	std::vector<Handle> players;
	for (std::vector<Player*>::iterator it = this->players.begin(); it != this->players.end(); ++it){
		players.push_back((*it)->getMovingObject());
	}
	return players;
}