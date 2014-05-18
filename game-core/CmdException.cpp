#include "CmdException.h"

using namespace std;

CmdException::CmdException()
{
}

CmdException::CmdException(string msg){
	this->msg = msg;
}

CmdException::~CmdException()
{
}
