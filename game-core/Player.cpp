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