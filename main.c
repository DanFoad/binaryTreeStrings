/** main.c
 *	Binary Tree - Strings implementation
 *	Created by Dan Foad and Alex Owen-Meehan
 *	Student IDs: 1526813, 1434732
 */

/* Include libraries and headers */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "binaryTree.h"
#include "queue.h"

/* Max length of strings in nodes */
#define MAXLENGTH 14

/** initNode
 * Initialise a node in the binary tree with given data and null children
 * @param char *data	String to hold inside of created node
 * @param Node **leaf	Reference to Node pointer to modify memory values
 */
void initNode(char *data, Node **leaf) {
	*leaf = (Node*)malloc(sizeof(Node));
	(*leaf)->data = data;
	(*leaf)->left = 0;
	(*leaf)->right = 0;
}

/** insertAtPoint
 * @param char *data	Data to insert at point in tree
 * @param Node **root	Root node of binary tree
 * @param char *parent	Name of parent node to insert under
 * @param int isChild	Whether to position left or right in LCRS system
 */
void insertAtPoint(char *data, Node **root, char *parent, int isChild) {
	Node *traverse; /* Temporary node to traverse tree with */

	/* If no root node, initialise root node with given data */
	if (*root == 0) {
		initNode(data, root);
		return;
	}

	/* Add root node to queue for level-order traversal */
	push(*root);

	/* Perform level-order traversal until chosen parent is found */
	while (!isEmpty()) {
		traverse = pop();

		/* If current node is the parent of new node to be created */
		if (strcmp(traverse->data, parent) == 0) {
			if (isChild) { /* Add to the left */
				if (traverse->left != 0) {
					/* If child node taken, recursively go to find next free node */
					insertAtPoint(data, root, (traverse->left)->data, 0);
				} else {
					initNode(data, &(traverse)->left);
					resetQueue();
					return;
				}
			} else { /* Add to the right */
				if (traverse->right != 0) {
					/* If child node taken, recursively go to find next free node */
					insertAtPoint(data, root, (traverse->right)->data, 0);
				} else {
					initNode(data, &(traverse)->right);
					resetQueue();
					return;
				}
			}

			/* Reset the queue for other functions to use */
			resetQueue();
			return;
		}

		/* If current node is not parent, add children node to queue */
		if (traverse->left != 0) {
			push(traverse->left);
		}
		if (traverse->right != 0) {
			push(traverse->right);
		}
	}

	/* Reset the queue for other functions to use */
	resetQueue();
	return;
}

/** insert
 * Insert node at next available space
 * @param char *data	Data to insert at free spot in tree
 * @param Node **root	Reference to root node of tree
 */
void insert(char *data, Node **root){
	Node *traverse; /* Temporary node to traverse tree with */

	if (*root == 0) { /* If root doesn't exist */
		initNode(data, root);
		return;	
	}

	/* Add root node to queue for level-order traversal */
	push(*root);

	/* Perform level-order traversal until next free spot is found */
	while (!isEmpty()) {
		traverse = pop();

		/* If left child node is taken add to queue */
		if (traverse->left != 0) {
			push(traverse->left);
		} else { /* Otherwise, add data to free space and return */
			initNode(data, &(traverse)->left);
			resetQueue();
			return;
		}

		/* If right child node is taken add to queue */
		if (traverse->right != 0) {
			push(traverse->right);
		} else { /* Otherwise, add data to free space and return */
			initNode(data, &(traverse)->right);
			resetQueue();
			return;
		}
	}
}

/** getSize
 * Get size of binary tree
 * @param Node *root	Root node of tree to count elements
 * @return int			Number of nodes contained in binary tree
 */
int getSize(Node *root) {
	Node *traverse; /* Temporary node to traverse tree with */
	int count = 0;

	/* If root node is empty, tree size is 0 */
	if (root == 0) {
		return 0;
	}

	/* Add root node to queue for level-order traversal */
	push(root);

	/* Perform level-order traversal until all elements found */
	while (!isEmpty()) {
		traverse = pop();
		++count;

		if (traverse->left != 0) {
			push(traverse->left);
		}
		if (traverse->right != 0) {
			push(traverse->right);
		}
	}

	return count;
}

/** destroyTree
 * Recursively free all memory for elements in tree
 * @param Node *node	Node to free memory of
 */
void destroyTree(Node *node) {
	/* Perform post-order traversal to free up nodes in reverse order */
	if (node != 0) {
		destroyTree(node->left);
		destroyTree(node->right);
		free(node);
	}
}

