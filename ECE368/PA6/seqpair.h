#define KRED  "\x1B[31m"
#define KRESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _rectNode{
  int * verticalAdjList;
  int * horzontalAdjList;

  double width;
  double height;

  double x;
  double y;

  int color;
  int label;

} RectNode;

// typedef struct _adjNode{
//   struct RectNode * this; //non-leaf node
//   struct RectNode * next; //non-leaf node
// } AdjNode;

// void DEBUG_Print_Array(int * Array, int Size);
// void DEBUG_AdjList(RectNode ** rectNodeArr, int size);

int * generateLUT(int * seqOne, int sizeofSeq);
void processAdjList(RectNode ** rectNodeArr, int * seqTwo, int sizeofSeq, int * lut);
int * initArr(int * arr, int size);
int * toplogicalSort(RectNode ** rectNodeArr, int * toplogicalSortList, int numberOfRect, int mode);
void dfs(RectNode * curStartingNode, RectNode ** rectNodeArr, int * toplogicalSortList, int * curIndexOfArray, int mode);
// void DEBUG_Print_RectNodeArray(RectNode ** Array, int Size);
RectNode ** updateCoordinates(RectNode ** rectNodeArr, int * toplogicalSortList, int numberOfRect, int mode);
