// ***
// *** You MUST modify this file
// ***

#include "josephus.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef TEST_JOSEPHUS
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails,
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
  // initialize all elements
    for(int j=0; j<n; j++){
        arr[j] = -1;
    }
  // counting to k,

    int counter = 1;
    int done = 0;
    int numPlacement = 0;
    int arrayIndex = 0;
   
    while(!done){
        if(arrayIndex == n){
            arrayIndex = 0;
        }
        if(counter == k + 1){
            counter = 1;
        }
        if(numPlacement == n){
            done = 1;
        }else{
            if(counter == k){
                if(arr[arrayIndex] != 0){
                    printf("%d\n",arrayIndex);
                    arr[arrayIndex] = 0;
                    numPlacement ++;
                    counter++;
                }
            }else{
                if(arr[arrayIndex] != 0){
                    arr[arrayIndex] = counter;
                    counter++;
                }
            }
            arrayIndex++;
            
        }
    
    }
   
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked




  // print the last one




  // release the memory of the array
  free (arr);
}
#endif
