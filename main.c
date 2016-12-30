//
//  main.c
//  binaryTree
//
//  Created by Alex Owen-Meehan on 17/11/2016.
//  Copyright © 2016 Alex Owen-Meehan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "binaryTree.h"
#include "queue.h"

void initNode(int data, Node **leaf) {
	*leaf = (Node*)malloc(sizeof(Node));
	(*leaf)->data = data;
	(*leaf)->left = 0;
	(*leaf)->right = 0;
}

void insert(int data, Node **root){

	Node *traverse;

	if (*root == 0) { /* If root doesn't exist */
		initNode(data, root);
		return;	
	}

	push(*root);

	while (!isEmpty()) {
		traverse = pop();

		if (traverse->left != 0) {
			push(traverse->left);
		} else {
			initNode(data, &(traverse)->left);
			resetQueue();
			return;
		}

		if (traverse->right != 0) {
			push(traverse->right);
		} else {
			initNode(data, &(traverse)->right);
			resetQueue();
			return;
		}
	}
}

void destroy_tree(Node *node) {
	if (node != 0) {
		destroy_tree(node->left);
		destroy_tree(node->right);
		free(node);
	}
}

int getDepth(Node *root) {
	if (root == 0) {
		return 0;
	}

	int leftDepth = getDepth(root->left);
	int rightDepth = getDepth(root->right);
	return leftDepth < rightDepth ? leftDepth + 1 : rightDepth + 1;
}

void printBinaryTree(Node *root){
    
    int currentCount, nextCount, depth, level, isFirst;
	currentCount = level = isFirst = 1;
	nextCount = 0;
	depth = getDepth(root);
    
	Node *traverse;

	if (root == 0) { /* If root doesn't exist */
		return;
	}

	push(root);

	while (!isEmpty()) {
		traverse = pop();
		--currentCount;

		if (isFirst) {
			int i;
			for (i = 0; i < pow(2, depth - level); i++) {
				printf("  ");
			}
			isFirst = 0;
		}

		if (traverse != 0) {
			if (traverse->data < 10) {
				printf("%d ", traverse->data);
			} else {
				printf("%d", traverse->data);
			}
			push(traverse->left);
			push(traverse->right);
			nextCount += 2;
		}

		int i;
		for (i = 0; i < 2*pow(2, depth - level + 1) - 2; i++) {
			printf(" ");
		}

		if (currentCount == 0) {
			printf("\r\n");
			currentCount = nextCount;
			nextCount = 0;
			++level;
			isFirst = 1;
		}
	}
	resetQueue();
}

int main(void) {
    
    int toBeCoverted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    int noOfDataSets = (sizeof(toBeCoverted)/sizeof(int));
    int count;
    
    Node *root = 0;
    
    for(count = 0; count < noOfDataSets; count++){
        insert(toBeCoverted[count], &root);
    }

	printBinaryTree(root);
    
    return 0;
}
