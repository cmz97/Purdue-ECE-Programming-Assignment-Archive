#include <string.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

//TODO: Currently is working on the printing of the tree, stucked on initialization of the huffman code array.

ListNode * generateFrequencyMap(char * ,char * , int * );
void printListWithTree(ListNode *);
void printPreorder(TreeNode * );
void printFreqListToFile(char *,TreeNode * , int *, int );
void append(int * , int , int );
void printPath(char value, int * huffmanCode, int length, TreeNode * tn , int * found);
ListNode * generateHuffmanTree(ListNode *,char *);

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
  ListNode * headListNode = NULL;
  int huffmanLength = 0; //this is the number of unique char in the file

  headListNode = generateFrequencyMap(argv[1],argv[2],&huffmanLength);

  printf("The HUFFMAN length is %d\n", huffmanLength);

  // int lengthArr = (int)ceil((double)huffmanLength/2);
  // int huffmanCode[lengthArr] = {-1}; //initialize the array to -1,-1,-1,...
  //
  // for (int i = 0; i < lengthArr; i++) {
  //   printf("huffmanCode: %d\n",huffmanCode[i] );
  // }
  //
  // headListNode = generateHuffmanTree(headListNode,argv[3]);


  return EXIT_SUCCESS;
}

ListNode * generateFrequencyMap(char * inputFileName,char * outputFileName, int * huffmanLength){
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
  // if(headListNode == NULL)printf("headListNode is NULL\n" );

  for(int i = 1 ; i<numByteFile ; i++){
    //Read byte from file
    if(fread(&curbyte, sizeof(unsigned char), 1, inputFilePtr)!=1){
      printf("read byte inconsistant or failed");
      return NULL;
    }

    if(listHas(headListNode,curbyte) == 0){ //meaning this char has not been found
      ListNode * newNode = newListNode(TreeNode_create(curbyte,1));
      headListNode = List_insert(headListNode,newNode);//insert the newly added list node
    }else{
      getElement(headListNode,curbyte) -> treeNodePtr -> freq ++;
    }
  }
  * huffmanLength = getHuffmanLength(headListNode);

  fclose(inputFilePtr);
  printListWithTree(headListNode); //REMOVE BEFORE TURNED IN


  return headListNode;
}

void printListWithTree(ListNode * head){
  ListNode *  curPtr = head;
  int count = 0;
  while (curPtr != NULL) {
    printf("\nListNode Index: %d TreeNode Total Freq: %d\n", count, curPtr->treeNodePtr->freq);
    printPreorder(curPtr->treeNodePtr);
    curPtr = curPtr->nxtNode;
    count ++;
  }
}

ListNode * generateHuffmanTree(ListNode * headListNode,char * outputFileName){


  while(1){
    printf("\n\n New Merge Begin!\n");
    headListNode = mergeListNode(headListNode);
    printListWithTree(headListNode); //REMOVE BEFORE TURNED IN
    if (headListNode->nxtNode == NULL)break;
    printf("\n       Now Sort!\n");
    headListNode = sortList(headListNode); //Again, this assume only first element is unsorted
    printListWithTree(headListNode); //REMOVE BEFORE TURNED IN
  }
  //Now, construct the tree from the list
  return headListNode;

}

void printPreorder(TreeNode * tn)
{
    if (tn == NULL){
      return;
    }
    /* first print data of node */
    if(tn->right == NULL && tn->left == NULL){ //reached the leaf node
      printf(" Value: %c, Freq: %d\n",tn->value,tn->freq);
    }
    /* then recur on left sutree */
    printPreorder(tn->left);
    /* now recur on right subtree */
    printPreorder(tn->right);
}

void printFreqListToFile(char * outputFilePath, TreeNode * tn, int * huffmanCode, int length){
  int found = 0;

  //experiment with one character
  //this should print the path of 'g'
  printPath('g', huffmanCode, length,  tn , &found);

}

void printPath(char value, int * huffmanCode, int length, TreeNode * tn , int * found){
  if (tn == NULL){
    return;
  }
  /* first print data of node */
  if(tn->right == NULL && tn->left == NULL){ //reached the leaf node
    if (*found == 0 && value == tn->value) { //if not found before and found the value
      *found = 1;
    }
  }

  /* then recur on left sutree */
  if (*found != 1 ) {
    append(huffmanCode, 0, length);
    printPreorder(tn->left);
  }else{
    return;
  }

  if (*found != 1 ) {
    /* now recur on right subtree */
    append(huffmanCode, 1,length);
    printPreorder(tn->right);
  }else{
    return;
  }

}

void append(int * huffmanCode, int num, int length){
  int lastIndex = 0;
  if (huffmanCode[0] == -1) {
    huffmanCode[0] = num;
    return;
  }
  while(huffmanCode[lastIndex]!=-1){
    lastIndex++;
    if (lastIndex == length) {
      // reached the end, array fulled
      printf("ERROR ARRAY FULLED\n" );
      return;
    }
  }
  huffmanCode[lastIndex - 1] = num;
  return;
}
