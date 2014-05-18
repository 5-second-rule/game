#pragma once

#include <string>

class CmdException
{
public:
	std::string msg;

	CmdException();
	CmdException(std::string msg);
	~CmdException();
};

