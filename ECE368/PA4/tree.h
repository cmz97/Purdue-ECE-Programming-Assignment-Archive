#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _treenode{
  struct _treenode * left; //non-leaf node
  struct _treenode * right; //non-leaf node

  int key;
  int height;

} TreeNode;

typedef struct _listnode{
  struct _listnode * nxtNode; //next node
  TreeNode * treeNode;
} ListNode;

bool constructTree(FILE * fptr,TreeNode ** headNode);
void printTreePreOrderToFile(TreeNode * headNode, char * outputFileName);
int getMax(int first, int second);
int getHeight(TreeNode * tnode);
TreeNode * treeRotation(TreeNode * tNode, int rotationMode);
TreeNode * autoBalance(TreeNode * curNode);
TreeNode * insertNodeUlti(TreeNode * curNode, TreeNode * myNode);
TreeNode * insertNode(TreeNode * headNode, int key);
void Tree_destroy(TreeNode * tn);
TreeNode * deleteNode(TreeNode * curNode, int key);
TreeNode * getImediatePredecessor(TreeNode * curNode);
int getNodalBalance(TreeNode * curNode);
void printTreePreOrderToFileUtil(TreeNode * curNode, FILE * fptr);
int buildEvalTreePre(char * evalFileName, TreeNode ** headNode);
ListNode * push(ListNode * head, ListNode * ln);
TreeNode * pop(ListNode ** head);
int checkAVL(TreeNode * headNode);
int checkBST(TreeNode * headNode);
