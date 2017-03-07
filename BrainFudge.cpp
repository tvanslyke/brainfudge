/*
 * BrainFudge.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */
#include "BrainFudge.h"
#include <iostream>


BrainFudge::BrainFudge(std::string fname, size_t allocate):memory(allocate)
{
	Parser parser(fname);

	// parse source code and read the results into 'sigs' and 'conditionals'.
	parser.parse(sigs, conditionals);

	end = sigs.end();
	instr = sigs.begin();
}


void BrainFudge::run()
{
	while(instr < end)
	{
		// choose the instruction.
		switch(char(instr->instr))
		{
		case '>':
			memory+=instr->reps;
			break;
		case '<':
			memory-=instr->reps;
			break;
		case '+':
			(*memory)+=instr->reps;
			break;
		case '-':
			(*memory) -= instr->reps;
			break;
		case '.':
			for(auto i = 0u; i < instr->reps; ++i)
				putchar(char(*memory));
			break;
		case ',':
			for(auto i = 0u; i < instr->reps; ++i)
				*memory = (unsigned char)getchar();
			break;
		case '[':
			if((*memory) == (unsigned char)(0))
				instr = conditionals[instr];
			break;
		case ']':
			if((*memory) != (unsigned char)(0))
				instr = conditionals[instr];
			break;
		}
		++instr;
	}
}
