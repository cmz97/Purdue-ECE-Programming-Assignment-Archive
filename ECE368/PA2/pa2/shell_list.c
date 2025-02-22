#include "shell_list.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct List {
  Node *node;
  struct List *next;
} List;


Node * Node_insert_rear(Node * head, Node * ln);
int getNodeListSize(Node * head);
List * divideNodeList(List * headList, Node * list, int k, int listSize, int k_ind, double * n_comp);
void sortedInsert(List * headList, int listIndex, Node * value, int k_ind);
List * List_insert(List * head, List * ln);
void destroyAllList(List * headList);
void debugListofNodes(List * headList);
Node * revert2SingleNodeList(List * headList, long k, int listSize);
void popNodefromList(List * headList, int listIndex, Node ** result);
void debugNodes(Node * curNode);

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
    headNode = Node_insert_rear(headNode,curNode);
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
  int seq_size = 0; //sequence size
  List * headList = NULL;
  int listSize = getNodeListSize(list);
  long * sequence = Generate_2p3q_Seq(listSize,&seq_size);


  for(int i = seq_size - 1 ; i >= 0 ; i--){
    // printf("DEBUG: sequence[2]:%ld\n", sequence[i]);
    headList = divideNodeList(headList,list,sequence[i],listSize,i,n_comp);
    // debugListofNodes(headList);
    list = revert2SingleNodeList(headList,sequence[i],listSize);
    // debugNodes(list);
    destroyAllList(headList);
    headList = NULL;
  }

  free(sequence);
  return list;
}

Node * revert2SingleNodeList(List * headList, long k, int listSize){
  Node * curNode = NULL;
  Node * tempNode = NULL;
  for (int i = 0; i < listSize; i++) {
    popNodefromList(headList,i%k,&tempNode);
    tempNode->next = curNode;
    curNode = tempNode;
    // printf("curNode->%ld, imodk = %ld \n",curNode->value,i%k);
    tempNode = NULL;
  }
  return curNode;
}

void popNodefromList(List * headList, int listIndex, Node ** result){
  List * curList = headList;
  int index = 0;

  while(index!=listIndex && curList!= NULL){
    curList = curList->next;
    index++;
  }

  * result = curList->node;
  curList->node = curList->node->next;
  // printf("curList->node->next->value: %ld\n",curList->node->next->value);
}

void destroyAllList(List * headList){
  List * curList = headList;
  List * tempList = NULL;
  while (curList != NULL) {
    tempList = curList->next;
    free(curList);
    curList = tempList;
  }
}


List * divideNodeList(List * headList, Node * list, int k, int listSize, int k_ind, double * n_comp){
  if (headList != NULL) { //this means the list is not initialized
    printf("HeadList is not NULL\n");
    return NULL;
  }
  List * curList = NULL;
  for (int i = 0; i < k; i++) {
    curList = malloc(sizeof(List));
    curList -> node = NULL;
    curList -> next = NULL;
    headList = List_insert(headList,curList);
  }

  Node * curNode = list;
  Node * tempNode = NULL; //if node deletion
  for (int i = 0; i < listSize; i++) {
    // printf("curNode->%ld, imodk = %d \n",curNode->value,i%k);
    tempNode = curNode->next;
    sortedInsert(headList,i%k,curNode,k_ind);
    *n_comp = *n_comp + 1.0;
    // debugListofNodes(headList);

    curNode = tempNode;
    // if (curNode == NULL) {
    //   printf("ERROR: CurNode is NULL!");
    // }
  }

  //----------- DEBUG -----------
  // debugListofNodes(headList);

  return headList;
}

void debugListofNodes(List * headList){
  List * curList = headList;
  Node * curNode = NULL;
  int listIndex = 0;
  while (curList != NULL) {
    // printf("List[%d]\n",listIndex);
    curNode = curList->node;
    while(curNode!= NULL){
      // printf("curNode:%ld -> ", curNode->value);
      curNode = curNode->next;
    }
    // printf("NULL\n");
    curList = curList->next;
    listIndex++;
  }
}

void debugNodes(Node * curNode){
  while(curNode!= NULL){
    printf("Node:%ld -> ", curNode->value);
    curNode = curNode->next;
  }
}

void sortedInsert(List * headList, int listIndex, Node * thisNode, int k_ind)
{
    List * curList = headList;
    int index = 0;
    int mode = k_ind % 2; //odd for assending, even for dessending

    //traverse to correct list
    while(index!=listIndex && curList!= NULL){
      curList = curList->next;
      index++;
    }

    Node * curNode = curList->node;
    Node * lastNode = NULL;

    if(curNode == NULL){
      thisNode->next = NULL; //continute
      curList->node = thisNode;
      // printf("\n1\n");
      return;
    }
    if (mode == 1) {
      while (curNode->value < thisNode->value && curNode->next != NULL) {
        lastNode = curNode;
        curNode = curNode->next;
      }
    }else{
      while (curNode->value > thisNode->value && curNode->next != NULL) {
        lastNode = curNode;
        curNode = curNode->next;
      }
    }


    //create the new Node
    thisNode->next = NULL;

    // printf("Debug: Currenty curNode->value:%ld value:%ld difference : %ld\n",curNode->value,thisNode->value, curNode->value-thisNode->value);

    if (mode == 1) {
      if (curNode->next == NULL && curNode->value < thisNode->value) { //in the end
        curNode->next = thisNode;
        // printf("\n2\n");
        return;
      }
    }else{
      if (curNode->next == NULL && curNode->value > thisNode->value) { //in the end
        curNode->next = thisNode;
        // printf("\n2\n");
        return;
      }
    }


    if (curList->node == curNode){//in the beginning, first node is greater than the value
      thisNode->next = curNode;
      curList->node = thisNode;
      // printf("\n3\n");
      return;
    }

    //In the middle
    lastNode->next = thisNode;
    thisNode->next = curNode;

    // printf("\n4\n");
    return;
}

List * List_insert(List * head, List * ln){
  if (ln == NULL){
    // printf("ERROR! ln is NULL\n");
    return NULL;
  }
  if ((ln -> next) != NULL){
      // printf("ERROR! ln -> next is not NULL\n");
      return NULL;
  }
  //CODE BLOCK BELLLOW IS FOR REAR APPENDs
  if (head == NULL)return ln;

  ln -> next = head;
  return ln;
}

int getNodeListSize(Node * head){
  Node * curNode = head;
  int length = 0;
  while(curNode != NULL){
    curNode = curNode->next;
    length++;
  }
  // printf("Length from List: %d\n", length);
  return length;
}

Node * Node_insert_rear(Node * head, Node * ln){
  if (ln == NULL){
    // printf("ERROR! ln is NULL\n");
    return NULL;
  }
  if ((ln -> next) != NULL){
      // printf("ERROR! ln -> next is not NULL\n");
      return NULL;
  }
  if (head == NULL)return ln;

  Node * curNode = head;

  while (curNode->next != NULL) curNode = curNode->next; //traverse to the end
  curNode->next = ln;
  return head;
}
