//edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw18.h"

//Do Not Change this function
void PrintAnswer(ListNode* head, ListNode* min1, ListNode* min2)
{
	ListNode* temp = head;
	int i;
	while(temp!=NULL)
	{
		i = 0;
		while(i < head -> treenode->dimension)
		{
			if(i == 0)
				printf("(%d, ", temp->treenode->data[i]);
			else if(i == head -> treenode->dimension-1)
				printf("%d)\n", temp->treenode->data[i]);
			else
				printf("%d, ", temp->treenode->data[i]);
			i+=1;

		}
		temp = temp->next;
	}

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
YOU CAN EDIT BELOW THIS COMMENT
*/

#ifdef TEST_MIN
int getMag(TreeNode* x);

void FindMin(ListNode* head)
{
	// find pair of ListNodes with least distance between them.
	// call print Function
    int length = 0;
    ListNode * temp = head;
    while (temp!=NULL) {
        temp = temp -> next;
        length++;
    }
    int min = 0; //initialize 
    ListNode * min1 = NULL;
    ListNode * min2 = NULL;
    if (length > 1) {
        ListNode * ptr1 = head;
        ListNode * ptr2 = head -> next;
 	if(getMag(ptr1->treenode)>getMag(ptr2->treenode)){
		min1 = ptr2;
		min2 = ptr1;
	}else{
		min1 = ptr1;
		min2 = ptr2;
	}
        min = FindDist(ptr1->treenode,ptr2->treenode);
        while (1) {
            ptr2 = ptr1->next;
            if (ptr2 == NULL) {
                break;
            }
            while (ptr2!=NULL) {
		//printf("min pair:%d\n",FindDist(ptr1->treenode,ptr2->treenode));
                if (min > FindDist(ptr1->treenode,ptr2->treenode)) {
                    min = FindDist(ptr1->treenode,ptr2->treenode);
		    if(getMag(ptr1->treenode)>getMag(ptr2->treenode)){
			min1 = ptr2;
			min2 = ptr1;
		    }else{
			min1 = ptr1;
			min2 = ptr2;
		    }
		}
                ptr2 = ptr2->next;
            }
            ptr1 = ptr1->next;
        }
    } else {
        fprintf(stderr, "Lenght of List incorrect (<2)\n");
    }
	/*
	ENSURE the 2nd parameter of the print function (min1) is smaller than
	the 3rd parameter (min2). 
	Look at README, and expected output for more details.
	*/
    PrintAnswer(head, min1, min2);
}

int getMag(TreeNode* x)
{
    //int result = 0;
    //for (int i=0; i<x->dimension; i++) {
    //    result += x->data[i];
    //}
    return x->data[0];
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
void LinkedListCreate(ListNode ** head, int n, int dim, FILE* fp)
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
