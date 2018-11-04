/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw15.h"

#ifdef LINKEDLIST
// Do not modify this function.
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
			printf("%d\n",temp->value);
		}
		temp=temp->next;
	}
}
#endif


/********** Do Not modify the file above this line, you can modify below ***********/
#ifdef TEST_CREATENODE

Node * CreateNode(int val)
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

void LinkedListCreate(Node ** head, char* name)
{
	/*
	Create a linked list from the input file referenced by `name`.
	*/
    FILE * fp = fopen(name, "r");
    int len = 0;
    if (fp == NULL) {
        printf("error while attemp to open file");
        return;
    }
    
    //count the number of numbers in file
    int waste = 0;
    while (fscanf(fp, "%d", &waste) == 1)len++;
    
    //malloc array
    int * arr = malloc(sizeof(int)*len);

    if (arr == NULL) {
        fclose(fp);
        return;
    }
    
    //reset fp
    fseek(fp,0,SEEK_SET);

    int ind = 0;
    while (ind < len)
    {
        if (fscanf(fp, "%d", &arr[ind]) != 1)
        {
            fprintf(stderr, "fscanf fail\n");
            fclose (fp);
            free (arr);
            return;
        }
        ind ++;
    }
    
    if (len <= 0) {
        * head = NULL;
        fclose(fp);
        free(arr);
        return;
    }else{
        * head = CreateNode(arr[0]); //create the head of the node
        Node * temp = * head;
        for (int i = 1; i < len; i++) {
            temp -> next = CreateNode(arr[i]);
            temp = temp -> next;
        }
        fclose(fp);
        free(arr);
        return;
    }
    
}
#endif
#ifdef TEST_REMOVED
//This function will remove repetitions of a linked list value.
void RemoveDuplicate(Node *headRef)
{
	/*
	This function will remove repetitions from the linked list referenced by headRef.
	Each time we check for a new Node in the linked list, we will check if it is distinct from
	the Nodes already present in the list ( upto the previous Node).
	So for each occurrence after its first, we will be deleting that node.
	To delete a node: we will map the next Node of the previous Node to the Node after the current Node.
	Print the linked list after all repetitions have been removed. Use the function given to you for priniting.
	*/
	
	Node * temp = headRef;
	Node * temp2 = NULL;
	Node * prev_temp2 = NULL;
	while(temp){
		int current = temp->value;
		temp2 = temp->next;
		prev_temp2 = temp;
		while(temp2){
			if(temp2->value == current){
				prev_temp2 -> next = temp2 -> next;
				free(temp2);
				temp2 = prev_temp2->next;
			}else{
				prev_temp2 = temp2;
				if(temp2)temp2 = temp2->next;		
			}
		}
		temp = temp->next;
	}
	LinkedListPrint(headRef);
}

#endif
