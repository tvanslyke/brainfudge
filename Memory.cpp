/*
 * Memory.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */
#include "Memory.h"
#include <iostream>
Memory::Memory()
{
	mem = std::vector<unsigned char>(30000, 0);
	pos = 15000;
}

Memory::Memory(size_t nbytes)
{
	mem = std::vector<unsigned char>(nbytes, 0);
	pos = nbytes/2;
}

void Memory::operator-=(size_t nbytes)
{
	if( nbytes > pos)
	{
		// if the new position is out of bound, resize leftwards.
		size_t len = mem.size();
		mem.resize(((ptrdiff_t(pos)-nbytes) / mem.size() + 2) * mem.size());
		auto old_begin = mem.end() - len;
		std::move(mem.begin(), mem.begin() + len, old_begin);
		std::fill(mem.begin(), old_begin, 0);
		pos = (old_begin - nbytes) - mem.begin();
	}
	else
	{
		// otherwise decrement the pointer
		pos -= nbytes;
	}
}

void Memory::operator+=(size_t nbytes)
{
	// calculate the new position
	size_t newpos = pos + nbytes;

	if(newpos >= mem.size())
	{
		// if the new position is out of bound, resize rightwards.
		mem.resize((newpos / mem.size() + 1) * mem.size());
	}
	pos = newpos;
}
unsigned char & Memory::operator*()
{
	return mem[pos];
}
