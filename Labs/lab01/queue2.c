// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

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


// create a new node for a Queue
static QueueNode *makeQueueNode(int id, int size)
{
	//create new node
	QueueNode *new;
	new = malloc(sizeof(struct QueueNode));
	//check that it now exists
	assert(new != NULL);

	//initialise the variables for the new node
	new->jobid = id;
	new->size = size;
	new->next = NULL;

	//return the node
	return new;
}

// make a new empty Queue
Queue makeQueue() {

	//create new queue
	Queue new;
	new = malloc(sizeof(struct QueueRep));
	//check that it now exists
	assert(new != NULL);

	//initialise the variables for the new queue
	new->nitems = 0; 
	new->head = NULL;
	new->tail = NULL;

	//return the queue
	return new;
}

// release space used by Queue
void freeQueue(Queue q) {

	//check that queue exists
	assert(q != NULL);
	//free the queue
	free(q);
}

// add a new item to tail of Queue
void enterQueue(Queue q, int id, int size) {

	//check queue exists
	assert(q != NULL);

	//create new node to be added, check it exists and assign variables
	QueueNode *new_node = makeQueueNode(id, size);
	assert(new_node != NULL);

	//create node for checking curr node variables
	QueueNode *curr = q->head;

	//case where empty queue
	if (q->head == NULL) {
		q->head = new_node;
		q->tail = new_node;
		q->nitems++;
	}
	//else case where queue is not empty, iterate through queue
	else {
		while (curr->next != NULL) {
			curr = curr->next; 
		}
		curr->next = new_node;
		q->tail = new_node;
		q->nitems++;
	}
}

// remove item on head of Queue
int leaveQueue(Queue q) {

	//check queue exists
	assert(q != NULL);

	//create node for checking curr node variables
	QueueNode *curr_node = q->head;
	
	//if queue is empty, return
	if (q->head == NULL) {
		return 0;
	}
	else {
		//if queue has 1 item, remove it
		if (q->nitems == 1) {
			q->head = NULL;
			q->tail = NULL;
			int id = curr_node->jobid;
			free(curr_node);
			q->nitems--;
			return id;
		} //if queue has multiple items, remove the head
		else {
			q->head = curr_node->next;
			int id = curr_node->jobid;
			free(curr_node);
			q->nitems--;
			return id;
		}
	}
}

// count # items in Queue
int lengthQueue(Queue q) {
	assert(q != NULL);
	return q->nitems;
}

// return total size in all Queue items
int volumeQueue(Queue q) {
	QueueNode *curr_node = q->head;
	int sum;
	assert(q != NULL);
	if (q->head == NULL) {
		return 0;
	}
	else {
		sum = 0;
		while (curr_node != NULL) {
			sum = sum + curr_node->size;
			curr_node = curr_node->next;
		}
	}
	return sum;
}

// return size/duration of first job in Queue
int nextDurationQueue(Queue q) {
	QueueNode *curr_node = q->head;
	assert (q != NULL);
	if (q->head == NULL) {
		return 0;
	}
	return curr_node->size;
}

// display jobid's in Queue
void showQueue(Queue q) {
	QueueNode *curr;
	curr = q->head;
	while (curr != NULL) {
		printf(" (%d,%d)", curr->jobid, curr->size);
		curr = curr->next;
	}
}
