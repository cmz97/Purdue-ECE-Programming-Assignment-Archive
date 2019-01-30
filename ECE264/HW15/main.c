/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw15.h"

/****************** DO NOT Modify this file above this line *************************/

// Modify the following function
#ifdef TEST_MAIN

void List_destroy(Node * );

int main(int argc, char **argv)
{
	// input argv[1] contains the name of the input file.
	// Check for the right number of input arguments.
    if (argc<2) {
        return EXIT_FAILURE;
    }
    
    Node * head;
    LinkedListCreate(&head,argv[1]);
    RemoveDuplicate(head);
    List_destroy(head);     
	//Initialize a linked list Node and use the file name from input arguments to create a linked list
	//Remove all duplicates in the linked list created above.

	// release memory
}

void List_destroy(Node * h){
  Node * p;
  while(h!=NULL){
    p = h->next;
    free(h);
    h = p;
  }
}
#endif
