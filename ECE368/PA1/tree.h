#include <stdlib.h>

typedef struct treenode{
  struct treenode * left;
  struct treenode * right;
  unsigned char value; //characters
  long freq; //frequencies
}TreeNode;

TreeNode * TreeNode_create(unsigned char val, long freq);
TreeNode * Tree_merge(TreeNode * becomesLeftChild, TreeNode * becomesRighChild);
void Tree_destroy(TreeNode * tn);
