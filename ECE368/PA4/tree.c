// #include "tree.h"
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
    }
  }
  return true;
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
    printf("<Insertion>: 1\n");
  }else{
    curNode -> right = insertNodeUlti(curNode->right,myNode);
    printf("<Insertion>: 2\n");
  }

  //update height
  curNode -> height = getMax(getHeight(curNode->left),getHeight(curNode->right)) + 1;
  return autoBalance(curNode,myNode->key);
}

TreeNode * autoBalance(TreeNode * curNode, int insertedKey){
  int balance = 0;
  if (curNode != NULL) balance =  getHeight(curNode->left) - getHeight(curNode->right);


  //CURRENTLY WORKING ON THE CASES OF ROTATION
  if (balance > 1 && insertedKey < curNode->left->key) {  // Left Left
    printf("<AutoBalance>: 1\n");
    return treeRotation(curNode,1);
  }

  if (balance < -1 && insertedKey > curNode->right->key) {  //Right Right
    printf("<AutoBalance>: 2\n");
    return treeRotation(curNode,-1);
  }

  if (balance > 1 && insertedKey > curNode->left->key){  // Left Right
    printf("<AutoBalance>: 3\n");
    curNode->left = treeRotation(curNode->left,-1);
    return treeRotation(curNode,1);
  }

  if (balance < -1 && insertedKey < curNode->right->key){  // Right Left
    printf("<AutoBalance>: 4\n");
    curNode->right = treeRotation(curNode->right,1);
    return treeRotation(curNode,-1);
  }


  return curNode;

}

TreeNode * treeRotation(TreeNode * tNode, int rotationMode){
  //rotationMode: Left = -1, right = 1;
  if (rotationMode == -1){
    TreeNode * newRoot = tNode->right;
    TreeNode * temp_ptr = newRoot -> left;
    newRoot -> left = tNode;
    tNode -> right = temp_ptr;

    newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    tNode->height = getMax(getHeight(tNode->left), getHeight(tNode->right)) + 1;

    return newRoot;
  }else if(rotationMode == 1){
    TreeNode * newRoot = tNode->left;
    TreeNode * temp_ptr = newRoot -> right;
    newRoot -> right = tNode;
    tNode -> left = temp_ptr;

    newRoot->height = getMax(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    tNode->height = getMax(getHeight(tNode->left), getHeight(tNode->right)) + 1;

    return newRoot;
  }else{
    printf("incorrect rotationMode\n");
  }
  return NULL;
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
