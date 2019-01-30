// Edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw18.h"


#ifdef TEST_MAIN
void Tree_destroy(TreeNode * n);
void List_destroy(ListNode * n);
void Tree_destroy(TreeNode * n){
  if(n==NULL)return;
  Tree_destroy(n->left);
  Tree_destroy(n->right);
  free(n->data);
  free(n);
}

void List_destroy(ListNode * n){
  ListNode * temp;
  while(n!=NULL){
     temp = n->next;
     Tree_destroy(n->treenode);
     free(n);
     n = temp;
  }
}
int main(int argc, char * * argv)
{
	// check for input error
    if (argc < 2) {
        return EXIT_FAILURE;
    }
	// open the file
    
	// input file is in argv[1]
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
	// call FindMin
    FindMin(head);
    fclose (fp);
    List_destroy(head);
    

}
#endif
