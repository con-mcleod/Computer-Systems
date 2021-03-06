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
   // TODO: add more fields here, if needed ...
   int  next;
   int  prev;
} PTE;

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries
static int  nPages;         // # entries in page table
static int  replacePolicy;  // how to do page replacement

static int  firstPNO;       // index of first PTE in FIFO list
static int  lastPNO;       // index of last PTE in FIFO list

// Forward refs for private functions
static int findVictim(int);
static void addToList(PTE *p, int pno);
static void removeFromList(PTE *p, int pno);

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
   firstPNO = NONE;
   lastPNO = NONE;
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      p->status = NOT_USED;
      p->modified = 0;
      p->frame = NONE;
      p->accessTime = NONE;
      p->loadTime = NONE;
      p->nPeeks = p->nPokes = 0;
      p->next = NONE;
      p->prev = NONE;
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

   switch (p->status) {
   case NOT_USED:
   case ON_DISK:

      // TODO: add stats collection
      countPageFault();

      int fno = findFreeFrame();
      if (fno == NONE) {
         int vno = findVictim(time);
#ifdef DBUG
         printf("Evict page %d\n",vno);
#endif
         PTE *vic = &PageTable[vno];

         // if victim page modified, save its frame
         fno = vic->frame;
         if (vic->modified == 1) saveFrame(fno);
         // update PTE for victim page
         vic->status = ON_DISK;
         vic->modified = 0;
         vic->frame = vic->accessTime = vic->loadTime = NONE;

         // remove the victim from page table
         removeFromList(vic, vno);
      }
      printf("Page %d given frame %d\n",pno,fno);
      
      // load page pno into frame fno
      loadFrame(fno, pno, time);

      // update PTE for page
      p->status = IN_MEMORY;
      p->modified = 0;
      p->frame = fno;
      p->loadTime = time;

      // add new page into page table
      addToList(p, pno);
      break;

   case IN_MEMORY:
      // TODO: add stats collection
      countPageHit();
      if (replacePolicy == REPL_LRU) {
         // remove the entry that was accessed from PTE list
         removeFromList(p, pno);
         // re-add the entry that was accessed to end of PTE list
         addToList(p, pno);
      }
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

   // THESE PRINTS USEFUL FOR DEBUGGING
   // Prints each page's number, next and prev in the PTE List
   // and also notes the first and last items in the PTE List
   
   // printf("first_page=%d, first_page->next=%d\n", firstPNO, PageTable[firstPNO].next);
   // for (int i = 0; i < nPages; i++) {
   //    PTE *n = &PageTable[i];
   //    printf("Page=%d, page->prev=%d, page->next=%d\n",i,n->prev, n->next);
   // }
   // printf("last_page=%d, last_page->prev=%d\n",lastPNO, PageTable[lastPNO].prev);

   p->accessTime = time;
   return p->frame;
}

// addToList: adds the given page to the end of the PTE list
static void addToList(PTE *p, int pno) {
   if (lastPNO == NONE) firstPNO = pno;
   else PageTable[lastPNO].next = pno;
   p->next = NONE;
   p->prev = lastPNO;
   lastPNO = pno;
}

// removeFromList: removes the given page from the PTE list
static void removeFromList(PTE *p, int pno) {
   if (p->prev == NONE) firstPNO = p->next;
   else PageTable[p->prev].next = p->next;
   if (p->next == NONE) lastPNO = p->prev;
   else PageTable[p->next].prev = p->prev;
}

// findVictim: find the page to be replaced
// this page is always the first page in the PTE list
static int findVictim(int time)
{
   int victim = firstPNO;
   if (replacePolicy == REPL_CLOCK) return 0;
   else return victim;
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
