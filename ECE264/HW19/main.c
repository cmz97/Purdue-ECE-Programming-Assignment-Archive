// Please modify this file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw19.h"


#ifdef TEST_MAIN
int main(int argc, char * * argv)
{
	// check for input error
    if (argc < 2) {
        return EXIT_FAILURE;
    }
	// open the file
	
	// Create linkedList
    FILE * fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
    // n is the element in the file
    int n = 0;
    if (fscanf(fp, "%d", &n) != 1)
    {
        fprintf(stderr, "fscanf fail\n");
        fclose (fp);
        return EXIT_FAILURE;
    }
    // dim is the second element in the file
    int dim = 0;;
    if (fscanf(fp, "%d", &dim) != 1)
    {
        fprintf(stderr, "fscanf fail\n");
        fclose (fp);
        return EXIT_FAILURE;
    }
    // the rest of the data in the file are the datapoints.
    // call LinkedListCreate
    ListNode * head = NULL;
    LinkedListCreate(&head,n,dim,fp);
    
	// call MakeCluster
    fclose (fp);
    List_destroy(head);
}
#endif
