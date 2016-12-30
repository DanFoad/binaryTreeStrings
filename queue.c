#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

#define maxSize 32

Node * nodeArray[maxSize];
int frontOfQueue = 0;
int endOfQueue = -1;
int queueSize = 0;

Node * peek(){
	return nodeArray[frontOfQueue];
}

void resetQueue() {
	queueSize = 0;
	frontOfQueue = 0;
	endOfQueue = -1;
}

int isEmpty(){
	if(queueSize == 0){ 
		return 1;
	}
	return 0;
}

int size(){
	return queueSize;
}

void push ( Node * Element){

	if(queueSize < maxSize){

		if(endOfQueue == maxSize - 1){
			endOfQueue = -1;
		}

		nodeArray[++endOfQueue] = Element;
		queueSize++;
	}
}

Node * pop(){
	if (queueSize == 0) return 0;
	Node * toBeRemoved = nodeArray[frontOfQueue++];

	if(frontOfQueue == maxSize){
		frontOfQueue = 0;
	}

	queueSize--;
	return toBeRemoved;
}