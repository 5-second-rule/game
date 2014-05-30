#pragma once
#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "SelectionEvent.h"
#include "ActionType.h"

class GAMECOREDLL Player : public ISerializable, public PlayerDelegate {	
private:
	struct PlayerData {
		unsigned int guid;
		int deathCount;
		int tempSelection;
		int selection;
	};

protected:
	PlayerData data;

public:
	Player();
	Player(unsigned int guid);
	~Player();

	void die();
	void updateTempSelection(int tempSelection);
	void makeSelection(int selection);
	int getDeathCount();
	int getTempSelection();
	int getSelection();
	unsigned int getGuid();

	// ISerializable methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);

	// PlayerDelegate methods
	void handleEvent(const ActionEvent* evt);
	Handle cameraTarget();
};

