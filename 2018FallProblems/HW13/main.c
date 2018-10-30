/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw13.h"

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

	// count the number of integers in the file.

    int count = 0;
    
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
    
    // count the number of integers using a loop
    // at the end of the loop close file_pointer
    while(!feof(fp)){
        int c = fgetc(fp);
        if(c == '\n')count++;
    }
    

	// allocate memory to store the numbers
    int * arr = malloc(sizeof(int)*count);
	// check for malloc fail, if so, return EXIT_FAILURE
    if (arr == NULL) {
        return EXIT_FAILURE;
    }
    fseek(fp,0,SEEK_SET);
	// use fscanf to read the file, and store its contents into an array.
    int ind = 0;
    while (ind < count)
    {
        if (fscanf(fptr, "%d", &arr[ind]) != 1)
        {
            fprintf(stderr, "fscanf fail\n");
            fclose (fptr);
            free (arr);
            return EXIT_FAILURE;
        }
        ind ++;
    }
	// create head node to store the head of the linked list.
    Node * head = NULL;
	// call the appropriate function to create the rest of the linked list, with the values of the array.
    LinkedListCreate(&head,count,arr);
    Divide(&head);
	// Divide is a function to break the lists into smaller sublists.
		// You are supposed to find the mid-point of the list, and then break the list into two lists.
		// Then the sub-lists are broken down further into smaller sub-lists.
		// Refer to the example in the README
    fclose(fp);
    free(arr)
	// Tip: check for memory errors.

	return EXIT_SUCCESS;
}

#endif
