#pragma once
#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "SelectionEvent.h"
#include "ActionType.h"
#include "PlayerMovingObject.h"
#include "RotateCameraObject.h"

class GAMECOREDLL GameState;

class GAMECOREDLL Player : public ISerializable, public PlayerDelegate {	
private:
	struct PlayerData {
		unsigned int guid;
		int deathCount;
		int selection;
		bool selected;
		Handle movingObject;
		Handle rotateCameraObject;
		Handle deathCamera;

		bool dead;
		float respawnTimer;
		bool hasAdrenaline;
	};

	GameState* gameState;

protected:
	PlayerData data;

public:
	Player(GameState* state);
	Player(unsigned int guid, GameState* state);
	~Player();

	void update(float dt);
	
	unsigned int getGuid();
	void spawnMoveableObject();

	void spawnRotateCameraObject();
	void spawnDeathCamera();

	Handle getMovingObject();
	Handle getRotateCameraObject();
	void respawn();

	// death tracking
	void die();
	int getDeathCount();

	bool isDead();

	void addPowerup();
	
	// selection
	void updateSelection(int tempSelection);
	
	int getSelection();
	bool isSelected();

	// powerup
	bool hasAdrenaline();

	// ISerializable methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);

	// PlayerDelegate methods
	void handleEvent(ActionEvent* evt);
	Handle cameraTarget();

	bool isReallyReallyDead();
};

