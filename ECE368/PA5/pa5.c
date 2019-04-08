#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

long * Load_Into_Array(char * Filename, int * Size);
int Save_From_Array(char * Filename, long * Array, int Size);

int main(int argc, char ** argv)
{
  // argv[1]: mode -q for quicksort, -m for mergesort
  // argv[2]: inputName
  // argv[3]: outputName
  long * inputArr = NULL; //input array reading from file
  int sizeofInputArr = 0;

  if (argc != 4) {
    printf("Wrong Argument Count (usage: 3 Argument)\n");
    return EXIT_FAILURE;
  }

  inputArr = Load_Into_Array(argv[2],&sizeofInputArr);
  if (inputArr == NULL) return EXIT_FAILURE;
  if (strcmp(argv[1],"-q") == 0) {
    Quick_Sort(inputArr,sizeofInputArr);
    Save_From_Array(argv[3],inputArr,sizeofInputArr);   
    free(inputArr);
    return EXIT_SUCCESS;
  }else if (strcmp(argv[1],"-m") == 0) {
    Merge_sort(inputArr,sizeofInputArr);
    Save_From_Array(argv[3],inputArr,sizeofInputArr);   
    free(inputArr);
    return EXIT_SUCCESS;
  }
  printf("Wrong Argument (usage: -l or -a)\n");
  return EXIT_FAILURE;

}

long * Load_Into_Array(char * Filename, int * Size){
  *Size = 0;
  FILE * inputFilePtr = fopen(Filename,"r");
  long curLong = 0;
  long * numArray = NULL;

  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist\n");
    //fclose(inputFilePtr);
    return NULL;
  }

  while(fread(&curLong, sizeof(long), 1, inputFilePtr) == 1) (*Size)++;
  fseek(inputFilePtr, 0, SEEK_SET); //now put back the file pointer
  numArray = malloc(sizeof(long)*(*Size));

  if (numArray == NULL) {
    printf("Faild to Malloc");
    fclose(inputFilePtr);
    return NULL;
  }

  for(int i = 0 ; i < *Size ; i++){
    fread(&curLong, sizeof(long), 1, inputFilePtr);
    numArray[i] = curLong;
  }
  fclose(inputFilePtr);
  return numArray;
}

int Save_From_Array(char * Filename, long * Array, int Size){
  long trueSize = 0;
  FILE * outputFilePtr = fopen(Filename,"w");
  if(outputFilePtr == NULL){
    printf("Can not create file\n");
    fclose(outputFilePtr);
    return 0;
  }
  if (Size == 0) return 0; //create empty file for zero byte array
  trueSize = fwrite(Array,sizeof(long),Size,outputFilePtr);
  fclose(outputFilePtr);

  return trueSize;
}
