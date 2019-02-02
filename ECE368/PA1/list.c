#include "list.h"


ListNode * newListNode(TreeNode * tn){
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> nxtNode = NULL;
  ln -> treeNodePtr = tn;
  return ln;
}

//this function merge the first two list node
ListNode * mergeListNode(ListNode * head){
  ListNode * second = head->nxtNode;
  ListNode * third = second -> nxtNode;

  TreeNode * tn1 = head -> treeNodePtr;
  TreeNode * tn2 = second -> treeNodePtr;

  free(head);
  free(second);
  head = third;
  TreeNode * mrg;
  mrg = Tree_merge(tn2,tn1);
  ListNode * ln = newListNode(mrg);
  head = List_insert(head,ln);
  return head;
}

// //Insert Node according to its ASCII value as well as the frequencies
// ListNode * List_insert_ASCII(ListNode * head, ListNode * ln)
// {
//   if (ln == NULL)
//     {
//       printf("ERROR! ln is NULL\n");
//       return NULL;
//     }
//   if ((ln -> nxtNode) != NULL){
//       printf("ERROR! ln -> next is not NULL\n");
//       return NULL;
//   }
//
//   char standardValue = ln->treeNodePtr->value;
//   // int standardFreq = ln->treeNodePtr->freq;
//   ListNode *  curListPtr = head;
//   ListNode *  nxtListPtr = curListPtr->nxtNode; //Might be NULL
//
//   //if the current head is bigger than the node that we want to insert
//   //this time the head will be change
//   //which mean the inserted node is the smallest
//   if (curListPtr->treeNodePtr->value > standardValue) {
//     ln -> nxtNode = head;
//     return ln;
//   }
//   while(nxtListPtr != NULL){
//     //Note that '==' should never appear because of if block in main.c line:64
//     if (nxtListPtr->treeNodePtr->value < standardValue) {
//       curListPtr = curListPtr -> nxtNode;
//       nxtListPtr = curListPtr->nxtNode;
//     }else{
//       ln->nxtNode = nxtListPtr;
//       curListPtr -> nxtNode = ln;
//       return head;
//     }
//   }
//
//   //this mean the inserted node is the largest
//   ln->nxtNode = nxtListPtr;
//   curListPtr -> nxtNode = ln;
//   return head;
//
// }

ListNode * List_insert(ListNode * head, ListNode * ln){
  if (ln == NULL){
    printf("ERROR! ln is NULL\n");
    return NULL;
  }
  if ((ln -> nxtNode) != NULL){
      printf("ERROR! ln -> next is not NULL\n");
      return NULL;
  }
  //CODE BLOCK BELLLOW IS FOR REAR APPENDs
  if (head == NULL)return ln;

  ln -> nxtNode = head;
  return ln;
}


//Alert: This function pretend everything except for the first element is sorted
ListNode * sortList(ListNode * head){
  ListNode * newHead = head->nxtNode;
  int standardFreq = head->treeNodePtr->freq;
  ListNode *  curListPtr = head->nxtNode;
  ListNode *  nxtListPtr = curListPtr->nxtNode;
  while(nxtListPtr != NULL){
    if (nxtListPtr->treeNodePtr->freq <= standardFreq) {
      curListPtr = curListPtr -> nxtNode;
      nxtListPtr = curListPtr->nxtNode;
    }else{
      head->nxtNode = nxtListPtr;
      curListPtr -> nxtNode = head;
      return newHead;
    }
  }
  head->nxtNode = nxtListPtr;
  curListPtr -> nxtNode = head;
  return newHead;
}

//Alert: This function only work if all list node contain on and only one treenode
int listHas(ListNode * head, unsigned char b){
  ListNode *  curPtr = head;
  while (curPtr != NULL) {
    if (curPtr->treeNodePtr->value == b) {
      return 1;
    }
    curPtr = curPtr->nxtNode;
  }
  return 0;
}

//This function return the ListNode that has the character
ListNode * getElement(ListNode * head, unsigned char character){
  ListNode *  curPtr = head;
  while (curPtr != NULL) {
    if (curPtr->treeNodePtr->value == character) {
      return curPtr;
    }
    curPtr = curPtr->nxtNode;
  }
  return NULL;
}

//This function sort a 1d singlely linked list according to its ASCII value


ListNode * sort1dListAccord2Ascii(ListNode * headListNode)
{
  ListNode * sortedHead = NULL;
  ListNode * next = NULL;
  ListNode * current = headListNode;

  while (current != NULL)
  {
      next = current->nxtNode;
      sortedHead = sortedInsert(sortedHead,current);

      current = next;
  }

  return sortedHead;
}

ListNode * sortedInsert(ListNode * headListNode, ListNode * newNode)
{
    ListNode * current = NULL;

    if (headListNode == NULL || ((headListNode->treeNodePtr->value >= newNode->treeNodePtr->value) && (headListNode->treeNodePtr->freq == newNode->treeNodePtr->freq))){
        newNode->nxtNode = headListNode;
        headListNode = newNode;
        return headListNode;
    }

    current = headListNode;
    while (current->nxtNode!=NULL && ((current->nxtNode->treeNodePtr->value < newNode->treeNodePtr->value) || (current->nxtNode->treeNodePtr->freq < newNode->treeNodePtr->freq))){
        current = current->nxtNode;
    }

    newNode->nxtNode = current->nxtNode;
    current->nxtNode = newNode;

    return headListNode;
}

//This function get the number of char in a file, our linked list
int getHuffmanLength(ListNode * ln){
  int count = 0;
  while(ln != NULL){
    ln = ln -> nxtNode;
    count ++;
  }
  return count;
}
