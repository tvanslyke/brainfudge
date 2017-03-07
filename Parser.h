/*
 * Parser.h
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include "InstructionSignature.h"
class Parser {
private:
	using SigVec = std::vector<InstructionSignature>;
	using SigVecIter = std::vector<InstructionSignature>::iterator;
	/** Source code.*/
	std::ifstream file;
	/** BST of valid instruction characters. */
	static const std::set<char> valid_insts;
public:
	/** Create a parser for a file. */
	Parser(std::string fname);
	/** Parses its source-code file into a vector of InstructionSignatures. */
	void parse(SigVec & instructions, std::map<SigVecIter, SigVecIter> & cond_map);

};

#endif /* PARSER_H_ */
