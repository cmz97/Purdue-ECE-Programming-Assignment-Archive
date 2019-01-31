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
TreeNode * Tree_merge(TreeNode * , TreeNode * );
