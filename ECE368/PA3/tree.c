#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//post order to get the nodal capacitance

void printDelay2FilePreorder(TreeNode * tn, double delay, double pathres,FILE * outputFilePtr){
  //the pathres include the current path
  double leftDelay = 0;
  double rightDelay = 0;
  double myDelay = 0;
  pathres += tn->res;
  // printf("<Path Resistance> %le\n",pathres);
  if(tn->left == NULL && tn->right == NULL){ //leafNode
    delay += pathres*pathres*tn->nodalCap;
    tn->tn_delay = delay/pathres;
    // printf("<TN_DELAY> label:%d delay:%le pathRes:%le\n",tn->label,tn->tn_delay,pathres);
    fwrite(&tn->label,sizeof(int), 1, outputFilePtr);
    fwrite(&tn->tn_delay,sizeof(double),1, outputFilePtr);
    return;
  }
  myDelay = pathres*pathres * tn->nodalCap + delay;


  leftDelay = myDelay + pathres*pathres*tn->right->totalNodalCap;
  printDelay2FilePreorder(tn->left,leftDelay,pathres,outputFilePtr);
  rightDelay = myDelay + pathres*pathres*tn->left->totalNodalCap;
  // printf("tn->left->totalNodalCap:%le\n", tn->left->totalNodalCap);
  printDelay2FilePreorder(tn->right,rightDelay,pathres,outputFilePtr);

}

double fillInNodalCapacitance(TreeNode * curNode){
  if (curNode->left == NULL && curNode->right == NULL ) { //leaf Node
    //update self nodal capacitance
    curNode -> nodalCap = (curNode->cap / 2) + curNode -> SNCap;
    curNode -> totalNodalCap = curNode -> nodalCap;
    return curNode->cap; //return the upsteam capacitance
  }
  //non leaf Node
  double leftCap = fillInNodalCapacitance(curNode->left);
  double rightCap = fillInNodalCapacitance(curNode->right);
  curNode -> nodalCap = (curNode->cap + leftCap + rightCap) / 2;
  curNode -> totalNodalCap = curNode->left->totalNodalCap + curNode->right->totalNodalCap + curNode -> nodalCap;
  return curNode->cap;
}


//**Note that when you push to list, you change from post order to pre order.
TreeNode * constructTree(char * inputfileName, double * rd, double * r, double * c){
  FILE * inputFilePtr = fopen(inputfileName,"r");
  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist\n");
    fclose(inputFilePtr);
    return NULL;
  }
  //start to make the stack for my shit
  ListNode * headList = NULL;
  ListNode * thisListNode = NULL;

  //get the header line
  fscanf(inputFilePtr, "%le %le %le\n", rd, r, c);
  printf("header: rd <%le> r <%le> c <%le>\n",*rd, *r, *c);

  //temp data for reading
  int label = 0; //label of the leaf node
  double SNCap= 0; //sink node capacitance
  double leftWL = 0; //left wire length
  double rightWL = 0; //right wire length
  char curLine[100]; //buffer string

  TreeNode * rightNode = NULL;
  TreeNode * leftNode = NULL;
  TreeNode * returnNode = NULL;

  while(fgets(curLine,100,inputFilePtr)!=NULL){
    if(sscanf(curLine, "%d(%le)", &label, &SNCap) == 2){ //The leaf Node
      // printf("<Leaf Node> label: %s%d%s SNCap: %s%le%s\n",KRED,label,KRESET,KRED, SNCap, KRESET);
      thisListNode = malloc(sizeof(ListNode));
      thisListNode -> tn = malloc(sizeof(TreeNode));
      thisListNode -> tn = initTree(thisListNode -> tn);

      thisListNode -> tn -> SNCap = SNCap;
      thisListNode -> tn -> label = label;
      thisListNode -> nxtNode = NULL;
      headList = List_insert(headList,thisListNode);

    }else if(sscanf(curLine, "(%le %le)", &leftWL, &rightWL) == 2){ //Non Leaf Node
      // printf("<None Leaf Node> Leftlength: %s%le%s, Rightlength: %s%le%s\n",KRED,leftWL,KRESET, KRED,rightWL,KRESET);
      thisListNode = malloc(sizeof(ListNode));
      thisListNode -> tn = malloc(sizeof(TreeNode));
      thisListNode -> tn = initTree(thisListNode -> tn);

      //child wireLength for printing
      thisListNode -> tn -> leftWireLength = leftWL;
      thisListNode -> tn -> rightWireLength = rightWL;


      //pop treeNode, assume two node already in
      rightNode = popListNode(&headList);
      rightNode -> wireLength = leftWL;
      rightNode -> cap = rightWL * (*c);
      rightNode -> res = rightWL * (*r);

      leftNode = popListNode(&headList);
      leftNode -> wireLength = leftWL;
      leftNode -> cap = leftWL * (*c);
      leftNode -> res = leftWL * (*r);
      thisListNode -> nxtNode = NULL;

      //assign left and right
      thisListNode -> tn -> right = rightNode;
      thisListNode -> tn -> left = leftNode;

      //push back this ListNode
      headList = List_insert(headList,thisListNode);
      //from here, calculate the line cap and line res to the children node
    }else{
      printf("some thing is wrong while parse\n");
    }
  }
  //add the rd to the headNode
  thisListNode -> tn -> res = *rd;
  returnNode = thisListNode -> tn;

  free(thisListNode);
  fclose(inputFilePtr);
  printf("\n");

  return returnNode;
}

