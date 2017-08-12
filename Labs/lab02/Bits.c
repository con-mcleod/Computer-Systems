// ADT for Bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
	int nwords;   // # of Words
	Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
	Bits new;
	new = malloc(sizeof(struct BitsRep));
	assert(new != NULL);
	int  nwords;
	if (nbits%BITS_PER_WORD == 0)
		nwords = nbits/BITS_PER_WORD;
	else
		nwords = 1+nbits/BITS_PER_WORD;
	new->nwords = nwords;
	// calloc sets to all 0's
	new->words = calloc(nwords, sizeof(Word));
	assert(new->words != NULL);
	return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
	assert(b != NULL && b->words != NULL);
	free(b->words);
	free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res) {
	for (int i = 0; i <= a->nwords - 1; i++) {
		res->words[i] = a->words[i] & b->words[i];
	}
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res) {
	for (int i = 0; i <= a->nwords - 1; i++) {
		res->words[i] = a->words[i] | b->words[i];
	}
}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res) {
	for (int i = 0; i <= a->nwords - 1; i++) {
		res->words[i] = ~a->words[i];
	}
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
	 // challenge problem
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
	 // challenge problem
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to) {

	for (int i = to->nwords - 1; i >= 0; i--) {
		to->words[i] = 0;
	}

	for (int j = 0; j <= from->nwords - 1; j++) {
		to->words[j] = from->words[j];
	}
}

// assign a bit-string (sequence of 0's and 1's) to Bits.
// if the bit-string is longer than the size of Bits, truncate higher-order bits

void setBitsFromString(Bits b, char *bitseq) {

	int inputBits = strlen(bitseq) - 1;
	unsigned int mask;
	
	for (int index = b->nwords - 1; index >= 0; index--) {
		b->words[index] = 0;
		int maskShifter = 0;
		int maxBits = BITS_PER_WORD - 1;
		while ((maxBits >= 0) && (inputBits >= 0) && (maskShifter <= BITS_PER_WORD-1)) {
			mask = 1u << maskShifter;
			if (bitseq[inputBits] == '1') {
				b->words[index] = b->words[index] | mask;
			}
			maxBits--;
			inputBits--;
			maskShifter++;
		}
	}
}  

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b) {
	unsigned int mask;

	for (int i = 0; i <= b->nwords - 1; i++) {
		for (int bitCount = BITS_PER_WORD - 1; bitCount >= 0; bitCount--) {
			mask = 1u << bitCount;
			if (mask & b->words[i]) printf("1");
			else printf("0");
		}
	}
}