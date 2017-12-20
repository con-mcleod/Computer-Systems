#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct list {
	int x;
	struct list *next;
};

struct lrep {
	struct list *head;
	struct list *tail;
	void (*insert)(int insertee, struct lrep * head);
	void (*delete)(int deletee,  struct lrep * head);
	void (*fwrite)(char *s, struct lrep * lrep);
	void (*printl)(struct lrep * head);
	struct list * (*create_node)(int val);
};


struct lrep *lrep;

//creates a node
struct list *CN(int val){
	struct list *n = malloc(sizeof(struct list));
	assert(n != NULL);
	n->x = val;
	n->next = NULL;
	return n;
};

//TODO INSERTION SORT
void IN(int x, struct lrep * lrep) {
	printf("write insert %d\n", x);
	struct list newNode = *CN(x);

	if (lrep->head == NULL) {
		lrep->head = &newNode;
		newNode.next = lrep->tail;
	} else {
		lrep->tail = &newNode;
	}
}

//TODO FIND AND REMOVE ElEM
void DEL(int x, struct lrep * lrep){

	printf("write delete\n");
	exit(0);
}

//TODO CREATE AND WRITE SPACE SEPARATED ELEMS TO FILE SPECIFIED AS FILE NAME WITH A NEWLINE AT END
void WRITE(char * filename, struct lrep * lrep){
	printf("write write ;)\n");
	exit(0);
}

//TO PRINT LIST
void PRINTL(struct lrep * lrep){
	printf("print the list\n");

	for (int i = 0; i<)

	exit(0);
}

int main(void){

	//init lrep
	lrep = malloc(sizeof(struct lrep));
	lrep->head = NULL;
	lrep->tail = NULL;
	lrep->insert = &IN;
	lrep->delete = &DEL;
	lrep->fwrite = &WRITE;
	lrep->printl = &PRINTL;
	lrep->create_node = &CN;

	printf("inserting elems\n");
	//insert some elements
	lrep->insert(1, lrep);
	lrep->insert(3, lrep);
	lrep->insert(5, lrep);
	lrep->insert(7, lrep);
	lrep->insert(2, lrep);
	lrep->insert(4, lrep);
	lrep->insert(6, lrep);

	printf("inserted\n");

	printf("testing correct insert\n");

	//test order is correct
	struct list *tmp = lrep->head;
	assert(tmp != NULL);
	for (int i = 1; i < 9; i++){
		if (i != tmp->x) assert("LIST NOT ORDERED");
		tmp = tmp->next;
	}

	printf("passed\n");
	lrep->printl(lrep);

	printf("deleting elems\n");

	//remove even nums
	lrep->delete(2, lrep);
	lrep->delete(4, lrep);
	lrep->delete(6, lrep);

	printf("deleted\n");
	printf("testing correct delete\n");


	//check even nums removed
	tmp = lrep->head;
	assert(tmp != NULL);

	while (tmp != NULL){
		if (tmp->x % 2 == 0) assert("LIST NOT ODD ELEMS NOT REMOVED CORRECTLY");
		tmp = tmp->next;
	}

	printf("passed\n");

	/* possible bugs lie ahead !!!!!!!!! */
	printf("testing write to file\n if you've gotten this far there may be bugs in this test\n");

	//write to file to test
	FILE *fptr = fopen("test.txt", "w");
	fprintf(fptr, "1 3 5 7\n");
	fclose(fptr);

	//use implementation
	lrep->fwrite("test1.txt", lrep);

	fptr = fopen("test.txt", "r");
	FILE *fp = fopen("test1.txt", "r");

	char buf[9];
	char buf1[9];
	//copy contents to buffers
	fscanf(fptr, "%s", buf);
	fscanf(fp, "%s", buf1);

	//compare them
	if (strcmp(buf, buf1)){
		printf("WRITE NOT WORKING\n");
	}
	printf("passed\n");

	printf("ALL TESTS PASSED, YOU ARE AWESOME! :)\n");

	return 0;
}
