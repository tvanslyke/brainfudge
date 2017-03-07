/*
 * Main.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#include "BrainFudge.h"
#include "Interactive.h"
#include <iostream>

/**
 * @param argc - number of command-line args. (should be no greater than 2)
 * @param argv - tokenized command-line args.
 * @return exit status (0 for success or 1 for failure)
 */
int main(int argc, char *argv[] )
{
	if(argc == 1)
	{
		std::ios_base::sync_with_stdio(true);
		// run as an interactive interpreter
		Interactive interactive;
		try
		{
			interactive.run();
		}
		catch(Interactive::GracefulExit & g)
		{
			std::cout << g.what() << std::endl;
			return 0;
		}
		catch(std::exception & e)
		{
			std::cout << e.what() << std::endl;
			return 1;
		}
	}
	else
	{
		std::string arg = argv[1];
		if(arg == "help" or arg == "-h" or arg == "--help" or arg == "-help")
		{
			std::cout <<    "A brainf@#k interpreter.  Supports an interactive mode and an optimizing source-code interpreter.\n\n"
					"Usage:\n"
					"\tWith pre-written brainf@#k code\n"
					"\t\t$ ./brainfudge <source code file>\n"
					"\tInteractive mode\n"
					"\t\t$ ./brainfudge\n" 
					"\tInteractive mode can be exited by issuing the 'quit' command."<< std::endl;
		}
		else
		{
			try
			{
				BrainFudge bf = BrainFudge(arg);
				bf.run();
			}
			catch(std::exception & e)
			{
				std::cout << e.what() << std::endl;
				return 1;
			}
		}

	}
	return 0;
}

