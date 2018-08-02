// Gianlouie Molinary gi713278
#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

int countNodes(node *root) // From Szumlanski's notes
{
	if (root == NULL)
		return 0;
	
	return 1 + countNodes(root->right) + countNodes(root->left);
}

node *create(int data) // From Szumlanski's testcases
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}

void preorder(node *root, int *pre, int *index) // preorder traversal of tree 
{
	if (root == NULL)
		return;
	
	pre[*index] = root->data;
	*index = *index + 1;
	preorder(root->left, pre, index);
	preorder(root->right, pre, index);
}

void postorder(node *root, int *post, int *index) // postorder traversal of tree
{
	if (root == NULL)
		return;
	
	postorder(root->left, post, index);
	postorder(root->right, post, index);
	*index = *index + 1;
	post[*index] = root->data;
}

int isReflection(node *a, node *b)
{
	if (a == NULL && b == NULL) // empty trees, everything is going to be okay
		return 1;
	
	if (a == NULL || b == NULL) // one isn't null, while the other is. Not a reflection
		return 0;
	
	if (a->data == b->data)
		return isReflection(a->right, b->left) && isReflection(a->left, b->right);
	
	else 
		return 0;
}

node *makeReflection(node *root)
{
	node *ref;
	
	if (root == NULL)
		return NULL;
	
	ref = create(root->data);
	
	ref->right = makeReflection(root->left); // mirrors each
	ref->left = makeReflection(root->right); //     node
	
	return ref;
}

int kindredSpirits(node *a, node *b)
{
	int *pre, *post, counta, countb, i, index = 0;
	
	if (a == NULL && b == NULL)
		return 1;
	
	if (a == NULL || b == NULL)
		return 0;
	
	counta = countNodes(a);
	countb = countNodes(b);
	
	if (counta != countb) // Don't even have the same amount of nodes, so can't be kindred spirits
		return 0;
	
	if (a->data == b->data && counta + countb != 2) // the root cannot be the same if kindred spirits, unless only one node in each tree  
		return 0;
	
	pre = malloc(sizeof(int) * counta);
	post = malloc(sizeof(int) * counta);
	
	preorder(a, pre, &index); // places the preorder traversal into an array
	index = -1;
	postorder(b, post, &index);	// places the postorder traversal into an array
	
	for(i = 0; i < counta; i++)
	{ 
		if (pre[i] != post[i]) // first instance of difference between the two traversal 
			return 0;
	}
	
	free(pre);
	free(post);
	
	return 1;
}

double difficultyRating(void)
{
	return 3.0;
}

double hoursSpent(void)
{
	return 20;
}