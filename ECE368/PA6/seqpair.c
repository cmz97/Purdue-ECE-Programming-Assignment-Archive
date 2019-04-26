#include "seqpair.h"


int * generateLUT(int * seqOne, int sizeofSeq){
  int * lut = malloc(sizeof(int)*(sizeofSeq + 1)); //account for the offsett to plus one
  for(int i = 0; i < sizeofSeq+1; i++) lut[i] = -1;
  //lut[sizeofSeq] = -1;
  for (int i = 0; i < sizeofSeq; i++) {
    lut[seqOne[i]] = i;
  }
  return lut;
}

RectNode ** updateCoordinates(RectNode ** rectNodeArr, int * toplogicalSortList, int numberOfRect, int mode){
  int curLabel = 0;
  for (int i = 0 ; i <  numberOfRect ; i ++){
     curLabel = toplogicalSortList[i];
     int j = 0;
     if (mode == 1) {
       while(j < numberOfRect && rectNodeArr[curLabel] -> verticalAdjList[j] != -1){
         if (rectNodeArr[rectNodeArr[curLabel] -> verticalAdjList[j]] -> y < rectNodeArr[curLabel] -> y + rectNodeArr[curLabel] -> height ){
           rectNodeArr[rectNodeArr[curLabel] -> verticalAdjList[j]] -> y = rectNodeArr[curLabel] -> y + rectNodeArr[curLabel] -> height;
         }
         j++;
       }
     }else{
       while(j < numberOfRect && rectNodeArr[curLabel] -> horzontalAdjList[j] != -1){
         if (rectNodeArr[rectNodeArr[curLabel] -> horzontalAdjList[j]] -> x < rectNodeArr[curLabel] -> x + rectNodeArr[curLabel] -> width ){
           rectNodeArr[rectNodeArr[curLabel] -> horzontalAdjList[j]] -> x = rectNodeArr[curLabel] -> x + rectNodeArr[curLabel] -> width;
         }
         j++;
       }
     }
  }
  return rectNodeArr;
}

int * toplogicalSort(RectNode ** rectNodeArr, int * toplogicalSortList, int numberOfRect, int mode){
  int curIndexOfArray = numberOfRect - 1; //current index of the toplogical sort list
  for (int i = 1; i < numberOfRect + 1 ; i++) rectNodeArr[i] -> color = 0;
  for (int i = 1; i < numberOfRect + 1 ; i++){
    if (rectNodeArr[i] -> color == 0) dfs(rectNodeArr[i],rectNodeArr,toplogicalSortList,&curIndexOfArray, mode);
  }
  return toplogicalSortList;
}

void dfs(RectNode * curStartingNode, RectNode ** rectNodeArr, int * toplogicalSortList, int * curIndexOfArray, int mode){
  curStartingNode -> color = 1; //white to gray
  int i = 0;
  if (mode == 1) {
    while(curStartingNode -> verticalAdjList[i] != -1){
      if (rectNodeArr[curStartingNode -> verticalAdjList[i]] -> color == 0) { //if is white
        dfs(rectNodeArr[curStartingNode -> verticalAdjList[i]], rectNodeArr, toplogicalSortList, curIndexOfArray, mode);
      }
      rectNodeArr[curStartingNode -> verticalAdjList[i]] -> color = 2; //should turn black
      i++;
    }
    toplogicalSortList[*curIndexOfArray] = curStartingNode -> label;
    (* curIndexOfArray) --;
  }else{
    while(curStartingNode -> horzontalAdjList[i] != -1){
      if (rectNodeArr[curStartingNode -> horzontalAdjList[i]] -> color == 0) { //if is white
        dfs(rectNodeArr[curStartingNode -> horzontalAdjList[i]], rectNodeArr, toplogicalSortList, curIndexOfArray, mode);
      }
      rectNodeArr[curStartingNode -> horzontalAdjList[i]] -> color = 2; //should turn black
      i++;
    }
    toplogicalSortList[*curIndexOfArray] = curStartingNode -> label;
    (* curIndexOfArray) --;
  }

}

