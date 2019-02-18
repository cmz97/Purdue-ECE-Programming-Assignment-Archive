#include "shell_array.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char *filename, int *size){
  *size = 0;
  FILE * inputFilePtr = fopen(filename,"r");
  long curLong = 0;
  long * numArray = NULL;

  if(inputFilePtr == NULL){
    printf("Input File Does Not Exist\n");
    fclose(inputFilePtr);
    return NULL;
  }

  while(fread(&curLong, sizeof(long), 1, inputFilePtr) == 1) (*size)++;
  fseek(inputFilePtr, 0, SEEK_SET); //now put back the file pointer
  numArray = malloc(sizeof(long)*(*size));

  if (numArray == NULL) {
    printf("Faild to Malloc");
    fclose(inputFilePtr);
    return NULL;
  }

  for(int i = 0 ; i < *size ; i++){
    fread(&curLong, sizeof(long), 1, inputFilePtr);
    numArray[i] = curLong;
    // printf("numArray[%d]:%ld\n",i,curLong);
  }
  fclose(inputFilePtr);
  return numArray;
}

int Array_Save_To_File(char *filename, long *array, int size){
  FILE * outputFilePtr = fopen(filename,"w");
  if(outputFilePtr == NULL){
    printf("Can not create file\n");
    fclose(outputFilePtr);
    return 0;
  }
  fwrite(array,sizeof(long),size,outputFilePtr);
  fclose(outputFilePtr);
  return size;
}

void Array_Shellsort(long *array, int size, double *n_comp){
  int seq_size = 0; //sequence size
  long * sequence = Generate_2p3q_Seq(size,&seq_size);
  int gapLength = 0; //the current sequence
  int x = 0; // inner array index
  long temp_r = 0; //the temperary r for swaping

  for(int i = seq_size - 1; i >= 0 ; i--){
    gapLength = sequence[i];
    for(int j = gapLength ; j < size ; j++){
      temp_r = array[j];
      x = j;
      while (x >= gapLength && array[x-gapLength] > temp_r) {
        (*n_comp)++;
        array[x] = array[x-gapLength];
        x = x - gapLength;
      }
      (*n_comp)++; //to compensate for while loop one more check
      array[x] = temp_r;
    }
  }
  free(sequence);
}
