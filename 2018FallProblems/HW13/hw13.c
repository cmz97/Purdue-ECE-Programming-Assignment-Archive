 /****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw13.h"

#ifdef LINKEDLIST
// Do not modify this function, we are using this within ifdef block for
// ease of grading.
void LinkedListPrint(Node * * source)
{

	Node *temp = * source;

	while(temp!=NULL)
	{
		if(temp->next!=NULL)
		{
			printf("%d,",temp->value);
		}
		else
		{
			printf("%d",temp->value);
		}
		temp=temp->next;
	}
	printf("\n");
}
#endif


/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_CREATENODE

Node * CreateNode(int val)
//val: value of the element of the node to be created
{
    // allocate memory for the new Node*
    Node * newNode = malloc(sizeof(Node));
    
    // check memory allocation fails
    if (newNode == NULL) {
        return NULL;
    }
    // create a Node* with the value as 'value'(input argument).
    newNode -> value = val;
    newNode -> next = NULL;
    return newNode;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
//head: the head of the singly linkedlist.
//len: the length of the array.
//arr: the array with the contents of the input file.

//This function will create and initialize the singly linkedlist with length=len,

void LinkedListCreate(Node * * source, int len, int* arr)
{
	// This function is similar to the one in HW12.
	// Tip: use CreateNode(arr[index])
    if(len <=0){
       *source = NULL;
    }
    Node *temp;
    Node *dummy = CreateNode(0);
    temp = dummy;
    *source = NULL;
    for (int i = 0; i < len; i++) {
        temp -> next = CreateNode(arr[i]);
        temp = temp -> next;
    }
    *source = dummy -> next;
    free(dummy);
}
#endif


#ifdef TEST_SPLIT
// source is the Node corresponding to the head of the list
// head1 is the list corresponding upper half of the list. (After Partition)
// head2 is the list corresponding lower half of the list. (After Partition)
int getListLen(Node * );

void SplitList(Node* source, Node** head1, Node** head2) 
{ 
	// Find the mid point of the list.
		//in case of an even number of nodes, mid point will be floor(<num_elements>/2)
			//Example: 1,2,3,4
				// The list should split into 1,2 and 3,4
    int mid = 0;
    int length = getListLen(source);
    /*if (length % 2 == 0) {
        mid = length / 2 + 1; //even number
    }else{
    	mid = length / 2 + 1;
    }*/
    mid = length - 1 - length/2;
		//in case of an odd number of nodes, mid point will be <num_elements>/2
			//Example: 1,2,3,4,5
				// The list should split into 1,2,3 and 4,5				
    * head1 = source;
  //  printf("%d\n", mid);
    Node * temp = source;
    for (int i=0; i<mid; i++) {
        temp = temp->next;
    }
    * head2 = temp -> next;
    temp -> next = NULL;
    	// Tip: head1 will point to the source node.
	// Tip: head2 will point to the mid-point of the list.
	// Tip: Ensure you break the link between the sub-lists.
}

int getListLen(Node * h){
  Node *temp = h;
  int count = 0;
  while (temp!=NULL) {
    count++;
    temp = temp -> next;
  }
  return count;
}

#endif


#ifdef TEST_DIV
void Divide(Node** source) 
{ 
	// Declare a node, to hold the current head of source list.Node * head = * source
    Node * head1;
    Node * head2;
	// Check for the base case -- length 0 or 1
		// if so, return;
    if (getListLen(*source)<2) {
        free(*source);
        return;
    }
	  
	// Use SpiltList(...) to partition the list into sub lists.
    SplitList(*source,&head1,&head2);
	// Use LinkedListPrint(...); to print the upper sub-list.
    LinkedListPrint(&head1);
	// Use LinkedListPrint(...); to print the lower sub-list
    LinkedListPrint(&head2);
		// DO NOT USE YOUR OWN PRINT FUNCTION.
	 // Recursively Divide(...) both sub-lists, to find their respective mid-points
    Divide(&head1);
    Divide(&head2);

	 // till only one or no elements are left in the sub-lists.
    
} 
#endif

