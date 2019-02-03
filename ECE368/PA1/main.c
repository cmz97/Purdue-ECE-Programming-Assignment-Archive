#include <string.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

//TODO: currently, the returned path array not correct

ListNode * generateFrequencyMap(char * ,char * , int * );
void printListWithTree(ListNode *);
void printPreorder(TreeNode * );
void printTreeListToFile(char * , ListNode * , int );
void pop(int * , int );
void printTreeListPreorderToFile(int * , int , TreeNode * , FILE * , char * );
ListNode * generateHuffmanCode(ListNode *,char *, int);
void printFreqListToFile(ListNode * , char * );
void push(int * , int , int );


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
  printListWithTree(headListNode); //REMOVE BEFORE TURNED IN

  printf("The HUFFMAN length is %d\n", huffmanLength);

  headListNode = generateHuffmanCode(headListNode,argv[4],huffmanLength);


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
  fclose(inputFilePtr);
  * huffmanLength = getHuffmanLength(headListNode);

  //sort the linked list
  headListNode = sort1dListAccord2Ascii(headListNode);

  //call the printFreqListToFile to print result
  printFreqListToFile(headListNode,outputFileName);


  return headListNode;
}

void printFreqListToFile(ListNode * headListNode, char * outputFileName){
  FILE * outputFilePtr = fopen(outputFileName,"w");
  if(outputFilePtr == NULL){
    printf("Unable to write to file, path is wrong (this should not happen)");
    fclose(outputFilePtr);
    return;
  }
  ListNode * charNode = NULL;
  long zero = 0;
  long castFreq = 0;
  for(long i = 0; i < 256; i++){
    charNode = getElement(headListNode, (char)i);
    if (charNode != NULL) {
      castFreq = charNode->treeNodePtr->freq;
      fwrite(&castFreq , 1 , sizeof(long) , outputFilePtr);
      // printf("char: %c freq:%d\n",charNode->treeNodePtr->value,charNode->treeNodePtr->freq );
    }else{
      fwrite(&zero,1,sizeof(long),outputFilePtr);
    }
  }
  fclose(outputFilePtr);
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

ListNode * generateHuffmanCode(ListNode * headListNode,char * outputFileName, int huffmanLength){

  while(1){
    // printf("\n\n New Merge Begin!\n");
    headListNode = mergeListNode(headListNode);
    // printListWithTree(headListNode); //REMOVE BEFORE TURNED IN
    if (headListNode->nxtNode == NULL)break;
    // printf("\n       Now Sort!\n");
    headListNode = sortList(headListNode); //Again, this assume only first element is unsorted
    // printListWithTree(headListNode); //REMOVE BEFORE TURNED IN
  }
  //Now, printf
  printTreeListToFile(outputFileName, headListNode, huffmanLength);

  return headListNode;
}

//print tree pre-order
void printPreorder(TreeNode * tn)
{
    if (tn == NULL){
      return;
    }

    if(tn->right == NULL && tn->left == NULL){ //reached the leaf node
      printf(" Value: %c, Freq: %d\n",tn->value,tn->freq);
    }

    printPreorder(tn->left);

    printPreorder(tn->right);
}

void printTreeListToFile(char * outputFilePath, ListNode * headListNode, int length){
  TreeNode * tn = headListNode->treeNodePtr;
  int arrayLength = (int)ceil((double)length/2);
  //this array store the path to a particular node
  int * pathArr = malloc(sizeof(int)*arrayLength);
  char * stringPrinted = NULL;
  //open file for writing

  FILE * outputFilePtr = fopen(outputFilePath,"w");
  if(outputFilePtr == NULL){
    printf("Unable to write to code file, path is wrong (this should not happen)");
    fclose(outputFilePtr);
    return;
  }
  //initialize array
  for(int i = 0 ; i<arrayLength; i++){
    pathArr[i] = -1; //-1 mean the end of the array. do not change here
  }

  //traverse the linked list and print list
  printTreeListPreorderToFile(pathArr, arrayLength,  tn, outputFilePtr, stringPrinted);

  fclose(outputFilePtr);
  free(pathArr);
}

//this function print the tree path to the 'value'
void printTreeListPreorderToFile(int * huffmanCode, int length, TreeNode * tn, FILE * outputFilePtr, char * stringPrinted){

  /* first print data of node */
  if(tn->right == NULL && tn->left == NULL){ //reached the leaf node
      int trueArrayLength = 0; //the array length without the -1
      //count the element in the huffmancode array that is not -1
      while (trueArrayLength != length  && huffmanCode[trueArrayLength]!=-1) trueArrayLength
      //print char
      fprintf (outputFilePtr, "%c:",tn->value);
      //print the tree path code
      for(int i = 0 ; i < trueArrayLength; i++ ){
          fprintf(outputFilePtr, "%d",huffmanCode[i]);
      }
      //print new line
      fprintf (outputFilePtr, "\n");
      // fprintf(stringPrinted , 1 , writeSize, outputFilePtr);
    return;
  }

    push(huffmanCode, 0, length);
    printTreeListPreorderToFile(huffmanCode,length,tn->left,outputFilePtr,stringPrinted);
    pop(huffmanCode,length);

    push(huffmanCode, 1,length);
    printTreeListPreorderToFile(huffmanCode,length,tn->right,outputFilePtr,stringPrinted);
    pop(huffmanCode,length);

}

//this function append 'num' into the end of the array 'huffmanCode'
void push(int * huffmanCode, int num, int length){
  int lastIndex = 0;
  if (huffmanCode[0] == -1) {
    huffmanCode[0] = num;
    // printf("\npushing:\n");
    //
    // for (int i = 0; i < length; i++) {
    //   printf("pushed: huffmanCode: %d\n",huffmanCode[i] );
    // }
    return;
  }
  while(huffmanCode[lastIndex]!=-1){
    lastIndex++;
    if (lastIndex == length) {
      // reached the end, array fulled
      // again this should not happen
      printf("ERROR: ARRAY FULL\n" );
      return;
    }
  }
  // printf("\npushing:\n");

  huffmanCode[lastIndex] = num;
  // for (int i = 0; i < length; i++) {
  //   printf("pushed: huffmanCode: %d\n",huffmanCode[i] );
  // }
  return;
}

void pop(int * huffmanCode, int length){
  int lastIndex = 0;
  if (huffmanCode[0] == -1) {
    //Nothing to pop
    // again this should not happen
    printf("ERROR: ARRAY EMPTY\n");
    return;
  }
  while(huffmanCode[lastIndex]!=-1 && lastIndex != length){
    lastIndex++;
  }
    huffmanCode[lastIndex - 1] = -1;
    // printf("\npoping:\n");
    // for (int i = 0; i < length; i++) {
    //   printf("poped: huffmanCode: %d\n",huffmanCode[i] );
    // }
    return;
  }
