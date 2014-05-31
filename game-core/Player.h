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
		int selection;
		bool selected;
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
	void updateSelection(int tempSelection);
	
	int getSelection();
	bool isSelected();

	// ISerializable methods
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);

	// PlayerDelegate methods
	void handleEvent(ActionEvent* evt);
	Handle cameraTarget();
};

