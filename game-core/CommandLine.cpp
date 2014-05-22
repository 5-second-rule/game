#include "CommandLine.h"

using namespace std;

// Command Line Exception
CmdException::CmdException(const string &message, bool inclSysMsg) : userMessage(message) {
	if (inclSysMsg) {
		userMessage.append(": ");
		userMessage.append(strerror(errno));
	}
}

CmdException::~CmdException() _NOEXCEPT{}

const char *CmdException::what() const _NOEXCEPT{
	return userMessage.c_str();
}

CommandLine::CommandLine(std::istream *input, std::ostream *output) : BaseObject(ObjectTypes::Cmd)
{
	this->input = input;
	this->output = output;
	input_thread = new std::thread(&cmdLoop, this->input, this->output, &cmd_mtx, &cmd_buffer);
}

CommandLine::~CommandLine()
{
}

void CommandLine::update(float dt){
	readCmd();
}

bool CommandLine::handleEvent(Event *evt){
	return false;
}

void CommandLine::readCmd(){
	std::string str;
	cmd_mtx.lock();
	while (getline(cmd_buffer, str)){
		handleCmd(str);
		*output << endl << ">> ";
	}
	cmd_buffer.clear();
	cmd_mtx.unlock();
}

void CommandLine::cmdLoop(istream *input, ostream *output, mutex *cmd_mtx, stringstream *cmd_buffer){
	std::string str;
	while (getline(*input, str)){
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
	Handle h = getWorld()->getGlobalObjectByIndex(id);

	if (h.id == -1)
		throw CmdException("Object did not find!", false);

	MovingObject *obj = (MovingObject*)getObject(h);

	if (obj == nullptr)
		throw CmdException("Null pointer exception!", false);

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
			cout << e.what() << endl;
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
			cout << e.what() << endl;
			printHelp();
		}
	}
	else {
		printHelp();
	}
}
