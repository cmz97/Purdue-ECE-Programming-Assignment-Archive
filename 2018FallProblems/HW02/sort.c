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
    int minNum;
    int minIndex;
    int temp;
    
    for(sortedIndex = 0; sortedIndex < size; sortedIndex++){
        currentIndex = sortedIndex ;
        minNum = arr[currentIndex];
        for(currentIndex; currentIndex < size; currentIndex++){
            if(arr[currentIndex] < minNum){
                minNum = arr[currentIndex];
                minIndex = currentIndex;
            }
        }
        temp = arr[sortedIndex];
        arr[sortedIndex] = minNum;
        arr[minIndex] = temp;
    }
    
  if (checkOrder(arr, size) == false)
    {
      fprintf(stderr, "checkOrder returns false\n");
    }
}
#endif
