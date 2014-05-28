#include "Player.h"

Player::Player(unsigned int guid) : MovingObject(0, nullptr) {
	this->guid = guid;
	this->tempSelection = 0;
	this->selection = -1;
}

Player::~Player() {
}

void Player::die() {
	this->deathCount++;
}

void Player::updateTempSelection(int tempSelection) {
	this->tempSelection = tempSelection;
	IHasHandle::setType(tempSelection);
}

void Player::makeSelection(int selection) {
	this->selection = selection;
	IHasHandle::setType(selection);
}

int Player::getDeathCount() {
	return this->deathCount;
}

int Player::getTempSelection() {
	return this->tempSelection;
}

int Player::getSelection() {
	return this->selection;
}

bool Player::handleEvent(Event *evt) {

	ActionEvent *actionEvt = Event::cast<ActionEvent>(evt);
	if (actionEvt == nullptr)
		return false;

	switch (ActionType(actionEvt->getActionType())) {
	case ActionType::SELECT: {
		SelectionEvent *selectionEvent = ActionEvent::cast<SelectionEvent>(actionEvt);
		if (selectionEvent == nullptr)
			return false;

		if (selectionEvent->selection.selectChar) {
			this->selection = this->tempSelection;
		}

		if (selectionEvent->selection.unselectChar) {
			this->selection = -1;
		}

		if (selectionEvent->selection.toggleSelect) {
			if (this->selection != -1) {
				this->selection = this->tempSelection;
			} else {
				this->selection = -1;
			}
		}

		if (selectionEvent->selection.selectionDirection < 0) {
			this->tempSelection = (this->tempSelection + 3) % 4;
		} else if (selectionEvent->selection.selectionDirection > 0) {
			this->tempSelection = (this->tempSelection + 1) % 4;
		}

		return true;
		break;
	}
	default:
		break;
	}
	return false;
}