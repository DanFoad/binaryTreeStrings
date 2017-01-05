#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

/* Create and set a max size for the queue. Can be changed if necessary */

/* Struct for linked list */
typedef struct listNode {
	Node *data;
	struct listNode *next;
} ListNode;

/* Create a node in linked list from data */

ListNode* createListNode(Node *data) {
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	node->next = 0;
	return node;
}

ListNode *listroot;
int queueSize = 0;

/* Return the first element in the queue, should be the only accessible one */

Node * peek(){
	return listroot;
}

/* if queue is emptied at any point, this resets all variables keeping track of the queue */

void resetQueue() {
	ListNode *temp = listroot;
	queueSize = 0;
	while (listroot != 0) {
		temp = listroot;
		listroot = temp->next;
		free(temp);
	}
}

/* Check to see if the queue is empty */

int isEmpty(){
	if(queueSize == 0){ 
		return 1;
	}
	return 0;
}

/* Return how many elements are present in the queue */

int size(){
	return queueSize;
}

/* Add a new element to the queue */

void push ( Node * Element){
	queueSize++;
	if (listroot == 0) {
		listroot = createListNode(Element);
		return;
	}
	/* Add the element to the next place in the queue. */
	ListNode *node = createListNode(Element);
	ListNode *traverse = listroot;
	while (traverse != 0) {
		if (traverse->next == 0) {
			traverse->next = node;
			return;
		}
		traverse = traverse->next;
	}
}

/* Remove the last element from the queue, then send the element to the user */

Node * pop(){

	/* Return 0 if user tries to pop an empty array */
	if (queueSize == 0){
		return 0;
	}

	/* Store the array at the front of the queue to be removed, increment front of queue for next time pop is used, 
	removing element from array */
	ListNode *toBeRemoved = listroot;

	if (toBeRemoved != 0) {
		listroot = toBeRemoved->next;
	}

	/* Reduce the size of the queue */
	queueSize--;
	return toBeRemoved->data;
}