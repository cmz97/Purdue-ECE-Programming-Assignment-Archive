#include "util.h"

s

void DEBUG_PreorderPrint(TreeNode * curNode){
  if(curNode == NULL){
    return;
  }
  printf("curKey: %d\n", curNode->key);
  DEBUG_PreorderPrint(curNode->left);
  DEBUG_PreorderPrint(curNode->right);
}
