#include "util.h"

int checkAVL(TreeNode * curNode){
  if (curNode == NULL) {
    return 1;
  }

  int balance = getNodalBalance(curNode);
  int avl = 1;

  if (balance < -1 || balance > 1) avl = 0;

  return checkAVL(curNode -> left) && checkAVL(curNode -> right) && avl;
}

int checkBST(TreeNode * curNode){
  if (curNode== NULL) {
    return 1;
  }

  int bst;
  if (curNode -> left == NULL && curNode ->right == NULL) { // leafNode, aways BST
    bst = 1;
  }else if (curNode -> left == NULL && curNode -> right != NULL) {
    if (curNode -> right -> key >= curNode -> key) {
      bst = 1;
    }else{
      bst = 0;
    }
  }else if (curNode -> left != NULL && curNode -> right == NULL) {
    if (curNode -> left -> key <= curNode -> key) {
      bst = 1;
    }else{
      bst = 0;
    }
  }else{
    if (curNode -> left -> key <= curNode -> key && curNode -> right -> key >= curNode -> key) {
      bst = 1;
    }else{
      bst = 0;
    }
  }

  return checkBST(curNode -> left) && checkBST(curNode -> right) && bst;
}


bool constructTree(FILE * fptr,TreeNode ** headNode){
  int numNode = 0;
  int curKey = 0;
  char curOperation = 0;


  while(fread(&curKey, sizeof(int), 1, fptr) == 1 && fread(&curOperation, sizeof(char), 1, fptr) == 1){
    numNode++;
    if (curOperation == 'i') {
      *headNode = insertNode(*headNode,curKey);
      DEBUG_pretty_tree(*headNode);
    }else if (curOperation == 'd'){
      *headNode = deleteNode(*headNode,curKey);
      DEBUG_pretty_tree(*headNode);
    }
  }

  if (feof(fptr) == 0){ //where the end of file is not reached
    return false; // can open and correct format
  }

  return true;
}

int buildEvalTreePre(char * evalFileName, TreeNode ** headNode){
  FILE * evalFilePtr = fopen(evalFileName,"r");
  int curKey = 0;
  char curBinPat = 0;
  ListNode * headList = NULL;
  ListNode * curListNode = NULL;
  TreeNode * leftNode = NULL;
  TreeNode * rightNode = NULL;

  int sizeOfFile = 0;

  if(evalFilePtr == NULL){
    fclose(evalFilePtr);
    return -1; //can not open
  }

  //get file size
  while(fread(&curKey, sizeof(int), 1, evalFilePtr) == 1 && fread(&curBinPat, sizeof(char), 1, evalFilePtr) == 1)sizeOfFile++;

  if (feof(evalFilePtr) == 0){ //where the end of file is not reached
    fclose(evalFilePtr);
    return 0; // can open and correct format
  }

  //create array for post order
  int * arrKey = malloc(sizeof(int)*sizeOfFile);
  char * arrChar = malloc(sizeof(char)*sizeOfFile);

  fseek(evalFilePtr, 0, SEEK_SET); //now put back the file pointer

  int index = sizeOfFile;
  while(fread(&curKey, sizeof(int), 1, evalFilePtr) == 1 && fread(&curBinPat, sizeof(char), 1, evalFilePtr) == 1){
    //fill in reversely as post order
    index--;
    arrKey[index] = curKey;
    arrChar[index] = curBinPat;
  }

  for (int i = 0; i < sizeOfFile; i++) {
    curKey = arrKey[i]; //get current ky
    curBinPat = arrChar[i]; //get current binary pattern

    curListNode = malloc(sizeof(ListNode)); //create listNode
    curListNode -> treeNode = malloc(sizeof(TreeNode)); //malloc treeNode
    curListNode -> treeNode -> left = NULL;
    curListNode -> treeNode -> right = NULL;
    curListNode -> treeNode -> key = curKey;
    curListNode -> treeNode -> height = 1; //TODO: have not update height yet.
    curListNode -> nxtNode = NULL;

    if (curBinPat == 0) { //leafNode push to stack
      headList = push(headList,curListNode);
    }else if(curBinPat == 1){ //left NULL right child
      rightNode = pop(&headList);
      curListNode -> treeNode -> right = rightNode;
      curListNode -> treeNode-> height = getHeight(rightNode) + 1;
      headList = push(headList,curListNode);
    }else if(curBinPat == 2){ //left child right NULL
      leftNode = pop(&headList);
      curListNode -> treeNode -> left = leftNode;
      curListNode -> treeNode-> height = getHeight(leftNode) + 1;
      headList = push(headList,curListNode);
    }else if(curBinPat == 3){ //left child right child
      //pop treeNode, assume two node already in
      leftNode = pop(&headList);
      rightNode = pop(&headList);
      //assign left and right
      curListNode -> treeNode -> right = rightNode;
      curListNode -> treeNode -> left = leftNode;
      curListNode -> treeNode-> height = getMax(getHeight(leftNode),getHeight(rightNode)) + 1;
      //push back this ListNode
      headList = push(headList,curListNode);
    }
  }

  *headNode = pop(&headList);


  free(arrChar);
  free(arrKey);

  fclose(evalFilePtr);
  return 1; // can open and correct format
}

