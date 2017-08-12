//Q4
int sumList(Node *L) {
	int sum = 0;
	if(L == NULL) return 0;
	else return L->value + sumList(L->next);
}

//Q5
int sumList(Node *L) {
	Node *curr = L;
	int sum = 0;
	while (curr != NULL) {
		sum += curr->value;
		curr = curr->next;
	}
	return sum;
}

//Q6
Node *append(Node *L, int v) {
	if (L == NULL) {
		L = newNode(v);
	} else {
		Node *curr = L;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newNode(v);
	}
	return L;
}

//Q7
Node *append(Node *L, int v) {
	if (L == NULL) {
		return newNode(v);
	} else {
		L->next = append(L->next, v);
	}
	return L;
}


void printBinary(int x) {
	int mask;

	for (int i = MAXINT - 1; i >= 0; i--) {
		mask = (1 << i);
		if (mask & x) printf("1");
		else printf("0");
	}
}

//Q10
device = (READING | LOCKED | AS_BYTES);