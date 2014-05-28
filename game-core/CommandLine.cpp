#include <algorithm>

#include "CommandLine.h"
#include "AutonomousObject.h"

#include "engine-core/ConfigSettings.h"

#include "common/misc/utils.h"

using namespace std;
using namespace Common;

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

Handle CommandLine::getHandle(){
	return this->handle;
}

void CommandLine::setHandle(Handle handle){
	this->handle = handle;
}

string CommandLine::toString(){
	return "";
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
	if(getline(cmd_buffer, str)){
		handleCmd(str);
		*output << endl << ">> ";
	}
	cmd_buffer.clear();
	cmd_mtx.unlock();
}

void CommandLine::cmdLoop(istream *input, mutex *cmd_mtx, stringstream *cmd_buffer){
	string str;
	regex white_space("\\s+");
	regex white_space_begin("^ ");
	regex white_space_end(" $");
	while (getline(*input, str)){
		str = toLower(str);
		str = regex_replace(str, white_space, " ");
		str = regex_replace(str, white_space_begin, "");
		str = regex_replace(str, white_space_end, "");
		cmd_mtx->lock();
		(*cmd_buffer) << toLower(str) << endl;
		cmd_mtx->unlock();
	}
}

void CommandLine::handleCmd(std::string cmd){
	static regex match_command("^((\\w|-)+) ?");
	static regex match_parameters("^(-\\w+) ?(.*)");
	static regex parameter_value("^(((\\w|_)+\\.(\\w|_)+|-?\\d+\\.\\d+|(\\w|_)+)) ?");
	string str, command, parameter, values, value;
	cmatch m;
	map<string, list<string> > parameter_list;
	regex_search(cmd.c_str(), m, match_command);

	command = m[1];
	str = m.suffix().str();
	while (regex_search(str.c_str(), m, match_parameters)){
		parameter = m[1];
		values = m[2];
		parameter_list[parameter];
		while (regex_search(values.c_str(), m, parameter_value)){
			str = parse(m[1]);
			if (str != m[1])
				values = str + " " + m.suffix().str();
			else {
				parameter_list[parameter].push_back(parse(m[1]));
				values = m.suffix().str();
			}
		}
		str = values;
	}

	/* DEBUG */
	cout << command << ": " << endl;
	for (map<string, list<string> >::iterator it = parameter_list.begin(); it != parameter_list.end(); ++it){
		cout << it->first << ": ";
		for (list<string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
			cout << "|" << *it2 << "|";
		}
		cout << endl;
	}
	

	
	try {
		if (command == "help" || command == "h") {
			helpCmd(parameter_list);
		}
		else if (command == "set" || command == "s") {
			set(parameter_list);
		}
		else if (command == "list-objects" || command == "lo") {
			*output << m_getWorld()->listObjects() << endl;
		}
		else if (command == "list-configurations" || command == "lc"){
			*output << ConfigSettings::config->toString();
		}
		else if (command == "print" || command == "p") {
			print(parameter_list);
		}
		else if (command == "create" || command == "c"){
			createObject(parameter_list);
		}
		else if (command == "run" || command == "r"){
			runFile(parameter_list);
		}
		else {
			invalidCommand();
		}
	}
	catch (CmdException e){
		*output << e.what() << endl;
	}
}

void CommandLine::help(){
	*output << "Commands:" << endl;
	*output << "list-objects | lo: list the global objects" << endl;
	*output << "list-configurations | lc: list the default configurations" << endl;
	*output << "set | s: set some property in the world" << endl;
	*output << "print | p: print some information about the world" << endl;
	*output << "create | c: create a new object" << endl;
	*output << "run | r: run commands in a file" << endl;
}

