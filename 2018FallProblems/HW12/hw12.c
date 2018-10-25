/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw12.h"

#ifdef LINKEDLIST

// Do not modify the below program, we are using ifdef block for
// ease of grading. Please include this flag in your Makefile
void LinkedListPrint(Node * head)
{

	Node *temp = head;

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


/********** Do Not modify the file above this line, you should modify below ***********/
#ifdef TEST_CREATENODE

Node * CreateNode(int value)
{
	// allocate memory for the new Node*
    Node * newNode = malloc(sizeof(Node));
	// check memory allocation fails
    if (newNode == NULL) {
        printf("Error in creating a node\n");
        return NULL;
    }
	// create a Node* with the value as 'value'(input argument).
    newNode -> value = value;
    return newNode;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
// 1. head: the head of the singly linkedlist.
// 2. length: the length of the singly linkedlist.

// This function creates and initializes a singly linkedlist with length as 'length'(input argument),
// The values of the nodes within the singly linkedlist will be the same as array indddices.
// For example, if the singly linkedlist length is 4, the value of the nodes will be 0 1 2 3
void LinkedListCreate(Node * * head, int length)
{
	// check if length is not negative
    if (length<=1) {
        printf("Error in creating Linklist (length<0)\n");
    }else{
        // create linked list of length as 'length'
        Node * previousNode = CreateNode(1);
        (*head)->next = previousNode;
        for (int i=2; i<length; i++) {
            Node * thisNode = CreateNode(i);
            previousNode->next = thisNode;
            previousNode = thisNode;
        }
    }
    
	// do not return anything
}
#endif



#ifdef TEST_JOSEPHUS

Node * list_delete(Node *, int);
void List_destroy(Node * );
int getListLen(Node * );
// 1. head: the head of the singly linkedlist.
// 2. k : this variable will be used for counting if count = k, the element will be out.
// 3. elemDivisible : this variable will be used for printing. When the number of
//    remaining nodes in linked list is divisible by elemDivisible then you should 
//    print the remaining LinkedList with print functin provided to you.

// This function should solve the josephus problem using the singly linkedlist.

void Josephus(Node ** head, int k, int elemDivisible)
{
	// implement the algorithm here
    int length = getListLen(*head);
    printf("THE LENGTH: %d\n",length);
    
    int counter = 0;
    Node * currentNode = *head;
    while (length>elemDivisible) {
        if (counter == k) {
            if (currentNode->next == NULL) {
                currentNode = *head;
            }
            *head = list_delete(*head,currentNode->value);
            length--;
            counter = 0;
        }else{
            if (currentNode->next == NULL) {
                currentNode = *head;
            }
            currentNode = currentNode->next;
            counter ++;
        }
        
    }
    LinkedListPrint(*head);
    List_destroy(*head);
    
	// remember to free the memory of the nodes
	// print the linked list using our function when number of nodes remaining is divisible by elemDivisible
    

}

Node * list_delete(Node *h, int u){
    if (h==NULL) {
        return NULL;
    }
    
    if (h->value == u) {
        Node * p = h->next;
        free(h);
        return p;
    }
    
    Node * q = h;
    Node * r = h->next;
    while ((r!=NULL)&&((r->value)!=u)) {
        r = r->next;
        q = q->next;
    }
    if (r == NULL) {
        return h;
    }
    q->next = r->next;
    free(r);
    return h;
}

void List_destroy(Node * h){
    Node * p;
    while(h!=NULL){
        p = h->next;
        free(h);
        h = p;
    }
}

int getListLen(Node * h){
    if (h==NULL) {
        return 0;
    }
    Node * p;
    int count = 0;
    while(h!=NULL){
        p = h->next;
        h = p;
        count ++;
    }
    return count;
}
#endif
