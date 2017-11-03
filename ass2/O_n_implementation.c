// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017
// Modified and completed by Connor McLeod, z5058240

#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

// PTE = Page Table Entry

typedef struct {
	char status;      // NOT_USED, IN_MEMORY, ON_DISK
	char modified;    // boolean: changed since loaded
	int  frame;       // memory frame holding this page
	int  accessTime;  // clock tick for last access
	int  loadTime;    // clock tick for last time loaded
	int  nPeeks;      // total number times this page read
	int  nPokes;      // total number times this page modified
	bool last;
	// TODO: add more fields here, if needed ...
	
} PTE;

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries
static int  nPages;         // # entries in page table
static int  replacePolicy;  // how to do page replacement
static int  fifoList;       // index of first PTE in FIFO list
static int  fifoLast;       // index of last PTE in FIFO list

// Forward refs for private functions

static int findVictim(int);

// initPageTable: create/initialise Page Table data structures

void initPageTable(int policy, int np)
{
	PageTable = malloc(np * sizeof(PTE));
	if (PageTable == NULL) {
		fprintf(stderr, "Can't initialise Memory\n");
		exit(EXIT_FAILURE);
	}
	replacePolicy = policy;
	nPages = np;
	fifoList = 0;
	fifoLast = nPages-1;
	for (int i = 0; i < nPages; i++) {
		PTE *p = &PageTable[i];
		p->status = NOT_USED;
		p->modified = 0;
		p->frame = NONE;
		p->accessTime = NONE;
		p->loadTime = NONE;
		p->nPeeks = p->nPokes = 0;
	}
}

// requestPage: request access to page pno in mode
// returns memory frame holding this page
// page may have to be loaded
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

int requestPage(int pno, char mode, int time)
{
	if (pno < 0 || pno >= nPages) {
		fprintf(stderr,"Invalid page reference\n");
		exit(EXIT_FAILURE);
	}
	PTE *p = &PageTable[pno];
	int fno; // frame number
	switch (p->status) {
	case NOT_USED:
	case ON_DISK:

		// TODO: add stats collection
		countPageFault();

		fno = findFreeFrame();
		if (fno == NONE) {
			int vno = findVictim(time);
#ifdef DBUG
			printf("Evict page %d\n",vno);
#endif
			// TODO:
			PTE *vic = &PageTable[vno];

			// if victim page modified, save its frame
			if (vic->modified == 1) {
				saveFrame(vno);
			}

			// collect frame# (fno) for victim page
			fno = vic->frame;

			// update PTE for victim page
			// - new status
			vic->status = ON_DISK;
			// - no longer modified
			vic->modified = 0;
			// - no frame mapping
			// - not accessed, not loaded
			vic->frame = NONE;
			vic->accessTime = NONE;
			vic->loadTime = NONE;
		}
		printf("Page %d given frame %d\n",pno,fno);
		// TODO:
		// load page pno into frame fno
		loadFrame(fno, pno, time);

		// update PTE for page
		// - new status
		p->status = IN_MEMORY;
		// - not yet modified
		p->modified = 0;
		// - associated with frame fno
		p->frame = fno;
		// - just loaded
		p->loadTime = time;
		break;

	case IN_MEMORY:
		// TODO: add stats collection
		countPageHit();
		break;
	default:
		fprintf(stderr,"Invalid page status\n");
		exit(EXIT_FAILURE);
	}
	if (mode == 'r')
		p->nPeeks++;
	else if (mode == 'w') {
		p->nPokes++;
		p->modified = 1;
	}
	p->accessTime = time;
	return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy

static int findVictim(int time)
{
	int victim = NONE;
	int oldest = time;

	switch (replacePolicy) {
	case REPL_LRU:
		// TODO: implement LRU strategy
		
		// for (i = 0; i < #Pages; i++) {
		for (int i = 0; i < nPages; i++) {
			// P = PageTable[i]
			PTE *P = &PageTable[i];
			// if (P's accessTime < oldest)
			if (P->accessTime < oldest && P->accessTime != NONE) {
				// oldest = P's accessTime
				oldest = P->accessTime;
				// victim = P's page
				victim = i;
				// printf("i: %d nPages: %d victim: %d oldest: %d\n", i, nPages, victim, oldest);
			}
		}
		return victim;
	case REPL_FIFO:
		// TODO: implement FIFO strategy

		// for (i = 0; i < #Pages; i++) {
		for (int i = 0; i <nPages; i++) {
			// P = PageTable[i]
			PTE *P = &PageTable[i];
			// if (P's loadTime < oldest)
			if (P->loadTime < oldest && P->loadTime != NONE) {
				// oldest = P's loadTime
				oldest = P->loadTime;
				// victim = P's page
				victim = i;
			}
		}
		return victim;
	case REPL_CLOCK:
		return 0;
	}
	return victim;
}

// showPageTableStatus: dump page table
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

void showPageTableStatus(void)
{
	char *s;
	printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
			 "Page","Status","Mod?","Frame","Acc(t)","Load(t)","#Peeks","#Pokes");
	for (int i = 0; i < nPages; i++) {
		PTE *p = &PageTable[i];
		printf("[%02d]", i);
		switch (p->status) {
		case NOT_USED:  s = "-"; break;
		case IN_MEMORY: s = "mem"; break;
		case ON_DISK:   s = "disk"; break;
		}
		printf(" %6s", s);
		printf(" %4s", p->modified ? "yes" : "no");
		if (p->frame == NONE)
			printf(" %6s", "-");
		else
			printf(" %6d", p->frame);
		if (p->accessTime == NONE)
			printf(" %7s", "-");
		else
			printf(" %7d", p->accessTime);
		if (p->loadTime == NONE)
			printf(" %7s", "-");
		else
			printf(" %7d", p->loadTime);
		printf(" %7d", p->nPeeks);
		printf(" %7d", p->nPokes);
		printf("\n");
	}
}
