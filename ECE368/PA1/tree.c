#include "tree.h"


TreeNode * TreeNode_create(unsigned char val, long freq)
{
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = val;
  tn -> freq = freq;
  return tn;
}

TreeNode * Tree_merge(TreeNode * becomesLeftChild, TreeNode * becomesRighChild)
{
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = becomesLeftChild;
  tn -> right = becomesRighChild;
  tn -> value = 0; // do not care
  tn -> freq = becomesLeftChild -> freq + becomesRighChild -> freq;
  return tn;
}

void Tree_destroy(TreeNode * tn)
{
  if (tn == NULL)
    {
      return;
    }
  Tree_destroy(tn -> left);
  Tree_destroy(tn -> right);
  free (tn);
}
