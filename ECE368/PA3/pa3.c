#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char ** argv)
{
  // argv[1]: inputName
  // argv[2]: outputName
  if (argc != 4) {
    printf("Wrong Argument Count (usage: 3 Argument)\n");
    return EXIT_FAILURE;
  }
  TreeNode * headNode = NULL;
  double rd = 0;
  double r = 0;
  double c = 0;

  headNode = constructTree(argv[1],&rd,&r,&c);
  fillInNodalCapacitance(headNode);

  FILE * outputFilePtr = fopen(argv[3],"w");
  if(outputFilePtr == NULL){
    printf("output 2 File Does Not Exist\n");
    fclose(outputFilePtr);
    return EXIT_FAILURE;
  }
  printDelay2FilePreorder(headNode,0,0,outputFilePtr);
  fclose(outputFilePtr);

  preOrder2File1(headNode,argv[2]);
  Tree_destroy(headNode);
  return EXIT_SUCCESS;

}