ListNode * push(ListNode * head, ListNode * ln){
  if (ln == NULL){
    printf("Something wrong 1\n");

    return NULL;
  }
  if ((ln -> nxtNode) != NULL){
      printf("Something wrong 2\n");
      return NULL;
  }
  // TreeNode * headNode = ln -> tn;
  //CODE BLOCK BELLLOW IS FOR REAR APPENDs
  // printf("%sCHECK%s <Insert TreeNode> label: %s%d%s wireLength: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KYEL,KRESET,KGRN,headNode->label,KRESET,KRED,headNode->wireLength,KRESET,KRED,headNode->cap,KRESET,KRED,headNode->res,KRESET,KRED,headNode->SNCap,KRESET);

  if (head == NULL){
    return ln;
  }
  ln -> nxtNode = head;
  return ln;
}

TreeNode * pop(ListNode ** head){
  if (*head == NULL){
    printf("ERROR: Can not pop anymore\n");
    return NULL;
  }
  // TreeNode * headNode = (*head) -> tn;

  // printf("%sCHECK%s <Pop TreeNode> label: %s%d%s wireLength: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KYEL,KRESET,KGRN,headNode->label,KRESET,KRED,headNode->wireLength,KRESET,KRED,headNode->cap,KRESET,KRED,headNode->res,KRESET,KRED,headNode->SNCap,KRESET);

  TreeNode * returnNode = (*head) -> treeNode;
  ListNode * oldHead = *head;
  *head = (*head) -> nxtNode;
  free(oldHead);

  return returnNode;
}


TreeNode * deleteNode(TreeNode * curNode, int key){
  if (curNode == NULL) {
    return curNode;
  }

  if (key > curNode->key ) { //look to the right
    curNode -> right = deleteNode(curNode -> right, key);
  }else if (key < curNode -> key ){ //look to the left
    curNode -> left = deleteNode(curNode -> left, key);
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
      if (/* condition */) {
        /* code */
      }
      TreeNode * tempNode = getImediatePredecessor(curNode -> left);
      curNode -> key = tempNode -> key; //exchange the value
      curNode -> left = deleteNode(curNode -> left, tempNode -> key); //delete the immediate successor
    }
  }
  //curNode might get deleted
  if (curNode == NULL) return NULL;

  curNode -> height = getMax(getHeight(curNode->left),getHeight(curNode->right)) + 1; //update height
  // DEBUG_pretty_tree(curNode);
  return autoBalance(curNode); //autoBalance

}

TreeNode * getImediatePredecessor(TreeNode * curNode){
  while(curNode->right != NULL){
    curNode = curNode -> right;
  }
  return curNode;
}

void printTreePreOrderToFile(TreeNode * headNode, char * outputFileName){
  FILE * outputFilePtr = fopen(outputFileName,"w");
  if(outputFilePtr == NULL){ //The problem description did not specify the error report, ignore for now
    fclose(outputFilePtr);
    return;
  }
  printTreePreOrderToFileUtil(headNode, outputFilePtr);
  fclose(outputFilePtr);
}

void printTreePreOrderToFileUtil(TreeNode * curNode, FILE * fptr){
  if (curNode == NULL) {
    return;
  }
  char binPat = 0; //binary pattern

  fwrite(&(curNode->key), sizeof(int), 1, fptr);
  if (curNode -> right != NULL){
    binPat |= 1 << 0; //right branch is non NULL node
  } //else default is 0;
  if (curNode -> left != NULL){
    binPat |= 1 << 1; //left branch is non NULL node
  } //else default is 0;

  fwrite(&(binPat), sizeof(char), 1, fptr); // write the bin-pat
  printf("Key:%d BinPat:%d\n",curNode->key, binPat );
  printTreePreOrderToFileUtil(curNode -> left, fptr);
  printTreePreOrderToFileUtil(curNode -> right, fptr);

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
