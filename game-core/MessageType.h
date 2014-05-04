#pragma once

namespace Game{

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
	Game::Direction dir;
};