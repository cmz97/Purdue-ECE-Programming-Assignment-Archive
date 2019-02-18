#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>
#define GROWFACTOR 2

static long * push(long * stacksize, int * curStackIndex, long * sequenceStack, long value);
// static void printArrayDEBUG(long * sequenceStack, long stacksize);
static long getMin(long num1, long num2);

long *Generate_2p3q_Seq(int n, int *seq_size){
    long stacksize = 1;
    int curStackIndex = 0;
    int index_2 = 0;  //storing the 2 index
    int index_3 = 0; //storing the 3 index
    long current_2 = 0;
    long current_3 = 0;
    long currentNumber = 0;

    long * sequenceStack = malloc(sizeof(long) * stacksize);
    if (sequenceStack == NULL) { //malloc failed
        *seq_size = 0;
        return NULL;
    }
    // long current = 0;
    if (n == 1 || n == 0) { // return 0 and empty stack if n =1 or 0
        *seq_size = 0;
        return sequenceStack;
    }
    sequenceStack = push(&stacksize,&curStackIndex,sequenceStack,1); //first initialize the first variable
    while(1){
        current_2 = 2 * sequenceStack[index_2];
        current_3 = 3 * sequenceStack[index_3];
        currentNumber = getMin(current_2, current_3);
        if (currentNumber >= n) break;
        sequenceStack = push(&stacksize,&curStackIndex,sequenceStack,currentNumber);
        if (current_2 <= current_3) index_2++;
        if (current_2 >= current_3) index_3++;
    }
    *seq_size = curStackIndex;
    return sequenceStack;
}

static long getMin(long num1, long num2){
  if (num1 > num2) return num2;
  return num1;
}

static long * push(long * stacksize, int * curStackIndex, long * sequenceStack, long value){
  if (*curStackIndex == *stacksize) { //If the array is full, realloc
    * stacksize = (long)((* stacksize) * GROWFACTOR); //grow the stack size by this factor
    // printf("Stack Growed to : %ld \n", (*stacksize));
    sequenceStack = realloc(sequenceStack, sizeof(long)*(*stacksize));
    sequenceStack[*curStackIndex] = value;
    * curStackIndex += 1; //increment the curent Stack Index by one
    return sequenceStack;
  }
  sequenceStack[*curStackIndex] = value;
  * curStackIndex += 1; //increment the curent Stack Index by one
  return sequenceStack;
}

// static void printArrayDEBUG(long * sequenceStack, long stacksize){
//   for (int i = 0 ; i < stacksize ; i++) {
//     printf("sequenceStack[%d]: %ld\n",i, sequenceStack[i]);
//   }
// }
