#include "seqpair.h"


int * generateLUT(int * seqOne, int sizeofSeq){
  int * lut = malloc(sizeof(int)*(sizeofSeq + 1)); //account for the offsett to plus one
  for (int i = 0; i < sizeofSeq; i++) {
    lut[seqOne[i]] = i;
  }
  return lut;
}

void processAdjList(RectNode *** rectNodeArr, int * seqTwo, int sizeofSeq, int * lut){
  for (int i = 0; i < sizeofSeq; i++) {
    (*rectNodeArr)[seqTwo[i]] -> verticalAdjList = malloc(sizeofSeq);
    (*rectNodeArr)[seqTwo[i]] -> horzontalAdjList = malloc(sizeofSeq);

    (*rectNodeArr)[seqTwo[i]] -> verticalAdjList = initArr((*rectNodeArr)[seqTwo[i]] -> verticalAdjList, sizeofSeq);
    (*rectNodeArr)[seqTwo[i]] -> horzontalAdjList = initArr((*rectNodeArr)[seqTwo[i]] -> horzontalAdjList, sizeofSeq);

    int verticalIndex = 0;
    int horizontalIndex = 0;

    int curSeqTwoNum = seqTwo[i]; //8
    int curLUTresult = lut[curSeqTwoNum]; // 7

    for (int j = i+1; j < sizeofSeq; j++) { //start after i
      printf("lut[seqTwo[%d]] = %d and curLUTresult = %d \n", j, lut[seqTwo[j]], curLUTresult);
      if (lut[seqTwo[j]] < curLUTresult){ //less than is vertical list
        printf("                                      headVerticalList[%d] = %d\n",verticalIndex, seqTwo[j]);
        ((*rectNodeArr)[seqTwo[i]] -> verticalAdjList)[verticalIndex] = seqTwo[j];
        verticalIndex ++;
      }else{
        printf("                                      headHorizontalList[%d] = %d\n",horizontalIndex, seqTwo[j]);
        ((*rectNodeArr)[seqTwo[i]] -> horzontalAdjList)[horizontalIndex] = seqTwo[j];
        horizontalIndex ++;
      }
    }
    printf("seqTwo[%d] = %d\n", i, seqTwo[i]);
  }
}

int * initArr(int * arr, int size){ //intit all arrat index to -1
  for (int i = 0; i < size; i++) {
    arr[i] = -1;
  }
  return arr;
}
