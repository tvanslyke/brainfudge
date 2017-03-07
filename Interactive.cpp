/*
 * Interactive.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: tim
 */

#include "Interactive.h"
#include <iostream>
#include <stdexcept>
#include <cassert>


const std::set<char> Interactive::valid_instrs = {'>', '<', '+', '-', ',', '.', '[', ']'};

const char* Interactive::GracefulExit::what() const noexcept
{
	return "Exiting.";
}

Interactive::Interactive()
{
	// TODO Auto-generated constructor stub
	memory = Memory(30000);
	instrs = "";
	pos = 0;
	brack_locs = std::set<size_t>();
	line = "";
}


void Interactive::extractFromLine()
{
	// inspect all characters in the current line.
	for(auto c:line)
	{
		if(valid_instrs.count(c))
		{
			instrs.push_back(c);
			if(c == '[' or c == ']')
			{
				brack_locs.insert(instrs.size() - 1);
			}
		}
	}
}
void Interactive::parseLine()
{

	if(not std::cin)
	{
		throw std::runtime_error("[Error] End-of-file detected while reading from stdin.");
	}
	// print a prompt and read the next entered line.
	std::cout << "\n>>> " << std::flush;
	std::getline(std::cin, line);
	std::cout << std::endl;
	// exit with success if "quit" is entered.
	if(line == "quit")
	{
		throw GracefulExit();
	}

}
char Interactive::getInstr()
{
	// if we are out of instructions, get new ones before continuing.
	if(pos == instrs.size())
	{
		size_t old_size = instrs.size();
		while(old_size == instrs.size())
		{
			parseLine();
			extractFromLine();
		}
	}
	return instrs[pos];
}
void Interactive::retreat()
{
	size_t count = 1;
	auto iter = brack_locs.find(pos);
	// find corresponding open '[' bracket.
	while(instrs[*iter] != '[' and count != 0)
	{
		--iter;
		count += (instrs[*iter] == ']') ? 1 : -1;
	}
	pos = *iter;
}
void Interactive::advance()
{
	size_t count = 1;
	auto iter = brack_locs.find(pos);
	assert(iter != brack_locs.end());
	assert(instrs[pos] == '[');
	auto end = brack_locs.end();
	// find corresponding closed ']' bracket.  Reads new instructions from user if necessary.
	while(instrs[*iter] != ']' and  count != 0)
	{
		++iter;
		count += (instrs[*iter]  == '[') ? 1 : -1;
		if(iter ==  end)
		{
			end = brack_locs.end();
			while(end == brack_locs.end())
			{
				getInstr();
			}
		}
	}
	pos = *iter;
}
void Interactive::run()
{
	for(;;)
	{
		switch(getInstr())
		{
		case '>':
			memory += 1;
			break;
		case '<':
			memory -= 1;
			break;
		case '+':
			(*memory)+=1;
			break;
		case '-':
			(*memory) -= 1;
			break;
		case '.':
			putchar(char(*memory));
			break;
		case ',':
			*memory = (unsigned char)getchar();
			break;
		case '[':
			if((*memory) == (unsigned char)(0))
				advance();
			break;
		case ']':
			if(not *memory == (unsigned char)(0))
				retreat();
			break;
		}
		// increment to the next instruction.
		++pos;
	}
}