TreeNode * initTree(TreeNode * tn){
  tn -> wireLength = 0; //the wireLength from parent to me
  tn -> cap = 0; //capacitance AT the Node
  tn -> res = 0; //resistance from parent to me

  tn -> SNCap = 0; //Sink Node Cap
  tn -> label = 0; //label for the leaf node

  tn -> nodalCap = 0;

  tn ->leftWireLength = 0;
  tn ->rightWireLength = 0;

  tn -> left = NULL;
  tn -> right = NULL;

  tn -> totalNodalCap = 0;
  tn -> tn_delay = 0;
  return tn;
}

ListNode * List_insert(ListNode * head, ListNode * ln){

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

TreeNode * popListNode(ListNode ** head){
  //this function pop the first treeNode and free the listNode
  if (*head == NULL){
    printf("ERROR: Can not pop anymore\n");
    return NULL;
  }
  // TreeNode * headNode = (*head) -> tn;

  // printf("%sCHECK%s <Pop TreeNode> label: %s%d%s wireLength: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KYEL,KRESET,KGRN,headNode->label,KRESET,KRED,headNode->wireLength,KRESET,KRED,headNode->cap,KRESET,KRED,headNode->res,KRESET,KRED,headNode->SNCap,KRESET);

  TreeNode * returnNode = (*head) -> tn;
  ListNode * oldHead = *head;
  *head = (*head) -> nxtNode;
  free(oldHead);

  return returnNode;
}

void preOrder2File1(TreeNode * tn, char * outputFileName){
  FILE * outputFilePtr = fopen(outputFileName,"w");
  if(outputFilePtr == NULL){
    printf("output File Does Not Exist\n");
    fclose(outputFilePtr);
    return;
  }
  preOrder2File1Util(tn, outputFilePtr);
  fclose(outputFilePtr);

}

void preOrder2File1Util(TreeNode * tn, FILE * outputFilePtr){
  if(tn == NULL){
    return;
  }
  // printf("<treeNode> nodalCap: %s%le%s label: %s%d%s totalNodalCap: %s%le%s cap: %s%le%s res: %s%le%s SNCap: %s%le%s\n",KRED,tn->nodalCap,KRESET,KGRN,tn->label,KRESET,KRED,tn->totalNodalCap,KRESET,KRED,tn->cap,KRESET,KRED,tn->res,KRESET,KRED,tn->SNCap,KRESET);
  if(tn->left == NULL && tn->right == NULL){ //leaf node
    fprintf(outputFilePtr, "%d(%le)\n",tn->label,tn->SNCap);
  }else{
    fprintf(outputFilePtr, "(%le %le)\n",tn->leftWireLength,tn->rightWireLength);
  }
  preOrder2File1Util(tn->left,outputFilePtr);
  preOrder2File1Util(tn->right,outputFilePtr);
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
