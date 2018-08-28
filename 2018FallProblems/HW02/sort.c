// ***
// *** You MUST modify this file, only the ssort function
// ***

#include "sort.h"
#include <stdio.h>
#include <stdbool.h>

static bool checkOrder(int * arr, int size)
// a static function is visible only in this file
// This function returns true if the array elements are
// in the ascending order.
// false, otherwise
{
  int ind;
  for (ind = 0; ind < (size - 1); ind ++)
    {
      if (arr[ind] > arr[ind + 1])
	{
	  return false;
	}
    }
  return true;
}

#ifdef TEST_SORT
void ssort(int * arr, int size)
{
    int currentIndex;
    int sortedIndex;
    int minNum = 0;
    int minIndex = 0;
    int temp = 0;
    int found = 0;
    
    for(sortedIndex = 0; sortedIndex < size - 1 ; sortedIndex++){
        minNum = arr[sortedIndex];
        for(currentIndex = sortedIndex; currentIndex < size; currentIndex++){
            if(arr[currentIndex] < minNum){
                minNum = arr[currentIndex];
                minIndex = currentIndex;
                found = 1;
            }
        }
        if(found){
            temp = arr[sortedIndex];
            arr[sortedIndex] = minNum;
            arr[minIndex] = temp;
        }
        found = 0;
        
        
        
        /*printf("sortedIndex at: %d\n", sortedIndex); //to be deleted
        for(int i=0;i<size;i++){ //to be deleted
            printf("arr[%d] =  %d\n", i, arr[i]); //to be deleted
        } //to be deleted
        */
        
    }
    
  if (checkOrder(arr, size) == false)
    {
      fprintf(stderr, "checkOrder returns false\n");
    }
}
#endif
