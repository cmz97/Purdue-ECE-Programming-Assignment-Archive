#include "seqpair.h"

RectNode ** Load_Into_Array(int * numberOfRect, char * inputfileName, int ** seqOne, int ** seqTwo);
void freeRectNode(RectNode ** rectNodeArr, int size);
void printRectArr2File(RectNode ** rectNodeArr, char * outputfileName, int sizeofSeq);
int main(int argc, char ** argv){
  // argv[1]: inputName
  // argv[2]: outputName
  RectNode ** rectNodeArr = NULL; //input array reading from file

  if (argc != 3) {
    printf("Wrong Argument Count (usage: 2 Argument)\n");
    return EXIT_FAILURE;
  }
  int numberOfRect = 0;
  int * seqOne = NULL;
  int * seqTwo = NULL;
  int * toplogicalSortListVertical = NULL;
  int * toplogicalSortListHorizontal = NULL;

  rectNodeArr = Load_Into_Array(&numberOfRect, argv[1], &seqOne, &seqTwo);
  DEBUG_Print_RectNodeArray(rectNodeArr, numberOfRect);
  if (rectNodeArr == NULL) return EXIT_FAILURE;

  printf("SeqOne\n");
  DEBUG_Print_Array(seqOne, numberOfRect);
  printf("SeqTwo\n");
  DEBUG_Print_Array(seqTwo, numberOfRect);

  int * lut = generateLUT(seqOne,numberOfRect);

  printf("LUT\n");
  DEBUG_Print_Array(lut, numberOfRect + 1);
  processAdjList(rectNodeArr, seqTwo, numberOfRect, lut);

  toplogicalSortListVertical = malloc(sizeof(int)*numberOfRect);
  toplogicalSortListHorizontal = malloc(sizeof(int)*numberOfRect);

  toplogicalSortListHorizontal = toplogicalSort(rectNodeArr,toplogicalSortListHorizontal, numberOfRect, 0); //tryVertical First
  toplogicalSortListVertical = toplogicalSort(rectNodeArr,toplogicalSortListVertical, numberOfRect, 1); //tryVertical First

  printf("Horizontal Toposort:\n");
  DEBUG_Print_Array(toplogicalSortListHorizontal, numberOfRect);
  printf("Vertical Toposort:\n");
  DEBUG_Print_Array(toplogicalSortListVertical, numberOfRect);

  updateCoordinates(rectNodeArr,toplogicalSortListHorizontal,numberOfRect,0);
  updateCoordinates(rectNodeArr,toplogicalSortListHorizontal,numberOfRect,1);

  DEBUG_Print_RectNodeArray(rectNodeArr,numberOfRect);
  // DEBUG_AdjList(rectNodeArr,numberOfRect);

  printRectArr2File(rectNodeArr, argv[2], numberOfRect);

  free(seqOne);
  free(seqTwo);
  free(toplogicalSortListHorizontal);
  free(toplogicalSortListVertical);
  free(lut);
  freeRectNode(rectNodeArr, numberOfRect);
  free(rectNodeArr);
  return EXIT_SUCCESS;

}

void freeRectNode(RectNode ** rectNodeArr, int size){
  for (int i = 1; i < size + 1; i++) {
    free(rectNodeArr[i] -> verticalAdjList);
    free(rectNodeArr[i] -> horzontalAdjList);
    free(rectNodeArr[i]);
  }
}

void printRectArr2File(RectNode ** rectNodeArr, char * outputfileName, int sizeofSeq){
  FILE * outputFilePtr = fopen(outputfileName,"w");

  if(outputFilePtr == NULL){
    printf("Output File Failed to create\n");
    fclose(outputFilePtr);
  }

  for (int i = 1; i < sizeofSeq + 1; i++) {
    fprintf(outputFilePtr, "%d(%le,%le)\n",i,rectNodeArr[i]->x,rectNodeArr[i]->y);
  }

  fclose(outputFilePtr);
}

RectNode ** Load_Into_Array(int * numberOfRect, char * inputfileName, int ** seqOne, int ** seqTwo){
  FILE * inputFilePtr = fopen(inputfileName,"r");
  int curIndex = 0;
  double width = 0;
  double height = 0;
  char * seqStr = NULL;

  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist\n");
    fclose(inputFilePtr);
    return NULL;
  }
  fscanf(inputFilePtr, "%d\n", numberOfRect);

  RectNode ** rectNodeArr = malloc(sizeof(RectNode *)*((*numberOfRect) + 1)); //puls one to offset the array by one
  rectNodeArr[0] = NULL; //set the index zero to null so that i dont make mistake

  *seqOne = malloc(sizeof(int)*(*numberOfRect));
  *seqTwo = malloc(sizeof(int)*(*numberOfRect));


  for (int i = 1; i < *numberOfRect + 1; i++) {
    fscanf(inputFilePtr, "%d(%le,%le)\n", &curIndex, &width, &height);
    rectNodeArr[curIndex] = malloc(sizeof(RectNode));
    rectNodeArr[curIndex] -> width = width;
    rectNodeArr[curIndex] -> height = height;
    rectNodeArr[curIndex] -> label = curIndex;

    rectNodeArr[curIndex] -> verticalAdjList = NULL;
    rectNodeArr[curIndex] -> horzontalAdjList = NULL;

    rectNodeArr[curIndex] -> x = 0;
    rectNodeArr[curIndex] -> y = 0;

    rectNodeArr[curIndex] -> color = 0;
  }

  int sizeofSeq = 2 * (*numberOfRect) - 1;
  printf("size of seq: %d\n", sizeofSeq);
  // seqStr = malloc((sizeofSeq - 1)*sizeof(char));

  for (int i = 0; i < *numberOfRect; i++) {
    fscanf(inputFilePtr,"%d", &((*seqOne)[i]));
  }

  for (int i = 0; i < *numberOfRect; i++) {
    fscanf(inputFilePtr,"%d", &((*seqTwo)[i]));
  }

  free(seqStr);
  fclose(inputFilePtr);

  return rectNodeArr;
}
