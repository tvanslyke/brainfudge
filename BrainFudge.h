/*
 * BrainFudge.h
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#ifndef BRAINFUDGE_H_
#define BRAINFUDGE_H_

#include <cstddef>
#include <vector>
#include <map>
#include "Parser.h"
#include "Memory.h"


/**
 * Top-level singleton object for interpreting a pre-written brainf@#k program.
 */
class BrainFudge
{
private:
	using SigVec = std::vector<InstructionSignature>;
	using SigVecIter = std::vector<InstructionSignature>::iterator;
	/** vector of sequential instruction signatures. */
	SigVec sigs;
	/** iterator to the end of 'sigs'. */
	SigVecIter end;
	/** iterator to the current instruction signature in 'sigs'. */
	SigVecIter instr;
	/** Binary search tree mapping iterators to  corresponding open '[' and closed ']' brackets in 'sigs'. */
	std::map<SigVecIter, SigVecIter> conditionals;
	/** Object encapsulating the memory allocated in the program.  Behaves similarly to a pointer. */
	Memory memory;
public:

	/**
	 *
	 * @param fname - name of file to interpret.
	 * @param allocate - number of bytes to initialize memory with.
	 */
	BrainFudge(std::string fname, size_t allocate = 30000);

	/**
	 * Runs the parsed brainf@*k program.
	 */
	void run();
};

#endif /* BRAINFUDGE_H_ */
