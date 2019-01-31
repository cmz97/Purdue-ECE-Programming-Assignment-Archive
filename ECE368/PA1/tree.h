#include <stdlib.h>

typedef struct treenode{
  struct treenode * left;
  struct treenode * right;
  char value; //characters
  int freq; //frequencies
}TreeNode;

TreeNode * TreeNode_create(char val, int freq);
TreeNode * Tree_merge(TreeNode * becomesLeftChild, TreeNode * becomesRighChild);
void Tree_destroy(TreeNode * tn);
