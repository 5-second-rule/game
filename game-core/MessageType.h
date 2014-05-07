#pragma once

namespace MsgGame{

	enum MessageType{
		none,
		move_command
	};

	enum Direction{
		right,
		left,
		up,
		down
	};

}

class MoveMessage{
public:
	MsgGame::Direction dir;
};