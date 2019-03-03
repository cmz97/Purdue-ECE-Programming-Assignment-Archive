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
  assignDelay(headNode,0,0);

  printf("\n");
  preOrder2File(headNode,argv[2]);

  // printf("<treeNode> label: %s%d%s wireLength: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KGRN,headNode->label,KRESET,KRED,headNode->wireLength,KRESET,KRED,headNode->cap,KRESET,KRED,headNode->res,KRESET,KRED,headNode->SNCap,KRESET);
  // headNode = headNode->right;
  // printf("<treeNode> label: %s%d%s wireLength: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KGRN,headNode->label,KRESET,KRED,headNode->wireLength,KRESET,KRED,headNode->cap,KRESET,KRED,headNode->res,KRESET,KRED,headNode->SNCap,KRESET);
  Tree_destroy(headNode);
  return EXIT_SUCCESS;

}
