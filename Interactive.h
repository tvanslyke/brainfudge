/*
 * Interactive.h
 *
 *  Created on: Mar 5, 2017
 *      Author: tim
 */

#ifndef INTERACTIVE_H_
#define INTERACTIVE_H_
#include "Memory.h"
#include <set>
#include <stdexcept>
#include <string>

/**
 * Top-level singleton object for dynamically interpreting brainf@#k code in a command-line interface.
 */
class Interactive
{
private:
	/** Object encapsulating the memory allocated in the program.  Behaves similarly to a pointer. */
	Memory memory;
	/** String containing valid sequential brainf@#k instructions. */
	std::string instrs;
	/** Position in 'instrs' of current instruction. */
	size_t pos;
	/** Binary Search Tree containing locations of open '[' and closed ']' brackets in 'instrs'. */
	std::set<size_t> brack_locs;
	/** String containing most recent line from stdin. */
	std::string line;

	/** Set containing valid brainf@#k instructions as characters. */
	static const std::set<char> valid_instrs;

	/**
	 * Extracts valid brainf@#k instructions from 'line' and adds them to 'instrs'.
	 * Additionally, this method will add the positions of any open '[' and closed ']' brackets to 'brack_locs'.
	 */
	void extractFromLine();
	/**
	 * Reads line from stdin and stores the result in 'line'.  extractFromLine() is called to extract
	 * valid instructions from the line.
	 */
	void parseLine();

	/**
	 * Retrieves the next instruction.  Calls parseLine() when instructions stored in 'instrs' are exhausted.
	 * @return the next instruction as an ascii character
	 */
	char getInstr();

	/**
	 * Moves 'pos' to the previous open '[' bracket corresponding to the current closed ']' bracket.
	 */
	void retreat();
	/**
	 * Moves 'pos' to the next closed ']' bracket corresponding to the current open '[' bracket.
	 */
	void advance();
public:

	/**
	 * Class to exit gracefully if the user issues the special 'exit' command.
	 * This simplifies the problem of returning with the proper exit code (0) in the middle of program execution.
	 */
	class GracefulExit: public std::exception
	{
	public:
		/**
		 * @return "Exiting.".
		 */
		const char* what() const noexcept;
	};
	/**
	 * Construct an 'Interactive' object.
	 */
	Interactive();
	/**
	 * Start the command-line interpreter.
	 */
	void run();
};

#endif /* INTERACTIVE_H_ */