void CommandLine::helpSet(){
	*output << "Set command:" << endl;
	*output << "[set | s] <parameters>			-- set parameters of objects and configurations" << endl;
	*output << "-i [index]						-- index of the object" << endl;
	*output << "-n [object_name]				-- name of the objet" << endl;
	*output << "-p [x] [y] [z]					-- position" << endl;
	*output << "-f <flag> [true|false]			-- flag" << endl;
	*output << "-ai <steering_behavior>			-- AI" << endl;
	*output << "-c <configuration> [new_value]	-- set a configuration to a new value" << endl;
	*output << "Obs: If -i and -n are expecified the object in the index will be stored with the expecified name." << endl;
	helpFlags();
	helpSteeringBehaviors();
}

void CommandLine::helpPrint(){
	*output << "Print command:" << endl;
	*output << "[print | p] <parameters> -- print the information of objects by ID" << endl;
	*output << "-i [id]" << endl;
	*output << "-n [object_name]" << endl;
}

void CommandLine::helpCreate(){
	*output << "Create command:" << endl;
	*output << "[create | c] <parameters>"<< endl;
	*output << "-t [[autonomous | a]] -- the type of object to be created" << endl;
	*output << "-p [x] [y] [z] -- position" << endl;
	*output << "-n [object_name]" << endl;
}

void CommandLine::helpRun(){
	*output << "Run command:" << endl;
	*output << "run <parameters>" << endl;
	*output << "-n [file_name.txt]" << endl;
}

void CommandLine::helpFlags(){
	*output << "Flags:" << endl;
	*output << "-follow_track" << endl;
}

