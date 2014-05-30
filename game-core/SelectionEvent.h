#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"
#include "ActionType.h"
#include "Game.h"

class GAMECOREDLL SelectionEvent : public ActionEvent {
public:
	struct SelectionType {
		unsigned int guid;
		bool selectChar;
		bool unselectChar;
		bool toggleSelect;
		float selectionDirection;
	};
	static const ActionType ACTIONTYPE = ActionType::SELECT;

	SelectionType selection;

	SelectionEvent(unsigned int playerGuid, SelectionType selection);
	SelectionEvent(unsigned int playerGuid, const char* data);
	~SelectionEvent();

	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);
};
