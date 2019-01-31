#include "utilities.h"
#include "list.h"

void printListWithTree(ListNode * head){
  ListNode *  curPtr = head;
  int count = 0;
  while (curPtr != NULL) {
    printf("Index: %d, Value: %c, Freq: %d\n",count,curPtr->treeNodePtr->value,curPtr->treeNodePtr->freq);
    curPtr = curPtr->nxtNode;
    count ++;
  }
}
