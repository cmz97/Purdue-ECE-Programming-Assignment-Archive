#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

//***** YOU NEED TO MODIFY main() FUNCTION BELOW *******//
#ifdef TEST_MAIN
int main(int argc, char **argv)
{
    //1. Check for number of arguments. If less than 2, do not proceed further.
    if (argc < 2) {
        return EXIT_FAILURE;
    }
        
    //2. The program should create a binary search tree from the numbers in input file. The input file
    //also contains a number for search query at the end.

        
    //3. The input file has one number per line. If there are 'n' lines in the file, the first n-1 numbers
    //are the elements of the binary search tree and the nth line is the search query.
    //NOTE: n is not given to you.
    FILE * fp = fopen(argv[1], "r");
    int count = 0;
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
    
    int waste = 0;
    while (fscanf(fp, "%d", &waste) == 1)count++;
    
    //4. Create an array of the first n-1 numbers and store the last number in a variable.

    int * arr = malloc(sizeof(int)*(count-1));//create array size n-1
    // check for malloc fail, if so, return EXIT_FAILURE
    if (arr == NULL) {
        fclose(fp);
        return EXIT_FAILURE;
    }
    fseek(fp,0,SEEK_SET);
    
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
    
    int query;
    if (fscanf(fp, "%d", &query) != 1)
    {
        fprintf(stderr, "fscanf fail in last element\n");
        fclose (fp);
        free (arr);
        return EXIT_FAILURE;
    }
    
    
    //5. Create a Binary Search Tree. It takes four arguments:
        //1. The array
        //2. the first element of the array
        //3. start index (index of first element of the array)
        //4. end index ( index of last element of the array)
    treenode * root = CreateBST(arr,arr[0],0, count - 1);
    //6. Print the created tree in Inorder fashion. Quick check if you have created the tree right: the output of
        //will be a sorted array of numbers.
    BinaryTreeInOrderPrint(root);
    //7. Compute the distance of the 'search query' node by passing it to the function.
    int distance = FindDistance(root,query,0);
    //8. Use PrintDistance() function to print the distance of the node from the root node in the right format.
    PrintDistance(distance);
    //9. Free all memory.
    free(arr);
    fclose(fp);


}
#endif
