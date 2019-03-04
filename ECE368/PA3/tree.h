#include <stdio.h>

typedef struct _treenode{
  //fill by parent
  double wireLength; //the wireLength from parent to me
  double cap; //capacitance AT the Node
  double res; //resistance from parent to me

  //child wireLength for printing
  double leftWireLength;
  double rightWireLength;

  //self filled
  double SNCap; //for leaf Node
  int label; //for leaf Node

  double nodalCap; //this is the c'

  struct _treenode * left; //non-leaf node
  struct _treenode * right; //non-leaf node

  //total nodal capacitance DownStream
  double totalNodalCap;

  //delay for leafNode
  double tn_delay;
} TreeNode;

typedef struct _listNode{
  TreeNode * tn;
  struct _listNode * nxtNode;
} ListNode;

TreeNode * constructTree(char * inputfileName, double * rd, double * r, double * c);
TreeNode * initTree(TreeNode * tn);
TreeNode * popListNode(ListNode ** head);
ListNode * List_insert(ListNode * head, ListNode * ln);
void preOrder2File1(TreeNode * tn, char * outputFileName);
void preOrder2File1Util(TreeNode * tn, FILE * outputFilePtr);

void printDelay2FilePreorder(TreeNode * tn, double delay, double pathres, FILE * outputFilePtr);

#define KRED  "\x1B[31m"
#define KRESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"


void Tree_destroy(TreeNode * tn);
double fillInNodalCapacitance(TreeNode * curNode);
