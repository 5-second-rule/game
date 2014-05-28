#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>
#include <regex>

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
	Handle handle;

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
	Handle getHandle();
	void setHandle(Handle);
	std::string toString();

	void readFile(std::string str);
	bool handleEvent(Event *evt);
	void readCmd();
	static void cmdLoop(std::istream *input, std::mutex *cmd_mtx, std::stringstream *cmd_buffer);
	void handleCmd(std::string cmd);
	std::string parse(std::string std);
	bool setParameter(std::map<std::string, std::string> &param, std::string parameters, std::list<std::string> values);
	void help();
	void helpSet();
	void helpPrint();
	void helpCreate();
	void helpRun();
	void helpFlags();
	void helpSteeringBehaviors();
	void helpObjectType();
	void invalidCommand();
	void helpCmd(std::map<std::string, std::list<std::string> > &parameter);
	void set(std::map<std::string, std::list<std::string> > &parameter);
	void setObject(std::map<std::string, std::string> &parameter, IHasHandle *obj);
	void print(std::map<std::string, std::list<std::string> > &parameter);
	void runFile(std::map<std::string, std::list<std::string> > &parameter);
	void createObject(std::map<std::string, std::list<std::string> > &parameter);
	bool validObjectType(std::string name);
	ObjectTypes toObjectType(std::string name);
	IHasHandle *findObjectByIndex(int);
	IHasHandle *translateObject(std::string str);

	static std::string toString(ObjectTypes type);
};
