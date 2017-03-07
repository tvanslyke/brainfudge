/*
 * InstructionSignature.h
 *
 *  Created on: Mar 3, 2017
 *      Author: tim
 */

#ifndef INSTRUCTIONSIGNATURE_H_
#define INSTRUCTIONSIGNATURE_H_

#include <cstddef>

/**
 * POD struct containing an instruction and how many times it is repeated consecutively.
 * No need to hide data, const prevents tampering and data should be visible to all observers.
 */
struct InstructionSignature
{
	const char instr;
	const size_t reps;
	InstructionSignature(char c, size_t n);
};

#endif /* INSTRUCTIONSIGNATURE_H_ */