/** getDepth
 * Get maximum depth of tree
 * @param Node *root	Root node of tree to traverse
 * @return int			Maximum depth of the tree
 */
int getDepth(Node *root) {
	/* If root node is empty, tree depth is zero */
	if (root == 0) {
		return 0;
	}

	/* Recursively get depth of tree */

	/* Find depth of left and right child nodes using post-order traversal */
	int leftDepth = getDepth(root->left);
	int rightDepth = getDepth(root->right);
	
	/* Return the depth of the deeper branch */
	return leftDepth < rightDepth ? leftDepth + 1 : rightDepth + 1;
}

/** getCountAtLevel
 * Get number of elements at a given depth of the tree through recursion
 * @param Node *node		Node to consider within tree
 * @param int currentDepth	Current depth of the node
 * @param int desiredDepth	The desired depth to reach and count
 * @return int				Count of elements at given level
 */
int getCountAtLevel(Node *node, int currentDepth, int desiredDepth) {
	/* If node is empty, don't add to count */
	if (node == 0) {
		return 0;
	}

	/* If at desired depth, add to count */
	if (currentDepth == desiredDepth) {
		return 1;
	}

	/* Get count recursively from branches until at desired depth */
	int count = 0;
	count += getCountAtLevel(node->left, currentDepth + 1, desiredDepth);
	count += getCountAtLevel(node->right, currentDepth + 1, desiredDepth);
	return count;
}

/** getLevels
 * Get count of each level in binary tree
 * @param Node *root	Root node of binary tree to traverse
 * @param int **levels	Reference to int array to store values in
 */
void getLevels(Node *root, int **levels) {
	int maxDepth = getDepth(root);
	int i;

	/* If tree is empty, no levels to consider */
	if (root == 0) {
		return;
	}

	/* Initialise each level to zero and assign memory */
	*levels = (int*)calloc(maxDepth, sizeof(int));

	/* Get count of each level and store in array */
	for (i = 0; i <= maxDepth; i++) {
		(*levels)[i] = getCountAtLevel(root, 0, i);
	}
}

/** centreString
 * Centre pad a string with spaces
 * @param char **str	Reference to string to centre pad
 */
void centreString(char **str) {
	char *temp; /* Temporary string to store value of text */
	int len = strlen(*str); /* Get length of input string */
	int i, j;

	/* Assign memory for temporary string */
	temp = (char*)malloc((len + 1) * sizeof(char));

	/* Copy input string to temporary one */
	strcpy(temp, *str);

	/* Clear input string by setting all memory within to zero */
	memset(*str, 0, len);

	/* Pad left side of string */
	for (i = 0; i < (MAXLENGTH - len) / 2; i++) {
		(*str)[i] = ' ';
	}

	/* Add original text to string */
	for (j = 0; i < ((MAXLENGTH - len) / 2) + len; i++, j++) {
		(*str)[i] = temp[j];
	}

	/* Pad right side of string */
	for (; i <= MAXLENGTH; i++) {
		(*str)[i] = ' ';
	}

	/* Null terminate string */
	(*str)[MAXLENGTH] = '\0';

	/* Free memory of temporary string */
	free(temp);
}

/** printNode
 * Add current node and it's parents arms to output array for printing
 * @param Node *node	Node to add to output array
 * @param int isLeft	Whether node is to to left of its parent
 * @param int offset	How far along the node is line of array
 * @param int depth		Current depth of node
 * @param char **output	Output array to modify for printing
 * @return int			How much space the node takes up to inform parent
 */
int printNode(Node *node, int isLeft, int offset, int depth, char **output) {
	int i;
	char *tempString; /* Temporary string to hold centre padded data value */

	/* If node is empty, return */
	if (node == 0) {
		return 0;
	}

	/* Create temporary string and copy data value to it */
	tempString = (char*)malloc((MAXLENGTH + 1) * sizeof(char));
	strcpy(tempString, node->data);
	tempString[MAXLENGTH] = '\0'; /* Null terminate temporary string */

	/* Centre pad the temporary string for aesthetics */
	centreString(&tempString);

	/* Get value for width of children nodes */
	int left = printNode(node->left, 1, offset, depth + 1, output);
	int right = printNode(node->right, 0, offset + left + MAXLENGTH, depth + 1, output);

	/* Add centre-padded data value to output array */
	for (i = 0; i < MAXLENGTH; i++) {
		output[depth][offset + left + i] = tempString[i];
	}

	/* If not root node and is left child of parent */
	if (depth && isLeft) {
		/* Draw branch lines for parent */
		for (i = 0; i < MAXLENGTH + right; i++) {
			output[depth - 1][offset + left + (MAXLENGTH / 2) + i] = '-';
		}

		output[depth - 1][offset + left + (MAXLENGTH / 2)] = '.';
	} else if (depth && !isLeft) { /* If not root node and right child */
		/* Draw branch lines for parent */
		for (i = 0; i < left + MAXLENGTH; i++) {
			output[depth - 1][offset - (MAXLENGTH / 2) + i] = '-';
		}

		output[depth - 1][offset + left + (MAXLENGTH / 2)] = '.';
	}

	/* Free memory for temporary string */
	free(tempString);

	return left + MAXLENGTH + right;
}