void CommandLine::helpSteeringBehaviors(){
	*output << "Steering Behaviors:" << endl;
	*output << "wander" << endl;
	*output << "pursuit [index or name of the target]" << endl;
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

void CommandLine::helpCmd(map<string, list<string> > &parameter){
	string str;

	if (parameter.size() != 0){
		str = parameter.begin()->first;

		if (str == "-set"){
			helpSet();
		}
		else if (str == "-print"){
			helpPrint();
		}
		else if (str == "-create"){
			helpCreate();
		}
		else if (str == "-object_type"){
			helpObjectType();
		}
		else if (str == "-run"){
			helpRun();
		}
	}
	else {
		help();
	}
}

IHasHandle *CommandLine::findObjectByIndex(int id){
	Handle handle = m_getWorld()->getGlobalObjectByIndex(id);

	if (handle.id == -1)
		throw CmdException("Object did not find!", false);

	IHasHandle *obj = m_getObject(handle);

	if (obj == nullptr)
		throw CmdException("Null pointer exception!", false);

	return obj;
}

IHasHandle *CommandLine::translateObject(std::string str){
	IHasHandle *obj;
	stringstream buffer;
	int id;
	// If object not in the dictionary
	if (dictionary.find(str) == dictionary.end()){
		buffer << str;
		buffer >> id;
		obj = findObjectByIndex(id);
	}
	else {
		obj = m_getObject(dictionary[str]);
		if (obj == nullptr)
			throw CmdException("Null pointer exception!", false);
	}

	return obj;
}

string CommandLine::parse(string str){
	static regex rexp("(\\w+)\\.(\\w+)");
	MovingObject *mObj;
	cmatch m;
	string tmp = "";
	if (regex_match(str.c_str(), m, rexp)){
		if (m[2] == "position"){
			if (dictionary.find(m[1]) != dictionary.end()){
				mObj = dynamic_cast<MovingObject*>(m_getObject(dictionary[m[1]]));

				if (mObj != nullptr){
					tmp += Common::toString(mObj->getPosition()[0]) + " ";
					tmp += Common::toString(mObj->getPosition()[1]) + " ";
					tmp += Common::toString(mObj->getPosition()[2]);
				}
				else {
					throw CmdException("Null pointer!", false);
				}
			}
			else {
				throw CmdException("Invalid object name!", false);
			}
		}
		else {
			tmp = str;
		}
	}
	else {
		tmp = str;
	}
	
	return tmp;
}

bool CommandLine::setParameter(map<string, string> &param, string parameter, list<string> values){
	list<string>::iterator it = values.begin();
	string str;

	if (parameter == "-t"){
		if (values.size() != 1)
			throw CmdException("-t Invalid amount of parameters!", false);
		str = *it;
		if (str == "a")
			str = "autonomous";
		param["type"] = str;
	}
	else if (parameter == "-o"){
		if (values.size() != 1)
			throw CmdException("-o Invalid amount of parameters!", false);
		str = *it;
		if (!validObjectType(str))
			throw CmdException("Invalid object type!", false);
		param["object_type"] = str;
	}
	else if (parameter == "-n"){
		if (values.size() != 1)
			throw CmdException("-n Invalid amount of parameters!", false);
		str = *it;
		if (str[0] >= '0' && str[0] <= '9') {
			throw CmdException("Invalid name!", false);
		}
		param["name"] = str;
	}
	else if (parameter == "-p"){
		if (values.size() != 3)
			throw CmdException("-p Invalid amount of parameters!", false);
		param["position"] = "true";
		param["x"] = *it; ++it;
		param["y"] = *it; ++it;
		param["z"] = *it;
	}
	else if (parameter == "-i"){
		if (values.size() != 1)
			throw CmdException("-i Invalid amount of parameters!", false);
		param["index"] = *it;
	}
	// AI
	else if (parameter == "-ai"){
		if (values.size() < 1)
			throw CmdException("-ai Invalid amount of parameters!", false);
		param["ai"] = *it; ++it;
		if (values.size() >= 2)
			param["ai:param_1"] = *it;
	}
	else if (parameter == "-w"){
		if (values.size() < 1)
			throw CmdException("-w Invalid amount of parameters!", false);
		param["what"] = *it;
	}
	else if (parameter == "-f"){
		if (values.size() < 2)
			throw CmdException("-f Invalid amount of parameters!", false);
		param["flag"] = *it; ++it;
		param["flag:value"] = *it;
	}
	else if (parameter == "-c"){
		if (values.size() < 2)
			throw CmdException("-c Invalid amount of parameters!", false);
		param["configuration"] = *it; ++it;
		param["configuration:value"] = *it;
	}
	else if (parameter == "-d"){
		if (values.size() < 1)
			throw CmdException("-d Invalid amount of parameters!", false);
		param["do"] = "true";
		param["do:what"] = *it;
	}
	else {
		return false;
	}
	return true;
}

void CommandLine::set(map<string, list<string> > &parameter){
	string str;
	map<string, string> param;
	IHasHandle *obj;

	try {
		for (map < string, list<string> >::iterator it = parameter.begin(); it != parameter.end(); ++it){
			if (!setParameter(param, it->first, it->second))
				throw CmdException("Invalid parameter!");
		}

		if (param.find("index") != param.end()){
			obj = translateObject(param["index"]);

			if (param.find("name") != param.end()){
				*output << param["name"] << " <-- " << toString(ObjectTypes(obj->getType())) << endl;
				dictionary[param["name"]] = obj->getHandle();
			}
		}
		else if (param.find("name") != param.end())
			obj = translateObject(param["name"]);
		else
			throw CmdException("Identifier not expecified!", false);

		if (param.find("position") != param.end() || param.find("ai") != param.end() || param.find("flag") != param.end()){
			setObject(param, obj);
		}

		if (param.find("configuration") != param.end()){
			if (param.find("configuration:value") == param.end())
				throw CmdException("Value to be setted not expecified", false);
			ConfigSettings::config->updateValue(param["configuration"], param["configuration:value"]);
		}
	}
	catch (CmdException e){
		*output << e.what() << endl;
		helpSet();
		return;
	}
}

void CommandLine::setObject(map<string, string> &param, IHasHandle *obj){
	MovingObject *mObj;
	AutonomousObject *aObj;

	if (param.find("position") != param.end()){
		mObj = dynamic_cast<MovingObject*>(obj);
		if (mObj == nullptr)
			throw CmdException("Object expecified is not a MovingObject!", false);

		mObj->setPos(toFloat(param["x"]), toFloat(param["y"]), toFloat(param["z"]));
	}

	if (param.find("ai") != param.end()){
		aObj = dynamic_cast<AutonomousObject*>(obj);
		if (aObj == nullptr)
			throw CmdException("Object expecified is not an autonomousObject!", false);

		if (param.find("ai:param_1") != param.end()){
			if (param["ai"] == "pursuit"){
				IHasHandle *obj = translateObject(param["ai:param_1"]);

				if (!aObj->setOnSteeringBehavior(BehaviorType::pursuit, obj->getHandle()))
					throw CmdException("Invalid behavior type");
			}
			if (param["ai"] == "evade"){
				IHasHandle *obj = translateObject(param["ai:param_1"]);

				if (!aObj->setOnSteeringBehavior(BehaviorType::evade, obj->getHandle()))
					throw CmdException("Invalid behavior type");
			}
		}
		else {
			if (!aObj->setOnSteeringBehavior(SteeringBehavior::toBehaviorType(param["ai"])))
				throw CmdException("Invalid behavior type: " + param["ai"], false);
		}
		
	}

	if (param.find("do") != param.end()){
		if (param["do:what"] == "init"){
			mObj = dynamic_cast<MovingObject*>(obj);
			if (mObj == nullptr)
				throw CmdException("Object expecified is not a MovingObject!", false);
			mObj->init();
		}
	}

	if (param.find("flag") != param.end()){
		mObj = dynamic_cast<MovingObject*>(obj);
		if (mObj == nullptr)
			throw CmdException("Object expecified is not a MovingObject!", false);

		if (!mObj->setFlag(param["flag"], Common::toBool(param["flag:value"])))
			throw CmdException("Invalid flag!", false);
	}
}

void CommandLine::createObject(map<string, list<string> > &parameter){
	stringstream buffer;
	string str;
	AutonomousObject *obj;
	map< string, string > param;

	try {
		// default parameters
		param["object_type"] = "ecoli";
		param["x"] = param["y"] = param["z"] = Common::toString(0.0f);

		for (map<string, list<string> >::iterator it = parameter.begin(); it != parameter.end(); ++it){
			if (!setParameter(param, it->first, it->second))
				throw CmdException("Invalid parameter!", false);
		}

		if (param["type"] == "autonomous"){
			obj = dynamic_cast<AutonomousObject*>(Game::getGlobalInstance()->invoke(ObjectTypes::RedBlood));
			m_getWorld()->allocateHandle(obj, HandleType::GLOBAL);
			m_getWorld()->insert(obj);
		}
		else {
			throw CmdException("Fail to expecify object type to be created!", false);
		}

		if (param.find("name") != param.end()) {
			*output << param["name"] << " <-- " << param["object_type"] << endl;
			dictionary[param["name"]] = obj->getHandle();
		}
		else {
			*output << "res" + Common::toString(allocator) << " <-- " << param["object_type"] << endl;
			dictionary["res" + Common::toString(allocator)] = obj->getHandle();
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

void CommandLine::print(map<string, list<string> > &parameter){
	stringstream buffer;
	string str;
	map<string, string> param;
	IHasHandle *obj;

	try{
		for (map<string, list<string> >::iterator it = parameter.begin(); it != parameter.end(); ++it){
			if (!setParameter(param, it->first, it->second))
				throw CmdException("Invalid parameter!", false);
		}

		if (param.find("index") != param.end() || param.find("name") != param.end()) {
			if (param.find("index") != param.end())
				obj = translateObject(param["index"]);
			else
				obj = translateObject(param["name"]);
			*output << obj->toString() << endl;
		}

		if (param.find("configuration") != param.end()){
			if (!ConfigSettings::config->getValue(param["configuration"], str))
				throw CmdException("Invalid configuration!", false);
			*output << str << endl;
		}

	}
	catch (CmdException e){
		*output << e.what() << endl;
		helpPrint();
	}
}

void CommandLine::runFile(map<string, list<string> > &parameter){
	if (parameter.find("-n") == parameter.end()){
		helpRun();
		throw CmdException("File name not expecified!", false);
	}
	string str = *parameter["-n"].begin();
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
