/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw14.h"


/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_CREATENODE

Node * CreateNode(int val)
//val: value of the element of the node to be created
{
	// same as previous homeworks
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
//source: the head of the singly linkedlist.
//len: the length of the array.
//arr: the array with the contents of the input file.

void LinkedListCreate(Node * * source, int len, int* arr)
{
	// Refer HW13 and HW12
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
// source is the head of the list to be split.
// head1 is the head of the upper sub-list.
// head2 is the head of the lower sub-list.

void SplitList(Node* source, Node** head1, Node** head2)
{
	// Refer HW13
    int mid = 0;
    Node *waste = source;
    int length = 0;
    while (waste!=NULL) {
        length++;
        waste = waste -> next;
    }
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
#endif

#ifdef TEST_MERGE
// upper is the upper sub-list to be merged
// lower is the lower sub-list to be merged
int getval(Node * head, int offset);
int getListLen(Node * );
void append(Node ** head, int val);

Node* Merge(Node* upper, Node* lower) 
{
    Node * head = NULL;
	// Check for the base cases. (When either sub-list is NULL)
    if (upper == NULL) {
        return lower;
    }else if(lower==NULL){
        return upper;
    }
    
    int leftind = 0;
    int rightind = 0;
    
    while(leftind<getListLen(upper) && rightind <getListLen(lower)){
        if (getval(upper,leftind)>=getval(lower,rightind)) {
            append(&head,getval(lower,rightind));
            rightind++;
        }else{
            append(&head,getval(upper,leftind));
            leftind++;
        }
    }
    //fill sup the rest of the array
    while(leftind<getListLen(upper)){
        append(&head,getval(upper,leftind));
        leftind++;
    }
    //fill up the rest of the array
    while(rightind <getListLen(lower)){
        append(&head,getval(lower,rightind));
        rightind++;
    }
    return head;
	// Pick the larger between upper and lower, and recur appropriately.
	// return the merged array
}

int getval(Node * head, int offset){
    if (head == NULL) {
        printf("Index dont exsist");
        return -1;
    }
    Node * temp = head;
    for (int i=1; i<=offset; i++) {
        temp = temp->next;
        if (temp == NULL) {
            printf("Index dont exsist");
            return -1;
        }
    }
    return temp->value;
}

void append(Node ** head, int val){
    Node *temp = *head;
    while (temp!=NULL) {
        temp = temp -> next;
    }
    Node * new = malloc(sizeof(Node));
    new->value = val;
    new->next = NULL;
    temp->next = new;
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

#ifdef TEST_SORT

// source is the head of the list to for which MergeSort is to be performed.
void MergeSort(Node** source) 
{ 
	// Declare a node, to hold the current head of the source list.
    Node * head = *source;
	// Declare nodes, to hold the two the heads of the two sub-lists.
    Node * upper = NULL;
    Node * lower = NULL;
	// Check for the base case -- length 0 or 1
		// if so, return;
    int length = 0;
    Node * waste = *source;
    while (waste!=NULL) {
        length++;
        waste = waste -> next;
    }
    if (length < 2) {
        return;
    }
	  
	// Use SpiltList() to partition the list into sub lists.
		// This will partiton the source list, into two lists (As done in the previous homework)
    SplitList(head,&upper,&lower);
	// Recursively sort the sub-lists by calling MergeSort() on the upper and lower sub-lists.
    MergeSort(&upper);
    MergeSort(&lower);
		// MergeSort() is a recursive function, and MergeSort() needs to be called
		// on both sub-lists (obtained after partitioning)
    Merge(upper,lower);
	// Merge the two sorted lists together, using the Merge()
}


#endif

