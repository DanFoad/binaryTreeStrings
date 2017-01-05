#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

/* Create and set a max size for the queue. Can be changed if necessary */

#define maxSize 32

Node * nodeArray[maxSize];
int frontOfQueue = 0;
int endOfQueue = -1;
int queueSize = 0;

/* Return the first element in the queue, should be the only accessible one */

Node * peek(){
	return nodeArray[frontOfQueue];
}

/* if queue is emptied at any point, this resets all variables keeping track of the queue */

void resetQueue() {

	queueSize = 0;
	frontOfQueue = 0;

	/* -1 to indicate the queue is empty, along with queueSize as 0 */
	endOfQueue = -1;
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

	/* Only add an element if the size of the queue is less than the max size */

	if(queueSize < maxSize){

		/* Set to -1, if the number of elements is one less than max size */
		if(endOfQueue == maxSize - 1){
			endOfQueue = -1;
		}

		/* Add the element to the next place in the queue. if queue is full, element will replace nodeArray[0] */
		nodeArray[++endOfQueue] = Element;
		queueSize++;
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
	Node * toBeRemoved = nodeArray[frontOfQueue++];

	/* If the last element has been popped from the queue, reset the frontOfQueue to the start of the array again */
	if(frontOfQueue == maxSize){
		frontOfQueue = 0;
	}

	/* Reduce the size of the queue */
	queueSize--;
	return toBeRemoved;
}