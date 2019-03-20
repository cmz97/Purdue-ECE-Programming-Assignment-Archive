#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _treenode{
  struct _treenode * left; //non-leaf node
  struct _treenode * right; //non-leaf node

  int key;
  char binPat; //Binary Pattern, indicate right and left null or not
  int height;

} TreeNode;

bool constructTree(FILE * fptr,TreeNode ** headNode);
void printTreePreOrderToFile(TreeNode * headNode, char * outputFileName);
int getMax(int first, int second);
int getHeight(TreeNode * tnode);
TreeNode * treeRotation(TreeNode * tNode, int rotationMode);
TreeNode * autoBalance(TreeNode * curNode, int insertedKey);
TreeNode * insertNodeUlti(TreeNode * curNode, TreeNode * myNode);
TreeNode * insertNode(TreeNode * headNode, int key);
void Tree_destroy(TreeNode * tn);
