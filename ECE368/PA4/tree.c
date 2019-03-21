#include "util.h"

bool constructTree(FILE * fptr,TreeNode ** headNode){
  int numNode = 0;
  int curKey = 0;
  char curOperation = 0;


  while(fread(&curKey, sizeof(int), 1, fptr) == 1 && fread(&curOperation, sizeof(char), 1, fptr) == 1){
    printf("\n<Inserting Node>curKey: %d, curOperation: %c\n", curKey, curOperation);
    numNode++;
    if (curOperation == 'i') {
      *headNode = insertNode(*headNode,curKey);
    }else if (curOperation == 'd'){
      printf("Before Deletion\n");
      DEBUG_pretty_tree(*headNode);
      *headNode = deleteNode(*headNode,curKey);
    }
  }
  return true;
}

TreeNode * deleteNode(TreeNode * curNode, int key){
  if (curNode == NULL) {
    return curNode;
  }

  if (key > curNode->key ) { //look to the right
    curNode -> right = deleteNode(curNode -> right, key);
  }else if (key < curNode -> key ){ //look to the left
    curNode -> right = deleteNode(curNode -> right, key);
  }else{ //found the target of deletion
    if (curNode -> left == NULL || curNode -> right == NULL) { //one or no child
      TreeNode * tempNode = NULL;
      if (curNode -> left != NULL ) { // left child only
        tempNode = curNode -> left;
        * curNode = * tempNode;
      }else if (curNode -> right != NULL ){ // right child only
        tempNode = curNode -> right;
        * curNode = * tempNode;
      }else{ // no child
        tempNode = curNode;
        curNode = NULL;
      }
      free(tempNode); //free current deleted Node
    }else{ //two children
      TreeNode * tempNode = getImediateSuccessor(curNode -> right);
      curNode -> key = tempNode -> key; //exchange the value
      curNode -> right = deleteNode(curNode -> right, tempNode -> key); //delete the immediate successor
    }
  }

  //curNode might get deleted
  if (curNode == NULL) return NULL;

  curNode -> height = getMax(getHeight(curNode->left),getHeight(curNode->right)) + 1; //update height
  DEBUG_pretty_tree(curNode);
  return autoBalance(curNode); //autoBalance

}

TreeNode * getImediateSuccessor(TreeNode * curNode){
  while(curNode->left != NULL){
    curNode = curNode -> left;
  }
  return curNode;
}

void printTreePreOrderToFile(TreeNode * headNode, char * outputFileName){

}

TreeNode * insertNode(TreeNode * headNode, int key){
  TreeNode * curNode = malloc(sizeof(TreeNode));
  curNode -> left = NULL;
  curNode -> right = NULL;
  curNode -> key = key;
  curNode -> height = 1;
  return insertNodeUlti(headNode,curNode);

}

TreeNode * insertNodeUlti(TreeNode * curNode, TreeNode * myNode){
  if (curNode == NULL) {
    return myNode;
  }
  //insert Node
  printf("myNode -> key = %d curNode -> key = %d\n",myNode -> key, curNode -> key);
  if (myNode -> key <= curNode -> key) {
    curNode -> left = insertNodeUlti(curNode->left,myNode);
    // printf("<Insertion>: 1\n");
  }else{
    curNode -> right = insertNodeUlti(curNode->right,myNode);
    // printf("<Insertion>: 2\n");
  }

  //update height
  curNode -> height = getMax(getHeight(curNode->left),getHeight(curNode->right)) + 1;
  return autoBalance(curNode);
}

TreeNode * autoBalance(TreeNode * curNode){
  int balance = getNodalBalance(curNode);
  int leftBalance = getNodalBalance(curNode-> left);
  int rightBalance = getNodalBalance(curNode -> right);


  printf("<My Balance: %d> <My left Height: %d> <My right Height: %d>\n", balance,getHeight(curNode->left),getHeight(curNode->right));
  //CURRENTLY WORKING ON THE CASES OF ROTATION
  if (balance > 1 && leftBalance >= 0) {  // Left Left
    return treeRotation(curNode,1);
  }

  if (balance < -1 && rightBalance <= 0) {  //Right Right
    return treeRotation(curNode,-1);
  }

  if (balance > 1 && leftBalance < 0){  // Left Right
    curNode->left = treeRotation(curNode->left,-1);
    return treeRotation(curNode,1);
  }

  if (balance < -1 && rightBalance > 0){  // Right Left
    curNode->right = treeRotation(curNode->right,1);
    return treeRotation(curNode,-1);
  }



  return curNode;

}

int getNodalBalance(TreeNode * curNode){
  if (curNode != NULL) return getHeight(curNode->left) - getHeight(curNode->right);
  return 0;
}

TreeNode * treeRotation(TreeNode * tNode, int rotationMode){
  //rotationMode: Left = -1, right = 1;
  if (rotationMode == -1){
    TreeNode * newRoot = tNode->right;
    TreeNode * temp_ptr = newRoot -> left;
    newRoot -> left = tNode;
    tNode -> right = temp_ptr;

    tNode->height = getMax(getHeight(tNode->left), getHeight(tNode->right)) + 1;
    newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
  }else if(rotationMode == 1){
    TreeNode * newRoot = tNode->left;
    TreeNode * temp_ptr = newRoot -> right;
    newRoot -> right = tNode;
    tNode -> left = temp_ptr;

    tNode->height = getMax(getHeight(tNode->left), getHeight(tNode->right)) + 1;
    newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
  }else{
    printf("incorrect rotation Mode\n");
  }
  return NULL;
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

int getHeight(TreeNode * tnode){
  if (tnode == NULL) {
    return 0;
  }
  return tnode->height;
}

int getMax(int first, int second){
  if(first > second) return first;
  return second;
}
