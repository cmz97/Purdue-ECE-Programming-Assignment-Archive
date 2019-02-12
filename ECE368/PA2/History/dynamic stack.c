#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>
#define GROWFACTOR 2

// static long * push(long * stacksize, long * curStackIndex, long * sequenceStack, long value);
// static void printArrayDEBUG(long * sequenceStack, long stacksize);

long *Generate_2p3q_Seq(int n, int *seq_size){
    long stacksize = 1;
    long curStackIndex = 0;
    long * sequenceStack = malloc(sizeof(long) * stacksize);
    if (* sequenceStack == NULL) { //malloc failed
        *seq_size = 0;
        return NULL;
    }
    // long current = 0;
    if (n == 1 || n == 0) { // return 0 and empty stack if n =1 or 0
        *seq_size = 0
        return sequenceStack;
    }
    sequenceStack = push(&stacksize,&curStackIndex,sequenceStack,1); //first initialize the first variable



    for (int i = 0 ; i < 100 ; i++) {
      sequenceStack = push(&stacksize,&curStackIndex,sequenceStack,current+i);
    }
    printArrayDEBUG(sequenceStack,curStackIndex);
    return NULL;
}

static long * push(long * stacksize, long * curStackIndex, long * sequenceStack, long value){
  if (*curStackIndex == *stacksize) { //If the array is full, realloc
    * stacksize = (long)((* stacksize) * GROWFACTOR); //grow the stack size by this factor
    printf("Stack Growed to : %ld \n", (*stacksize));
    sequenceStack = realloc(sequenceStack, sizeof(long)*(*stacksize));
    sequenceStack[*curStackIndex] = value;
    * curStackIndex += 1; //increment the curent Stack Index by one
    return sequenceStack;
  }
  sequenceStack[*curStackIndex] = value;
  * curStackIndex += 1; //increment the curent Stack Index by one
  return sequenceStack;
}

static void printArrayDEBUG(long * sequenceStack, long stacksize){
  for (long i = 0 ; i < stacksize ; i++) {
    printf("sequenceStack[%ld]: %ld\n",i, sequenceStack[i]);
  }
}
