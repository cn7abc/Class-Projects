// ja573625
// Jacob Rogers
// COP 3502, Spring 2017
// April-2-2017

// A program to determine if trees are kindred spirits of one another, make reflections of trees, 
// and determine if two trees are a reflection of one another.
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

int countNodes(node *root);
node *createNode(int data);
void postorderTraversal(node *root, int *ptr, int *array);
void preorderTraversal(node *root, int *ptr, int *array);


int countNodes(node *root)
{
	if (root == NULL)
		return 0;

	return 1 + countNodes(root->left) + countNodes(root->right);
}


node *createNode(int data)
{
	node *n = malloc(sizeof(node));
	if(n == NULL)
		return NULL;
	n->data = data;
	n->left = n->right = NULL;
	return n;
}

int isReflection(node *a, node *b){
	// If one of the trees is empty and one is not then it is obvously not a reflection.
	if((a == NULL && b != NULL) || (a != NULL && b == NULL)){
		return 0;
	}
	// If the function makes it to the end without finding a non-matching value then the trees are refelections.
	if (a == NULL || b == NULL){
		return 1;	
	}
	// If the values do not match eachother, then there is not a reflection.
	if(a->data != b->data){
		return 0;
	}

	// recursively traverse the left side of the A tree and at the same time the right side of the B tree, checking for the same values.
	// Then traverse and check the right side of the A tree and the left side of the B tree.
	if(a->data == b->data){
		isReflection(a->left,b->right);
		isReflection(a->right,b->left);
	}
}

node *makeReflection(node *root){
	if(root == NULL)
		return NULL;
	
	node* newRoot = createNode(root->data);

	// Recursively create a new tree by going through the original one but 
	// actually going the opposite way in the new tree.
	if(newRoot == NULL){
		return createNode(root->data);
	}

	newRoot->left = makeReflection(root->right);
	newRoot->right = makeReflection(root->left);

	return newRoot;
}

void postorderTraversal(node *root, int *ptr, int *array){
	if (root == NULL)
		return;

	postorderTraversal(root->left,ptr,array);
	postorderTraversal(root->right,ptr,array);
	array[(*ptr)++] = root->data;
}

void preorderTraversal(node *root, int *ptr, int *array){
	if (root == NULL) 
		return;

	array[(*ptr)++] = root->data;
	preorderTraversal(root->left,ptr,array);
	preorderTraversal(root->right,ptr,array); 
}


int kindredSpirits(node *a, node *b){
	
	int *aPre, *bPre, *aPost, *bPost, aSize, bSize, i = 0, pass = 0;
	int counter = 0;
	int *ptr = &counter;
	// Find the size of the A tree and find the length of the B tree, will allocate arrays of these sizes for each set of values.
	aSize = countNodes(a);
	bSize = countNodes(b);
	// If the sizes of the trees are not the same then they are not kindred spirits.
	if(aSize != bSize)
		return 0;
	
	aPre = malloc(sizeof(int) * aSize);
	aPost = malloc(sizeof(int) * aSize);
	bPre = malloc(sizeof(int) * bSize);
	bPost = malloc(sizeof(int) * bSize);
	// Populate the arrays of A.
	preorderTraversal(a,ptr,aPre);
	counter = 0;
	postorderTraversal(a,ptr,aPost);
	counter = 0;

	// Populate the arrays of B.
	preorderTraversal(b,ptr,bPre);
	counter = 0;
	postorderTraversal(b,ptr,bPost);

	//Check pre-order of A to Post-order of B.
	while((aPre[i] == bPost[i]) && i < aSize)
		i++;
	if(i == aSize)
		pass = 1;
	else if(i < aSize)
		pass = 0;

	//Check pre-order of A to Post-order of B.
	while((bPre[i] == aPost[i]) && i < aSize)
		i++;
	if(i == aSize)
		pass = 1;
	else if(i < aSize)
		pass = 0;

	// Return one or zero based on if at least one of the while loops tests passed.
	if(pass == 1)
		return 1;
	else if(pass == 0)
		return 0;

}

double difficultyRating(void){
	return 2.5;
}

double hoursSpent(void){
	return 7.0;
}
