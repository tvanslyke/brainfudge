# brainfudge
An optimizing brainf@#k interpreter.  Supports an interactive mode and an optimizing source-code interpreter. 
Simulates infinite memory by dynamically resizing the allocated memory whenever the pointer is moved out-of-bounds in either direction.  

(see: https://en.wikipedia.org/wiki/Brainfuck)

Usage:
        With pre-written brainf@#k code
                $ ./brainfudge <source code file>
        Interactive mode
                $ ./brainfudge
        Interactive mode can be exited by issuing the 'quit' command at the prompt.

A makefile is included.  Requires support for C++11.

