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
void andBits(Bits a, Bits b, Bits res)
{

	res = makeBits(a->nwords);
	for (int index = 0; index <= BITS_PER_WORD - 1; index++) {
		res->words[index] = a->words[index] & b->words[index];
	}
	/*
	int mask;
	int a_index = a->nwords - 1;
	int b_index = b->nwords - 1;
	int res_index = res->nwords - 1;

	while ((a_index >= 0) && (b_index >= 0)) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			if ((a->words[a_index] & b->words[b_index]) & mask) {
				res->words[res_index] = mask;
			} else if (!(a->words[a_index] & b->words[b_index]) & mask) {
				res->words[res_index] = !mask;
			}
			j--;
			x++;
		}
		a_index--;
		b_index--;
		res_index--;
	}
	*/
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
	res = makeBits(a->nwords);
	for (int index = 0; index < BITS_PER_WORD - 1; index++) {
		res->words[index] = a->words[index] | b->words[index];
	}
	/*
	int mask;
	int a_index = a->nwords - 1;
	int b_index = b->nwords - 1;

	while ((a_index >= 0) && (b_index >= 0)) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			if ((a->words[a_index] | b->words[b_index]) & mask) {
				res->words[a_index] = res->words[a_index] | mask;
			}
			j--;
			x++;
		}
		a_index--;
		b_index--;
	}
	*/
}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
	/*
	tmp = calloc(sizeof(nwords*int));
	for tmp<-data
	for res<-tmp
	free(tmp)
	ret res
	*/

	res = makeBits(a->nwords);
	for (int index = 0; index < BITS_PER_WORD - 1; index++) {
		res->words[index] = ~a->words[index];
	}
	/*
	int mask;
	int a_index = a->nwords - 1;

	a_index = a->nwords - 1;
	while (a_index >= 0) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			if (a->words[a_index] & mask) {
				res->words[a_index] = res->words[a_index] | mask;
			}
			j--;
			x++;
		}
		a_index--;
	}
	*/
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
	int mask;
	int mask2;
	int b_index = b->nwords - 1;

	while (b_index >= 0) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			mask2 = (1u << (x+shift));
			if (b->words[b_index] & mask) {
				res->words[b_index+shift] = res->words[b_index+shift] | mask;
			}
			j--;
			x++;
		}
		b_index--;
	}
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
	int mask;
	int mask2;
	int b_index = b->nwords - 1;

	while (b_index >= 0) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			mask2 = (1u << (x+shift));
			if (b->words[b_index] & mask) {
				res->words[b_index+shift] = res->words[b_index+shift] | mask;
			}
			j--;
			x++;
		}
		b_index--;
	}
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{
	int mask;
	int from_index = from->nwords - 1;
	int to_index = to->nwords - 1;

	while (to_index >= 0) {
		to->words[to_index] = 0;
		to_index--;
	}

	while (from_index >= 0) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			if (from->words[from_index] & mask) {
				to->words[from_index] = to->words[from_index] | mask;
			}
			j--;
			x++;
		}
		from_index--;
	}
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{
	int mask;
	int i = strlen(bitseq) - 1;
	int index = b->nwords - 1;

	while (index >= 0) {
		b->words[index] = 0;
		index--;
	}

	index = b->nwords - 1;
	while (index >= 0) {
		int x = 0;
		int j = BITS_PER_WORD - 1;
		while ((j >= 0) && (i >= 0) && (x <= BITS_PER_WORD - 1)) {
			mask = (1u << x);
			if (bitseq[i] == '1') {
				b->words[index] = b->words[index] | mask;
			}
			j--;
			i--;
			x++;
		}
		index--;
	}
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{
	int mask;
	int words_index = b->nwords - 1;
	int i = 0;

	while (i <= words_index) {
		int j = BITS_PER_WORD - 1;

		while (j >= 0) {
			mask = (1u << j);
			if (mask & b->words[i]) printf("1");
			else printf("0");
			j--;
		}
		i++;
	}
}
