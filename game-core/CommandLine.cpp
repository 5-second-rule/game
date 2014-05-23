#include <algorithm>

#include "CommandLine.h"
#include "AutonomousObject.h"


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

CommandLine::CommandLine(std::istream *input, std::ostream *output) : IHasHandle(ObjectTypes::Cmd)
{
	this->input = input;
	this->output = output;
	allocator = 0;
	input_thread = new std::thread(&cmdLoop, this->input, &cmd_mtx, &cmd_buffer);
}

CommandLine::~CommandLine()
{
}

void CommandLine::update(float dt){
	readCmd();
}

void CommandLine::readFile(string str){
	ifstream file;
	string tmp;

	file.open(str.c_str());
	if (file.is_open()){
		while (getline(file, tmp)){
			*output << tmp << endl;
			cmd_buffer << tmp << endl;
		}
	}
	else {
		throw CmdException("Error to open file!");
	}
}

bool CommandLine::handleEvent(Event *evt){
	return false;
}

void CommandLine::readCmd(){
	string str;
	cmd_mtx.lock();
	while (getline(cmd_buffer, str)){
		handleCmd(str);
		*output << endl << ">> ";
	}
	cmd_buffer.clear();
	cmd_mtx.unlock();
}

void CommandLine::cmdLoop(istream *input, mutex *cmd_mtx, stringstream *cmd_buffer){
	string str;
	while (getline(*input, str)){
		cmd_mtx->lock();
		(*cmd_buffer) << toLower(str) << endl;
		cmd_mtx->unlock();
	}
}

void CommandLine::handleCmd(std::string cmd){
	stringstream buffer;
	string str;
	buffer.str(cmd);
	buffer >> str;
	if (str == "--help" || str == "-h") {
		helpCmd(buffer);
	}
	else if (str == "set" || str == "s") {
		set(buffer);
	}
	else if (str == "list-objects") {
		*output << getWorld()->listObjects() << endl;
	}
	else if (str == "print" || str == "p") {
		print(buffer);
	}
	else if (str == "create" || str == "c"){
		createObject(buffer);
	}
	else if (str == "run" || str == "r"){
		runFile(buffer);
	}
	else {
		invalidCommand();
	}
}

void CommandLine::help(){
	*output << "Commands:" << endl;
	*output << "list-objects: list the global objects" << endl;
	*output << "set: set some property in the world" << endl;
	*output << "print: print some information about the world" << endl;
	*output << "create: create a new object" << endl;
	*output << "run: run commands in a file" << endl;
}

void CommandLine::helpSet(){
	*output << "Set command:" << endl;
	*output << "-p [x][y][z] -- position" << endl;
	*output << "-i [index] -- index of the object" << endl;
	*output << "-a [[wander | w]] -- AI" << endl;
}

void CommandLine::helpPrint(){
	*output << "Print command:" << endl;
	*output << "[object | o] [id]: print the information of objects by ID" << endl;
}

void CommandLine::helpCreate(){
	*output << "Create command:" << endl;
	*output << "[create | c] <parameters>"<< endl;
	*output << "-t [[autonomous | a]] -- the type of object to be created" << endl;
	*output << "-p [x] [y] [z] -- position" << endl;
}

void CommandLine::helpObjectType(){
	*output << "--Object Types--" << endl;
	*output << "Ecoli | e" << endl;
	*output << "ChickenPox | c" << endl;
	*output << "Syphillis | s" << endl;
	*output << "Malaria | m" << endl;
	*output << "WhiteBlood | w" << endl;
	*output << "RedBlood | r" << endl;
}

void CommandLine::invalidCommand(){
	*output << "Invalid command" << endl;
	help();
}

void CommandLine::helpCmd(stringstream &buffer){
	string str;

	if (!buffer.eof()){
		buffer >> str;

		if (str == "set"){
			helpSet();
		}
		else if (str == "print"){
			helpPrint();
		}
		else if (str == "create"){
			helpCreate();
		}
		else if (str == "object_type"){
			helpObjectType();
		}
	}
	else {
		help();
	}
}

