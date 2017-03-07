/*
 * Memory.h
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include <vector>
#include <cstddef>

/**
 * Class that simulates a pointer to byte in memory.
 * Protects from out-of-bounds access by expanding memory dynamically.
 */
class Memory {
private:
	/** The memory-space. */
	std::vector<unsigned char> mem;
	/** Position in memory. */
	size_t pos;
public:
	/** Initialize memory with 30000 bytes with pointer pointing to the middle byte. */
	Memory();
	/** Initialize memory with specified byte-width with pointer pointing to the middle byte. */
	Memory(size_t nbytes);
	/** Dereferences the byte being pointed to. */
	unsigned char & operator*();
	/** Safely decrements the pointer by 'nbytes' bytes. */
	void operator-=(size_t nbytes);
	/** Safely increments the pointer by 'nbytes' bytes. */
	void operator+=(size_t nbytes);

};

#endif /* MEMORY_H_ */