void processAdjList(RectNode ** rectNodeArr, int * seqTwo, int sizeofSeq, int * lut){
  printf("size of seq: %d\n", sizeofSeq);
  for (int i = 0; i < sizeofSeq; i++) {
    rectNodeArr[seqTwo[i]] -> verticalAdjList = malloc(sizeof(int)*sizeofSeq);
    rectNodeArr[seqTwo[i]] -> horzontalAdjList = malloc(sizeof(int)*sizeofSeq);

    rectNodeArr[seqTwo[i]] -> verticalAdjList = initArr(rectNodeArr[seqTwo[i]] -> verticalAdjList, sizeofSeq);
    rectNodeArr[seqTwo[i]] -> horzontalAdjList = initArr(rectNodeArr[seqTwo[i]] -> horzontalAdjList, sizeofSeq);

    int verticalIndex = 0;
    int horizontalIndex = 0;

    int curSeqTwoNum = seqTwo[i]; //8
    int curLUTresult = lut[curSeqTwoNum]; // 7
    printf("------------- %d ------------\n", i);
    for (int j = i+1; j < sizeofSeq; j++) { //start after i
      // printf("lut[seqTwo[%d]] = %d and curLUTresult = %d \n", j, lut[seqTwo[j]], curLUTresult);
      if (lut[seqTwo[j]] < curLUTresult){ //less than is vertical list
        // printf("                                      headVerticalList[%d] = %d\n",verticalIndex, seqTwo[j]);
        rectNodeArr[seqTwo[i]] -> verticalAdjList[verticalIndex] = seqTwo[j];
        verticalIndex ++;
      }else{
        // printf("                                      headHorizontalList[%d] = %d\n",horizontalIndex, seqTwo[j]);
        rectNodeArr[seqTwo[i]] -> horzontalAdjList[horizontalIndex] = seqTwo[j];
        horizontalIndex ++;
      }
    }
    printf("verticalAdjList\n");
    DEBUG_Print_Array(rectNodeArr[seqTwo[i]] -> verticalAdjList, sizeofSeq);
    printf("horzontalAdjList\n");
    DEBUG_Print_Array(rectNodeArr[seqTwo[i]] -> horzontalAdjList, sizeofSeq);
    // printf("seqTwo[%d] = %d\n", i, seqTwo[i]);
  }
}

int * initArr(int * arr, int size){ //intit all arrat index to -1
  for (int i = 0; i < size; i++) {
    arr[i] = -1;
  }
  return arr;
}

void DEBUG_AdjList(RectNode ** rectNodeArr, int size){
  for (int i = 1; i < size + 1; i++) {
    printf("Current Index : %d\n", i);
    printf("width: %le height: %le \n", rectNodeArr[i] -> width, rectNodeArr[i] -> height);
    printf("headVerticalList\n");
    DEBUG_Print_Array(rectNodeArr[i] -> verticalAdjList,size);
    printf("headHorizontalList\n");
    DEBUG_Print_Array(rectNodeArr[i] -> horzontalAdjList,size);
  }
}

void DEBUG_Print_Array(int * Array, int Size){
 for (int i = 0; i < Size; i++) {
   printf("Index: [%s%d%s] Value: <%s%d%s>\n", KRED, i, KRESET, KRED , Array[i] , KRESET);
 }
}

void DEBUG_Print_RectNodeArray(RectNode ** Array, int Size){
 for (int i = 1; i < Size + 1; i++) {
   printf("Index: [%s%d%s] Value: <%s%le, %le%s> Width and Height: %le, %le, Color: %d\n", KRED, i, KRESET, KRED , Array[i] -> x, Array[i] -> y , KRESET, Array[i]->width, Array[i]->height,  Array[i]->color);
 }
}
