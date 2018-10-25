/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw12.h"



/****************** DO NOT Modify this file above this line *************************/

// Modify the following function
#ifdef TEST_MAIN

int main(int argc, char **argv)
{
	// if argc < 4 then return EXIT_FAILURE
    if (argc<4) {
        printf("The input parameter is incorrect!")
        return EXIT_FAILURE;
    }
	// argv[1] - length of linked list
    int length  = argv[1];
	// argv[2] - value of k as mentioned in josephus algorithm
    int k = argv[2];
	// argv[3] - value of elemDivisible
    int elemDivisible = argv[3];
	// create head node
    Node * headNode = CreateNode(0);
	// create Linked list with length as argv[1]
    LinkedListCreate(&headNode,length);
	// run josephus
    Josephus(&headNode,k,elemDivisible);
	// free the head node
    free(headNode);
	return EXIT_SUCCESS;
}

#endif
