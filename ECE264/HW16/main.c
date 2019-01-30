/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw16.h"


#ifdef PRINT_FUN
// print function  for tn1 contained in tn2
void PrintTn1ContainedTn2 (bool tn1_contained_tn2, bool tn2_contained_tn1)
{
	if (tn1_contained_tn2)
		printf("tree1 is contained in tree2\n");
	else
		printf("tree1 is not contained in tree2\n");

	if (tn2_contained_tn1)
		printf("tree2 is contained in tree1\n");
	else
		printf("tree2 is not contained in tree1\n");

	if (tn1_contained_tn2 && tn2_contained_tn1)
		printf("tree1 and tree2 are mutually contained.\n");
	else
		printf("tree1 and tree2 are not mutually contained.\n");
}


#endif



/****************** DO NOT Modify this file above this line *************************/

// Modify the following function


#ifdef TEST_MAIN
// This is the main function for this assignment. You should follow the instructions
// for printing carefully. Do not mix the order, otherwise your results will not match
int main(int argc, char **argv)
{
	// if arguments are less than 3 you should not proceed further.
    if (argc<3) {
        return EXIT_FAILURE;
    }
    // The program should then create 2 binary trees from input arguments
	// Please check the functions given to you in README file for creating binary tree
    treeNode * tn1 = BinaryTreeCreate(argv[1]);
    treeNode * tn2 = BinaryTreeCreate(argv[2]);

	// After this you will begin checking the relationship between the two trees
	// 1. First check if `tn1` is contained in `tn2`.
    bool tn1_contained_tn2 = isContained(tn2,tn1);
	// 2. Second you should check if tree2 is contained in tree1,
    bool tn2_contained_tn1 = isContained(tn1,tn2);
	// 3. Pass the results to the print function given to your
    PrintTn1ContainedTn2(tn1_contained_tn2,tn2_contained_tn1);
	// remember to free all the memory.
    FreeBinaryTree(tn1);
    FreeBinaryTree(tn2);
    
	return EXIT_SUCCESS;
}

#endif
