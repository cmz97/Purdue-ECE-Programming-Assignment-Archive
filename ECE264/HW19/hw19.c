// You can modify this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw19.h"

// DO NOT MODIFY THIS FUNCTION
void PrintAns(ListNode* head, ListNode* min1, ListNode* min2)
{
	int i;
	i = 0;
	while(i < head -> treenode->dimension)
	{
		if(i == 0)
			printf("(%d, ", min1->treenode->data[i]);
		else if(i == head -> treenode->dimension-1)
			printf("%d) <-> ", min1->treenode->data[i]);
		else
			printf("%d, ", min1->treenode->data[i]);
		i+=1;
	}

	i = 0;
	while(i < head -> treenode->dimension)
	{
		if(i == 0)
			printf("(%d, ", min2->treenode->data[i]);
		else if(i == head -> treenode->dimension-1)
			printf("%d)\n", min2->treenode->data[i]);
		else
			printf("%d, ", min2->treenode->data[i]);
		i+=1;
	}
}

/*
MODIFY BELOW THIS COMMENT
*/


#ifdef TEST_CENT
ListNode* FindCentroid(TreeNode* x, TreeNode* y)
{
	// Create a new node
    ListNode * new = malloc(sizeof(ListNode));
	// new -> treenode.left should be x
    new -> treenode.left = x;
	// new -> treenode.right should be y
    new -> treenode.right = y;
	// x -> treenode.data should be less than y -> treenode.data (refer to README)
	
	// Use a loop to average the data from the two parameters (x and y).
	/*
	EXAMPLE
	Average x->treenode.data[0] and y->treenode.data[0] to new->treenode.data[0]
	Average x->treenode.data[1] and y->treenode.data[1] to new->treenode.data[1]
	and so on
	*/

	// Return the new node
}
#endif


#ifdef TEST_DIST
int FindDist(TreeNode* x, TreeNode* y)
{
    //find the eucledian distance between
    // x->data and y->data
    // DO NOT FIND SQUARE ROOT (we are working with int)
    // return the distance
    int result = 0;
    //printf("FindDist's dim:%d\n",x->dimension);
    for (int i=0; i<x->dimension; i++) {
        result += (x->data[i] - y->data[i])*(x->data[i] - y->data[i]);
    }
    //printf("FindDist's result:%d\n",result);
    return result;
}
#endif


#ifdef TEST_FUSE
ListNode* Fuse(ListNode* head, ListNode* fuse1, ListNode* fuse2)
{

	// Create a new ListNode element using findCentroid function.
	// The new->treenode.data will hold the averaged values of the two parameters' data (fuse1, and fuse2)
	// add the new ListNode to the list.
	// remove the fuse1 and fuse2 from the list. (Do NOT free)
	// you may want to return head from this function (depending on your implementation)
}
#endif


#ifdef TEST_CREATENODE
ListNode* CreateNode(int n, int dim, int* arr)
{
    // check for malloc error
    TreeNode * tNode = malloc(sizeof(TreeNode));
    if (tNode == NULL) {
        fprintf(stderr, "malloc fail in createNode func\n");
        return NULL;
    }
    // initialize dim
    tNode->dimension = dim;
    // both left and right childern will be NULL
    tNode->left = NULL;
    tNode->right = NULL;
    // allocate memory for data
    tNode->data = malloc(sizeof(int)*dim);
    // return a ListNode
    //printf("newdata: ");
    for(int i=0;i<dim;i++){
        tNode->data[i] = arr[n*dim+i];
        //printf("%d  ",tNode->data[i]);
    }
    //printf("\n");
    ListNode * lNode = malloc(sizeof(ListNode));
    lNode->treenode = tNode;
    return lNode;
    
}
#endif


#ifdef TEST_LINKEDLISTCREATE
void LinkedListCreate(ListNode ** head, int n, int dim, FILE* fptr)
{
    // create temp node using CreateNode
    // read from file into an array, pass array to CreateNode
    int * arr = malloc(sizeof(int)*n*dim);
    int ind = 0;
    while (ind < n*dim)
    {
        if (fscanf(fp, "%d", &arr[ind]) != 1)
        {
            fprintf(stderr, "fscanf fail\n");
            fclose (fp);
            free (arr);
        }
        //printf("number read from file (n:%d,dim:%d): %d\n",n,dim,arr[ind]);
        ind ++;
    }
    // assign temp to that node
    ListNode * temp = CreateNode(0,dim,arr);
    * head = temp;
    for (int i = 1; i < n; i++) {
        temp->next = CreateNode(i,dim,arr);
        temp = temp -> next;
    }
    temp->next = NULL;
    free(arr);
    // use a loop to create nodes for the remaining elements of the list.
    
}
#endif

#ifdef TEST_CLUSTER
void MakeCluster(ListNode** head)
{
	// Walk through the linked list.
	// find pair of nodes with minimum distance.
	// fuse the two nodes into one node.
	// call print function
	// repeat till one node is remaining.
}
#endif


