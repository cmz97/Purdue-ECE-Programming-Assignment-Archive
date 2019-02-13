#include "shell_list.h"
#include <stdio.h>
#include <stdlib.h>

Node * List_insert_rear(Node * head, Node * ln);

typedef struct List {
  Node *node;
  struct List *next;
} List;


Node *List_Load_From_File(char *filename){
  int size = 0;
  FILE * inputFilePtr = fopen(filename,"r");
  long curLong = 0;
  Node * headNode = NULL;
  Node * curNode = NULL;

  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist\n");
    fclose(inputFilePtr);
    return NULL;
  }

  while(fread(&curLong, sizeof(long), 1, inputFilePtr) == 1) (size)++;
  fseek(inputFilePtr, 0, SEEK_SET); //now put back the file pointer

  for(int i = 0 ; i < size ; i++){
    fread(&curLong, sizeof(long), 1, inputFilePtr);
    curNode = malloc(sizeof(Node));
    curNode->value = curLong;
    curNode->next = NULL;
    headNode = List_insert_rear(headNode,curNode);
    // printf("numArray[%d]:%ld\n",i,curLong);
  }
  fclose(inputFilePtr);
  return headNode;
}

int List_Save_To_File(char *filename, Node *list){
  int size = 0;
  FILE * outputFilePtr = fopen(filename,"w");
  if(outputFilePtr == NULL){
    printf("Can not create file\n");
    fclose(outputFilePtr);
    return 0;
  }
  Node * curNode = list;
  while(curNode != NULL){
    fwrite(&(curNode->value),sizeof(long),1,outputFilePtr);
    curNode = curNode->next;
    size ++;
  }
  fclose(outputFilePtr);
  return size-1;
}

Node *List_Shellsort(Node *list, double *n_comp){
  return list;
}

Node * List_insert_rear(Node * head, Node * ln){
  if (ln == NULL){
    printf("ERROR! ln is NULL\n");
    return NULL;
  }
  if ((ln -> next) != NULL){
      printf("ERROR! ln -> next is not NULL\n");
      return NULL;
  }
  if (head == NULL)return ln;

  Node * curNode = head;

  while (curNode->next != NULL) curNode = curNode->next; //traverse to the end
  curNode->next = ln
  return head;
}
