/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw14.h"


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

/****************** DO NOT Modify this file above this line *************************/

// Modify the following function
#ifdef TEST_MAIN

int main(int argc, char **argv)
{
	// if argc is less than 2 then, return EXIT_FAILURE
	
        // input file is specified through the Makefile.
    if (argc<2) {
        return EXIT_FAILURE;
    }
	// open file to read
    FILE * fp = fopen(argv[1], "r");
	// check for fopen fail. If so, return EXIT_FAILURE
    int count = 0;
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
	// count the number of integers in the file.
    int waste = 0;
    while (fscanf(fp, "%d", &waste) == 1)count++;
    // allocate memory to store the numbers
    int * arr = malloc(sizeof(int)*count);
    // check for malloc fail, if so, return EXIT_FAILURE
    if (arr == NULL) {
        fclose(fp);
        return EXIT_FAILURE;
    }
    fseek(fp,0,SEEK_SET);
	// use fscanf to read the file for its contents.
    int ind = 0;
    while (ind < count)
    {
        if (fscanf(fp, "%d", &arr[ind]) != 1)
        {
            fprintf(stderr, "fscanf fail\n");
            fclose (fp);
            free (arr);
            return EXIT_FAILURE;
        }
        ind ++;
    }
	// create head node, which corresponds to the head of the linked-list.
	Node * head;
	// You must now use the appropriate function to construct the remaining list.
    LinkedListCreate(&head,count,arr);
    MergeSort(&head);
	// call MergerSort() function for final output.
		// This will call a recursive function.
		// The input list will be divided into two sub-lists recursively,
		// Then the contents of the sub-lists are compared and merged back to form the
		// sorted output list.
    LinkedListPrint(&head);
	// use the provided function to print the final list.
    fclose(fp);
    free(arr);
	// Tip: Check for memory errors.

	return EXIT_SUCCESS;
}

#endif
