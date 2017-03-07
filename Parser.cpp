/*
 * Parser.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#include "Parser.h"
#include <stdexcept>
#include <functional>
#include <stack>
Parser::Parser(std::string fname):	file(fname, std::ios_base::in)
{
	if(not file)
	{
		throw std::runtime_error("File not found:\n" + fname);
	}
}

void Parser::parse(std::vector<InstructionSignature> & instructions, std::map<SigVecIter, SigVecIter> & cond_map)
{
	// current instruction
	char inst;
	// number of repetitions of current instruction.
	size_t reps = 0;
	// stack holding pending conditionals open '[' brackets.
	std::stack<size_t> cond_stack;
	// stack holding pending paired open '[' and closed ']' brackets.  Collapsed once 'instructions' is fully constructed.
	std::stack<std::pair<size_t, size_t>> paired_conds;

	// track row:col locations of unmatched open '[' brackets to report any errors to the user.
	size_t col = 1;
	size_t row = 1;
	std::stack<std::pair<size_t, size_t>> row_col_tracker;

	file.get(inst);

	// parse the entire file
	while(not file.eof())
	{
		// ignore comments and other non-instruction characters.
		if(valid_insts.count(inst) == 0)
		{
			if(inst == '\n')
			{
				++row;
				col = 1;
			}
			else
			{
				++col;
			}
			file.get(inst);
			continue;
		}
		// handle open '[' brackets with care
		else if(inst == '[')
		{
			instructions.emplace_back(inst, 1);
			reps = 0;
			cond_stack.push(instructions.size() - 1);
			row_col_tracker.emplace(row, col);
			file.get(inst);
			++col;
			continue;
		}
		// handle closed ']' brackets with care
		else if(inst == ']')
		{
			instructions.emplace_back(inst, 1);
			// report presence and location of an unmatched closed ']' bracket if needed.
			if(cond_stack.empty())
				throw std::runtime_error("[Error] Unmatched ']' conditional found in source. (r:" + std::to_string(row) + ", c:" + std::to_string(col) + ")");
			paired_conds.emplace(cond_stack.top(), instructions.size() - 1);
			cond_stack.pop();
			row_col_tracker.pop();
			reps = 0;
			file.get(inst);
			continue;
		}
		// handle the next non-conditional instruction.
		else
		{
			reps = 1;
			char next;
			// exhaust repetitions of the current instruction.
			while(not file.eof())
			{
				file.get(next);
				++col;
				if(next == inst)
				{
					++reps;
				}
				else
				{
					break;
				}
			}
			instructions.emplace_back(inst, reps);
			inst = next;
		}
	}
	if(not cond_stack.empty())
	{
		throw std::runtime_error("[Error] Unmatched '[' conditional found in source. (r:" +
								 std::to_string(row_col_tracker.top().first) + ", c:" +
								 std::to_string(row_col_tracker.top().second) + ")");
	}
	// collapse paired_conds and build cond_map
	auto cond_pair = paired_conds.top();
	auto inst_begin = instructions.begin();
	while(not paired_conds.empty())
	{
		cond_pair = paired_conds.top();
		cond_map.insert({inst_begin + cond_pair.first, inst_begin + cond_pair.second});
		cond_map.insert({inst_begin + cond_pair.second, inst_begin + cond_pair.first});
		paired_conds.pop();
	}
	file.close();
}



// valid instructions.
const std::set<char> Parser::valid_insts = {'>', '<', '+', '-', ',', '.', '[', ']'};









