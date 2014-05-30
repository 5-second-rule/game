#pragma once
#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "SelectionEvent.h"
#include "ActionType.h"
#include "MovingObject.h"

class GAMECOREDLL Player : public ISerializable, public PlayerDelegate {	
private:
	struct PlayerData {
		unsigned int guid;
		int deathCount;
		int tempSelection;
		int selection;
		Handle movingObject;
	};

protected:
	PlayerData data;

public:
	Player();
	Player(unsigned int guid);
	~Player();
	
	unsigned int getGuid();
	void spawnMoveableObject();

	// death tracking
	void die();
	int getDeathCount();
	
	// selection
	void updateTempSelection(int tempSelection);
	void makeSelection(int selection);
	
	int getTempSelection();
	int getSelection();


	// ISerializable methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);

	// PlayerDelegate methods
	void handleEvent(ActionEvent* evt);
	Handle cameraTarget();
};

