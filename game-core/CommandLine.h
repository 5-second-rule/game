#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "ServerGame.h"

class GAMECOREDLL CmdException : public exception
{
public:
	/// <summary> Construct a CmdException with a explanatory message.</summary>
	/// <param name="message">explanatory message</param>
	/// <param name="incSysMsg">true if system message (from strerror(errno)) 
	///  should be postfixed to the user provided message</param>
	CmdException(const string &message, bool inclSysMsg = false);

	/// <summary>Deconstructor</summary>
	~CmdException() _NOEXCEPT;

	/// <summary>Get the exception message</summary>
	/// <returns>exception message</returns>
	const char *what() const _NOEXCEPT;

private:
	/// <summary>Stores the exception message</summary>
	string userMessage;
};

const string str_init_file = "resources/init.txt";

class GAMECOREDLL CommandLine : public IHasHandle, public IUpdatable
{
private:
	std::istream *input;
	std::ostream *output;
	std::stringstream cmd_buffer;
	std::mutex cmd_mtx;
	std::thread *input_thread;
	std::map< std::string, Handle > dictionary;

	int allocator;

public:
	CommandLine(std::istream *input, std::ostream *output);
	~CommandLine();

	void update(float);
	void readFile(std::string str);
	bool handleEvent(Event *evt);
	void readCmd();
	static void cmdLoop(std::istream *input, std::mutex *cmd_mtx, std::stringstream *cmd_buffer);
	void handleCmd(std::string cmd);
	bool setParam(std::map<std::string, std::string> &param, std::string str, std::stringstream &buffer);
	void help();
	void helpSet();
	void helpPrint();
	void helpCreate();
	void helpObjectType();
	void invalidCommand();
	void helpCmd(std::stringstream &buffer);
	void set(std::stringstream &buffer);
	void print(std::stringstream &buffer);
	void runFile(std::stringstream &buffer);
	bool validObjectType(std::string name);
	ObjectTypes toObjectType(std::string name);
	void createObject(stringstream &buffer);
	MovingObject *findObjectByIndex(int);
	MovingObject *translateObject(std::string str);

	static std::string toString(ObjectTypes type);
};
