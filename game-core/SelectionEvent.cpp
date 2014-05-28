#include "SelectionEvent.h"

SelectionEvent::SelectionEvent(unsigned int playerGuid, SelectionType selection)
: ActionEvent(playerGuid, static_cast<int>(SelectionEvent::ACTIONTYPE)) {
	this->selection = selection;
}

SelectionEvent::SelectionEvent(unsigned int playerGuid, const char* data)
: ActionEvent(playerGuid, static_cast<int>(SelectionEvent::ACTIONTYPE)) {
	if (data != nullptr)
		this->selection = *reinterpret_cast<const SelectionType*>(data);
}

SelectionEvent::~SelectionEvent() {}

void SelectionEvent::reserveSize(IReserve& buffer) const {
	ActionEvent::reserveSize(buffer);
	buffer.reserve(sizeof(this->selection));
}

void SelectionEvent::fillBuffer(IFill& buffer) const {
	ActionEvent::fillBuffer(buffer);
	*reinterpret_cast<SelectionType*>(buffer.getPointer()) = this->selection;
	buffer.filled();
}

void SelectionEvent::deserialize(BufferReader& buffer) {
	ActionEvent::deserialize(buffer);
	this->selection = *reinterpret_cast<const SelectionType*>(buffer.getPointer());
	buffer.finished(sizeof(this->selection));
}