#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define KRED  "\x1B[31m"
#define KRESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define SMALLSIZE 9

static void qsort_tr(long * Array, int lb, int ub);
static int partition(long * Array, int lb, int ub);
static void merge(long * Array, int lb, int mid, int ub, long * temp);
static void msort(long * Array, int lb, int ub, long * temp);
void insertion_sort(long * Array, int ub, int lengthArr);

void Quick_Sort(long * Array, int Size){
  qsort_tr(Array,0,Size-1);
  insertion_sort(Array, Size - 1, 1);
}

void insertion_sort(long * Array, int ub, int lengthArr) {
    int j = 0;
    long tmp  = 0;
    for (int i = lengthArr; i < ub + 1; i ++) {
        tmp = Array[i];
        j = i;
        while (Array[j - lengthArr] > tmp && j >= lengthArr) {
            Array[j] = Array[j - lengthArr];
            j -= lengthArr;
        }
        Array[j] = tmp;
    }
}

static void qsort_tr(long * Array, int lb, int ub){
  int pivot_idx = 0;
  while (ub - lb > SMALLSIZE) {
    pivot_idx = partition(Array, lb, ub);
    if (pivot_idx < (lb + ub) / 2) { // tail recursion removed
      qsort_tr(Array, lb, pivot_idx - 1);
      lb = pivot_idx + 1;
    }else{
      qsort_tr(Array, pivot_idx + 1, ub);
      ub = pivot_idx - 1;
    }
  }
}


static int partition(long * Array, int lb, int ub){
  //before traversal and find the partition, we need to find the midian of the array by sampling three point
  long probeOne = Array[lb];
  long probeThree = Array[ub];
  long probeTwo = Array[(ub + lb) / 2];
  Array[(ub + lb) / 2] = Array[lb + 1]; // exchange the mid point and the 2 item
  if (probeOne > probeTwo) {       // used professor koh's method of findind the median by sampling three point
    if (probeOne > probeThree) {
      if (probeTwo <= probeThree) {
          Array[lb] = probeThree; //mean
          Array[lb + 1] = probeTwo;
          Array[ub] = probeOne;
      } else {
          Array[lb] = probeTwo; //mean
          Array[lb + 1] = probeThree;
          Array[ub] = probeOne;
      }
    } else Array[lb + 1] = probeTwo; //mean in place
  } else {
    if (probeTwo > probeThree) {
        if (probeOne <= probeThree) {
            Array[lb] = probeThree; //mean
            Array[lb + 1] = probeOne;
            Array[ub] = probeTwo;
        } else { //mean in place
            Array[lb + 1] = probeThree;
            Array[ub] = probeTwo;
        }
    } else {
      Array[lb] = probeTwo; //mean
      Array[lb + 1] = probeOne;
    }
  }

  long pivot = Array[lb];
  long temp;
  int down = lb;
  int up = ub;
  while (true) {
      while (Array[down] < pivot) down++;
      while (Array[up] > pivot) up--;
      if (down >= up) return up;
      //exchange elements
      temp = Array[down];
      Array[down] = Array[up];
      Array[up] = temp;
  }
}

void Merge_Sort(long * Array, int Size){
  msort(Array, 0, Size - 1, NULL);
}

static void msort(long * Array, int lb, int ub, long * temp){
  if (lb >= ub) return;
  temp = malloc(sizeof(long)*(ub - lb + 1));
  memcpy(temp, Array, sizeof(long) * (ub - lb + 1));
  int mid = (lb + ub)/2;
  msort(Array,lb,mid,temp);
  msort(Array,mid+1,ub,temp);
  merge(Array,lb,mid,ub,temp);
  free(temp);
}

static void merge(long * Array, int lb, int mid, int ub, long * temp){

	int i = lb;
  int j = mid + 1;
  int k = 0;
  int size = ub + 1;

	for (; i <= mid && j <= ub; k++) {
		if(Array[i] > Array[j]) {
      temp[k] = Array[j];
      j ++;
		}else if (Array[i] <= Array[j]) {
      temp[k] = Array[i];
      i ++;
    }
	}

	for (; i <= mid; i++) {temp[k] = Array[i]; k ++;}
	for (; j <= ub; j++) {temp[k] = Array[j]; k ++;}
	for(i = lb; i < size; i ++) Array[i] = temp[i - lb];

}

void DEBUG_Print_Array(long * Array, int Size){
 for (int i = 0; i < Size; i++) {
   printf("Index: [%s%d%s] Value: <%s%ld%s>\n", KRED, i, KRESET, KRED , Array[i] , KRESET);
 }
}
