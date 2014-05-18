#include "CommandLine.h"
#include "CmdException.h"

using namespace std;

CommandLine::CommandLine(ServerGame* owner, std::mutex *cmd_mtx, std::stringstream *cmd_buffer)
{
	this->owner = owner;
	input_thread = new std::thread(&cmdLoop, cmd_mtx, cmd_buffer);
}


CommandLine::~CommandLine()
{
}

void CommandLine::cmdLoop(std::mutex *cmd_mtx, std::stringstream *cmd_buffer){
	std::string str;
	while (getline(std::cin, str)){
		cmd_mtx->lock();
		(*cmd_buffer) << str << endl;
		cmd_mtx->unlock();
	}
}

void CommandLine::handleCmd(std::string cmd){
	std::stringstream buffer;
	std::string str;
	buffer.str(cmd);
	buffer >> str;
	if (str == "--help" || str == "-h"){
		// Help
		help();
	} 
	else if (str == "set" || str == "s") {
		set(buffer);
	}
	else if (str == "list-objects") {
		cout << getWorld()->listObjects() << endl;
	}
	else if (str == "print" || str == "p") {
		print(buffer);
	}
	else {
		invalidCommand();
	}
}

void CommandLine::help(){
	cout << "Commands:" << endl;
	cout << "list-objects: list the global objects" << endl;
	cout << "set: set some property in the world" << endl;
	cout << "print: print some information about the world" << endl;
}

void CommandLine::setHelp(){
	cout << "Set command:" << endl;
	cout << "[position | p] [id] [x] [y] [z]: set the position of the object by ID" << endl;
}

void CommandLine::printHelp(){
	cout << "Print command:" << endl;
	cout << "[object | o] [id]: print the information of objects by ID" << endl;
}

void CommandLine::invalidCommand(){
	std::cout << "Invalid command" << endl;
	help();
}

MovingObject *CommandLine::findObjectById(int id){
	Handle h = getWorld()->findObjectById(id);

	if (h.id == -1)
		throw CmdException("Object did not find!");

	MovingObject *obj = (MovingObject*)getObject(h);

	if (obj == nullptr)
		throw CmdException("Null pointer exception!");

	return obj;
}

void CommandLine::set(std::stringstream &buffer){
	std::string str;
	int id;
	float x, y, z;
	buffer >> str;
	// Position
	if (str == "position" || str == "p") {
		buffer >> id >> x >> y >> z;

		try {
			MovingObject *obj = findObjectById(id);
			obj->setPos(x, y, z);
		}
		catch (CmdException e){
			cout << e.msg << endl;
			printHelp();
		}
	}
	else {
		setHelp();
	}
}

void CommandLine::print(stringstream &buffer){
	string str;
	int id;
	buffer >> str;
	// Object
	if (str == "object" || str == "o"){
		buffer >> id;

		try {
			MovingObject *obj = findObjectById(id);
			cout << obj->toString() << endl;
		}
		catch (CmdException e){
			cout << e.msg << endl;
			printHelp();
		}
	}
	else {
		printHelp();
	}
}