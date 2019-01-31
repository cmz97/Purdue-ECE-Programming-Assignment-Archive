#include "list.h"


ListNode * newListNode(TreeNode * tn){
  ListNode * ln = malloc(sizeof(ListNode));
  ln -> nxtNode = NULL;
  ln -> treeNodePtr = tn;
  return ln;
}

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

ListNode * List_insert(ListNode * head, ListNode * ln)
{
  if (ln == NULL)
    {
      printf("ERROR! ln is NULL\n");
      return NULL;
    }
  if ((ln -> nxtNode) != NULL)
    {
      printf("ERROR! ln -> next is not NULL\n");
    }
  if (head == NULL)
    {
      return ln;
    }
    ln -> nxtNode = head;
    return ln;
}

ListNode * sortList(ListNode * head){
  return NULL;
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

ListNode * getElement(ListNode * head, unsigned char character){
  ListNode *  curPtr = head;
  while (curPtr != NULL) {
    if (curPtr->treeNodePtr->value == character) {
      return curPtr;
    }
    curPtr = curPtr->nxtNode;
  }
  return NULL; //this should never happen though
}