MovingObject *CommandLine::findObjectByIndex(int id){
	Handle handle = getWorld()->getGlobalObjectByIndex(id);

	if (handle.id == -1)
		throw CmdException("Object did not find!", false);

	MovingObject *obj = dynamic_cast<MovingObject*>(getObject(handle));

	if (obj == nullptr)
		throw CmdException("Null pointer exception!", false);

	return obj;
}

MovingObject *CommandLine::translateObject(std::string str){
	MovingObject *obj;
	stringstream buffer;
	int id;
	// If object not in the dictionary
	if (dictionary.find(str) == dictionary.end()){
		buffer << str;
		buffer >> id;
		obj = findObjectByIndex(id);
	}
	else {
		obj = dynamic_cast<MovingObject*>(getObject(dictionary[str]));
		if (obj == nullptr)
			throw CmdException("Null pointer exception!", false);
	}

	return obj;
}

bool CommandLine::setParam(map<string, string> &param, string str, stringstream &buffer){
	float x, y, z;

	if (str == "-t"){
		buffer >> str;
		if (str == "a")
			str = "autonomous";
		param["type"] = str;
	}
	else if (str == "-o"){
		buffer >> str;
		if (!validObjectType(str))
			throw CmdException("Invalid object type!", false);
		param["object_type"] = str;
	}
	else if (str == "-n"){
		buffer >> str;
		if (str[0] >= '0' && str[0] <= '9') {
			throw CmdException("Invalid name!", false);
		}
		param["name"] = str;
	}
	else if (str == "-p"){
		x = y = z = 0.0f;
		buffer >> x >> y >> z;
		param["position"] = "true";
		param["x"] = toString(x);
		param["y"] = toString(y);
		param["z"] = toString(z);
	}
	else if (str == "-i"){
		buffer >> str;
		param["index"] = str;
	}
	// AI
	else if (str == "-ai"){
		buffer >> str;
		param["ai"] = str;
	}
	else if (str == "-w"){
		buffer >> str;
		param["what"] = str;
	}
	else {
		return false;
	}
	return true;
}

void CommandLine::set(std::stringstream &buffer){
	MovingObject *mObj;
	AutonomousObject *aObj;
	string str;
	map<string, string> param;
	
	try {
		while (buffer >> str){
			if (!setParam(param, str, buffer)){
				throw CmdException("Invalid parameter!", false);
			}
		}

		if (param.find("index") != param.end()){
			mObj = translateObject(param["index"]);
			
			if (param.find("name") != param.end()){
				*output << param["name"] << " <-- " << toString(ObjectTypes(mObj->getType())) << endl;
				dictionary[param["name"]] = mObj->getHandle();
			}
		}
		else if (param.find("name") != param.end())
			mObj = translateObject(param["name"]);
		else
			throw CmdException("Identifier not expecified!", false);

		if (param.find("position") != param.end()){
			mObj->setPos(toFloat(param["x"]), toFloat(param["y"]), toFloat(param["z"]));
		}
		
		if (param.find("ai") != param.end()){
			aObj = dynamic_cast<AutonomousObject*>(mObj);

			if (aObj == nullptr)
				throw CmdException("The specified object is not an autonomous object!", false);

			aObj->setOnSteeringBehavior(SteeringBehavior::toBehaviorType(param["ai"]));
		}
	}
	catch (CmdException e){
		*output << e.what() << endl;
		helpSet();
		return;
	}
}

