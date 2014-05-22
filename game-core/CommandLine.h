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


class GAMECOREDLL CommandLine : public BaseObject
{
private:
	std::istream *input;
	std::ostream *output;
	std::stringstream cmd_buffer;
	std::mutex cmd_mtx;
	std::thread *input_thread;

public:
	CommandLine(std::istream *input, std::ostream *output);
	~CommandLine();

	void update(float);
	bool handleEvent(Event *evt);
	void readCmd();
	static void cmdLoop(std::istream *input, std::ostream *output, std::mutex *cmd_mtx, std::stringstream *cmd_buffer);
	void handleCmd(std::string cmd);
	void help();
	void setHelp();
	void printHelp();
	void invalidCommand();
	void set(std::stringstream &buffer);
	void print(std::stringstream &buffer);
	MovingObject *findObjectById(int);

};