/** printBinaryTree
 * Print out the binary tree to the console
 * @param Node *root	Root node of tree to traverse and print
 * @param *levels		Count of each level of tree
 */
void printBinaryTree(Node *root, int *levels) {
	int i, j, max = 0, width = 0;
	int nameCount = getSize(root);
	int maxDepth = getDepth(root);

	/* Find max width of tree */
	for (i = 0; i <= maxDepth; i++) {
		if (levels[i] > max) {
			max = levels[i];
		}
	}

	/* Create array to hold print representation of tree */
	char **output = malloc((maxDepth + 1) * sizeof(char*));
	output[maxDepth] = '\0'; /* Null terminate array of strings */
	width = ((max * MAXLENGTH) + (max * 2));

	/* Allocate space within array for each level of the tree */
	for (i = 0; i <= maxDepth; i++) {
		output[i] = (char*)malloc((MAXLENGTH * 10 + 1) * sizeof(char));
		for (j = 0; j < (MAXLENGTH * 10 * sizeof(char)); j++) {
			output[i][j] = ' '; /* Initialise strings to be filled with spaces */
		}
		output[i][(MAXLENGTH * 10 * sizeof(char))] = '\0'; /* Null terminate each line */
	}

	/* Recursively build print representation of tree */
	printNode(root, 0, 0, 0, output);

	/* Print out tree from representation */
	for (i = 0; i <= maxDepth; i++) {
		printf("%s\r\n", output[i]);
	}

	/* Free the output array and all of its lines */
	for (i = 0; i <= maxDepth; i++) {
		free(output[i]);
	}
	free(output);
}

/** printNAryTree
 * Prints out binary tree in N-Ary format
 * @param Node *root	Root node of tree to traverse and print
 */
void printNAryTree(Node *root) {

}

/** main
 * Main function of programme
 */
int main(void) {
	char **names;
	int i, count;

	count = 10; /* How many names to have on tree */

	/* Allocate memory for array of names */
	names = (char**)malloc(count * sizeof(char*));
	for (i = 0; i < count; i++) {
		names[i] = (char*)malloc(MAXLENGTH * sizeof(char));
	}

	/* Add all names to array of names */
	strcpy(names[0], "Main Person");
	strcpy(names[1], "Daughter");
	strcpy(names[2], "Son");
	strcpy(names[3], "Sister");
	strcpy(names[4], "Brother");
	strcpy(names[5], "Nephew");
	strcpy(names[6], "Granddaughter");
	strcpy(names[7], "Grandson");
	strcpy(names[8], "Daughter");
	strcpy(names[9], "Grandnephew");
    
	/* Create root node of tree */
    Node *root = 0;

	/* Add each name to specific points on tree */
	insertAtPoint(names[0], &root, "", 0);
	insertAtPoint(names[1], &root, names[0], 1);
	insertAtPoint(names[2], &root, names[0], 1);
	insertAtPoint(names[3], &root, names[0], 0);
	insertAtPoint(names[4], &root, names[0], 0);
	insertAtPoint(names[5], &root, names[3], 1);
	insertAtPoint(names[6], &root, names[2], 1);
	insertAtPoint(names[7], &root, names[1], 1);
	insertAtPoint(names[8], &root, names[0], 1);
	insertAtPoint(names[9], &root, names[5], 1);

	/* Get element count of each level of tree */
	int *levels;
	getLevels(root, &levels);
	
	/* Print out binary tree */
	printBinaryTree(root, levels);

	/* Free names array and all of its elements */
	for (i = 0; i < count; i++) {
		free(names[i]);
	}
	free(names);

	/* Free the tree and all of its nodes */
	destroyTree(root);

    return 0; /* Return error code 0 */
}