void CommandLine::createObject(std::stringstream &buffer){
	string str;
	AutonomousObject *obj;
	map< string, string > param;

	try {
		// default parameters
		param["object_type"] = "ecoli";
		param["x"] = param["y"] = param["z"] = toString(0.0f);

		while (buffer >> str){
			if (!setParam(param, str, buffer))
				throw CmdException("Invalid parameter!", false);
		}

		if (param.find("type") == param.end())
			throw CmdException("Type of object to be created not expecified!", false);

		if (param["type"] == "autonomous"){
			obj = new AutonomousObject(toObjectType(param["object_type"]));
			getWorld()->allocateHandle(obj, HandleType::GLOBAL);
			getWorld()->insert(obj);
		}
		else {
			throw CmdException("Fail to expecify object type to be created!", false);
		}

		if (param.find("name") != param.end()) {
			*output << param["name"] << " <-- " << param["object_type"] << endl;
			dictionary[param["name"]] = obj->getHandle();
		}
		else {
			*output << "res" + toString(allocator) << " <-- " << param["object_type"] << endl;
			dictionary["res" + toString(allocator)] = obj->getHandle();
			allocator++;
		}

		obj->setPos(toFloat(param["x"]), toFloat(param["y"]), toFloat(param["z"]));
	}
	catch (CmdException e){
		*output << e.what() << endl;
		helpCreate();
		return;
	}
}

void CommandLine::print(stringstream &buffer){
	string str;
	map<string, string> param;
	MovingObject *obj;

	try{
		while (buffer >> str){
			if (!setParam(param, str, buffer))
				throw CmdException("Invalid parameter!", false);
		}

		if (param.find("index") != param.end())
			obj = translateObject(param["index"]);
		else if (param.find("name") != param.end())
			obj = translateObject(param["name"]);
		else
			throw CmdException("Identifier not expecified!", false);

		*output << obj->toString() << endl;
	}
	catch (CmdException e){
		*output << e.what() << endl;
		helpPrint();
	}
}

void CommandLine::runFile(stringstream &buffer){
	string str;
	buffer >> str;
	readFile(str);
}



bool CommandLine::validObjectType(string name){
	if (name == "ecoli" || name == "chickenpox" || name == "syphillis" ||
		name == "malaria" || name == "whiteblood" || name == "redblood"){
		return true;
	}
	return false;
}

ObjectTypes CommandLine::toObjectType(string name){
	if (name == "ecoli" || name == "e"){
		return ObjectTypes::Ecoli;
	}
	if (name == "chickenpox" || name == "e"){
		return ObjectTypes::ChickenPox;
	}
	if (name == "syphillis" || name == "e"){
		return ObjectTypes::Syphillis;
	}
	if (name == "malaria"){
		return ObjectTypes::Malaria;
	}
	if (name == "whiteblood"){
		return ObjectTypes::WhiteBlood;
	}
	if (name == "redblood"){
		return ObjectTypes::RedBlood;
	}
	throw CmdException("Invalid object type", false);
}

string CommandLine::toString(ObjectTypes type){
	if (type == ObjectTypes::Ecoli)
		return "ecoli";
	if (type == ObjectTypes::ChickenPox)
		return "chickenpox";
	if (type == ObjectTypes::Syphillis)
		return "syphillis";
	if (type == ObjectTypes::Malaria)
		return "malaria";
	if (type == ObjectTypes::WhiteBlood)
		return "whiteblood";
	if (type == ObjectTypes::RedBlood)
		return "redblood";
	return "none";
}

string CommandLine::toString(int a){
	stringstream buffer;
	buffer << a;
	return buffer.str();
}

float CommandLine::toFloat(string f){
	stringstream buffer;
	float tmp;
	buffer << f;
	buffer >> tmp;
	return tmp;
}

string CommandLine::toString(float f){
	stringstream buffer;
	buffer << f;
	return buffer.str();
}

char CommandLine::toLowerChar(char c){
	if (c >= 'A' && c <= 'Z'){
		return c - 'A' + 'a';
	}
	return c;
}

string CommandLine::toLower(string str){
	transform(str.begin(), str.end(), str.begin(), CommandLine::toLowerChar);
	return str;
}