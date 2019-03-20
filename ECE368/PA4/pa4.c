#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "tree.h"
#include "util.h"

int main(int argc, char ** argv)
{
//(Mode One): Building Tree (SW): "-b" arg[2]:Operation_input_File arg[3]:tree_output_file
//(Mode Two): Evaluating Tree (SW): "-e" arg[2]:tree_input_file
  if (argc == 4 && strcmp(argv[1],"-b") == 0) {
    //Building Tree Mode
    TreeNode * headNode = NULL;
    FILE * intputFilePtr = fopen(argv[2],"r");
    if(intputFilePtr == NULL){
      printf("%d\n",-1);
      fclose(intputFilePtr);
      return EXIT_FAILURE;
    }
    //to check whether the reading of the input file is successfull
    if(constructTree(intputFilePtr,&headNode) == false){
      printTreePreOrderToFile(headNode, argv[3]); // still print if input file read wrong
      Tree_destroy(headNode);
      printf("%d\n",0);
      fclose(intputFilePtr);
      return EXIT_FAILURE;
    }

    printf("\nAfter Insert:\n");
    DEBUG_pretty_tree(headNode); //DEBUG print

    printTreePreOrderToFile(headNode, argv[3]);
    Tree_destroy(headNode);
    printf("%d\n",1);
    fclose(intputFilePtr);
    return EXIT_SUCCESS;
  }else if (argc == 3 && strcmp(argv[1],"-e") == 0){
    //Evaluating Tree Mode
    int inputState = 0;
    int bstState = 0;
    int avlState = 0;
    // inputState = buildTreeFromPreOrder();
    // bstState = checkBST();
    // avlState = checkAVL();

    printf("%d,%d,%d\n",inputState,bstState,avlState);

    if(inputState == 1){
      return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
  }else{
    printf("Wrong Argument\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
