#include <stdio.h>
#include <stdlib.h>
#include "tree.h"


typedef struct listnode{
 struct listnode * nxtNode;
 TreeNode * treeNodePtr;
}ListNode;

ListNode * newListNode(TreeNode * );
ListNode * mergeListNode(ListNode * );
ListNode * List_insert(ListNode * , ListNode * );
int listHas(ListNode * , unsigned char);
ListNode * getElement(ListNode * , unsigned char );
ListNode * sortList(ListNode * );
// ListNode * List_insert_ASCII(ListNode * , ListNode * );
int getHuffmanLength(ListNode * );
ListNode * sort1dListAccord2Ascii(ListNode * );
ListNode * sortedInsert(ListNode * , ListNode * );
void debugNodes(ListNode * curNode);
ListNode * List_delete(ListNode *h, ListNode * u);
ListNode * update_list_by_freq(ListNode * head, ListNode * ln);
