#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "utilities.h"


ListNode * generateFrequencyMap(char * );


int main(int argc, char ** argv)
{
  // argv[1]: name of the input file to be compressed
  // argv[2]: name of output file containning the frequencies of occurences
  // argv[3]: is an output file to store the huffman coding tree
  // argv[4]: is an output file to store the huffman code for characters
  // argv[5]: is an output file to store the compressed file
  if (argc != 6){
      printf("Not the correct number of arguments (argc != 6)");
      return EXIT_FAILURE;
  }

  FILE * inputFilePtr = fopen(argv[1],"r");
  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist");
    fclose(inputFilePtr);
    return EXIT_FAILURE;
  }
  fclose(inputFilePtr);

  // ---- end preprocess -----

  //--- compression ---
  generateFrequencyMap(argv[1]);
  return EXIT_SUCCESS;
}

ListNode * generateFrequencyMap(char * inputFileName){
  int numByteFile = 0;
  unsigned char curbyte;
  ListNode * headListNode = NULL;
  //file open
  FILE * inputFilePtr = fopen(inputFileName,"r");
  if(inputFilePtr == NULL){
    printf("Error whilte reading file");
    fclose(inputFilePtr);
    return NULL;
  }

  //now, counter the number of byte of this file
  while(fread(&curbyte, sizeof(unsigned char), 1, inputFilePtr) == 1)numByteFile++;
  fseek(inputFilePtr, 0, SEEK_SET); //now put back the file pointer

  //initialize the headListNode
  fread(&curbyte, sizeof(unsigned char), 1, inputFilePtr);
  headListNode = newListNode(TreeNode_create(curbyte,1));

  for(int i = 1 ; i<numByteFile ; i++){
    //Read byte from file
    if(fread(&curbyte, sizeof(unsigned char), 1, inputFilePtr)!=1){
      printf("read byte inconsistant or failed");
      return NULL;
    }

    if(listHas(headListNode,curbyte) == 0){ //meaning this char has not been found
      ListNode * newNode = newListNode(TreeNode_create(curbyte,1));
      List_insert(headListNode,newNode);//insert the newly added list node
    }else{
      getElement(headListNode,curbyte) -> treeNodePtr -> freq ++;
    }
  }

  printListWithTree(headListNode); //REMOVE BEFORE TURNED IN

  //Now, construct the tree from the list



  fclose(inputFilePtr);

  return headListNode;
}
