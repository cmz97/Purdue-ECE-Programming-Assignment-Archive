typedef struct _treenode{
  //fill by parent
  double wireLength; //the wireLength from parent to me
  double cap; //capacitance AT the Node
  double res; //resistance from parent to me

  //self filled

  double SNCap; //for leaf Node
  int label; //for leaf Node

  struct _treenode * left; //non-leaf node
  struct _treenode * right; //non-leaf node
} TreeNode;

typedef struct _listNode{
  TreeNode * tn;
  struct _listNode * nxtNode;
} ListNode;

TreeNode * constructTree(char * inputfileName, double * rd, double * r, double * c);
TreeNode * initTree(TreeNode * tn);
TreeNode * popListNode(ListNode ** head);
ListNode * List_insert(ListNode * head, ListNode * ln);
void postOrderDEBUG(TreeNode * tn);

#define KRED  "\x1B[31m"
#define KRESET "\033[0m"
#define KGRN  "\x1B[32m"

void Tree_destroy(TreeNode * tn);
