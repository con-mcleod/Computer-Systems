// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by Callum Bennett and Connor McLeod

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {   
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};

// TODO:
// remove the #if 0 and #endif
// once you've added code to use this function

// create a new node for a Queue
static
QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}

// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0;
   new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
   assert(q != NULL);
   free(q);
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
	//check q exists
   assert(q != NULL);
   //create new node and initialise
   QueueNode *newNode = makeQueueNode(id, size);

   //create pointer to current node reference
   QueueNode *curr = q->head;

   //if queue is empty do:
   if (q->nitems > 0) {
   		while(curr->next != NULL) {
   			curr = curr->next;
   		}
		curr->next = newNode;
   }
   //else if queue is not empty do:
   else {
   		q->head = newNode;
   }

   //point to newNode and increase node counter
   q->tail = newNode;
   q->nitems++;
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);

   QueueNode *curr = q->head;

   // if queue is empty, return
   if (q->nitems == 0) return 0;
   // if queue has 1 item, do:
   else if (q->nitems == 1) {
   		int returnID = curr->jobid;
   		q->head = q->tail = NULL;
   		free(curr);
   		q->nitems--;
   		return returnID;
   // if queue has more than 1 node, do:
   } else {
   		int returnID = curr->jobid;
   		q->head = curr->next;
   		free(curr);
   		q->nitems--;
   		return returnID;
   }
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   //create variable to store the size of the queue
   int sizeCounter = 0;

   QueueNode *curr;

   //if queue is empty return 0
   if (q->nitems == 0) return 0;
   //else iteratively add each node's size
   else for (curr = q->head; curr != NULL; curr=curr->next) sizeCounter += curr->size;

   //return the count
   return sizeCounter;
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *curr = q->head;
   //if queue is empty return 0
   if(q->nitems == 0) return 0;
   //else return the size of first item in queue
   else return curr->size;
}

// used for statistics collection
/*
int queueLength(Queue q) {
	assert(q != NULL);

	QueueNode *curr = q->head;
	int length = 0;
	while(curr != NULL) length += 1;
	return length;
}
*/


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
	  printf(" (%d,%d)", curr->jobid, curr->size);
	  curr = curr->next;
   }
}
