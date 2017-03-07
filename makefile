objects = Main.o BrainFudge.o InstructionSignature.o Interactive.o Memory.o Parser.o

brainfudge: $(objects)
	g++ -std=c++11 $(objects) -o brainfudge
	make clean

Memory.o: Memory.h
	g++ -std=c++11 -c Memory.cpp

InstructionSignature.o: InstructionSignature.h InstructionSignature.cpp
	g++ -std=c++11 -c InstructionSignature.cpp

Parser.o: InstructionSignature.h Parser.h Parser.cpp
	g++ -std=c++11 -c Parser.cpp

Interactive.o: Memory.h Interactive.h Interactive.cpp
	g++ -std=c++11 -c Interactive.cpp

BrainFudge.o: Parser.h Memory.h BrainFudge.h BrainFudge.cpp
	g++ -std=c++11 -c BrainFudge.cpp

Main.o: BrainFudge.h Interactive.h
	g++ -std=c++11 -c Main.cpp
clean:
	rm $(objects)

