#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define KRED  "\x1B[31m"
#define KRESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define SMALLSIZE 0

static void DEBUG_Print_Array(long * Array, int Size);
static void qsort_tr(long * Array, int lb, int ub);
static int partition(long * Array, int lb, int ub);
// static void insertion_sort(long * Array, int lb, int ub);
static void merge(long * Array, int lb, int mid, int ub, long * temp);
static void msort(long * Array, int lb, int ub, long * temp);
int pseudo_random_index(int lb, int ub);

static long rng = 5374;

void Quick_Sort(long * Array, int Size){
  DEBUG_Print_Array(Array,Size);
  qsort_tr(Array,0,Size-1);
  // insertion_sort(Array,0,Size-1);
  printf("Now Sorted\n");
  DEBUG_Print_Array(Array,Size);
}

// static void insertion_sort(long * Array, int lb, int ub){
//   //Insertion Sort: Using Sentinel
//   return;
//   long temp = 0;
//   int i = 0;
//   for (int j = ub; j >= 1; j--) {
//     if (Array[j] < Array[j - 1]){
//       temp = Array[j];
//       Array[j] = Array[j - 1];
//       Array[j - 1] = temp;
//     }
//   }
//   for (int j = 2; j < ub; j++) {
//       temp = Array[j];
//       i = j;
//       while (Array[i - 1] > temp) {
//         Array[i] = Array[i-1];
//         i = i - 1;
//       }
//       Array[i] = temp;
//   }
// }

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
  int pivot_idx = lb; //pseudo_random_index(lb,ub);
  long pivot = Array[pivot_idx];
  int down = lb;
  int up = ub;
  long temp = 0;
  while (down < up) {
    // printf("down: %d up: %d\n", down, up);
    while (Array[down] <= pivot && down < ub) {
      down ++;
    }
    while (Array[up] > pivot) {
      up --;
    }
    if (down < up) {
      temp = Array[down];
      Array[down] = Array[up];
      Array[up] = temp;
    }
  }
  Array[lb] = Array[up];
  Array[up] = pivot;
  return up;
}

int pseudo_random_index(int lb, int ub){
  long m = 7777777;
  long a = 8473988;
  long c = 3265398;

  rng = ( a * rng + c ) % m;
  return (int)((rng / (double) m)*(ub - lb + 1));
}

void Merge_sort(long * Array, int Size){
  DEBUG_Print_Array(Array,Size);
  printf("Now Sorted\n");

  msort(Array, 0, Size - 1, NULL);
  DEBUG_Print_Array(Array,Size);
}

static void msort(long * Array, int lb, int ub, long * temp){
  if (lb >= ub) return;
  temp = malloc(sizeof(long)*(ub - lb + 1));
  int mid = (lb + ub)/2;
  msort(Array,lb,mid,temp);
  msort(Array,mid+1,ub,temp);
  merge(Array,lb,mid,ub,temp);
}

static void merge(long * Array, int lb, int mid, int ub, long * temp){
	int i = lb;
  int j = mid+1;
  int k = 0;

	while(i <= mid && j <= ub) {
		if(Array[i] <= Array[j]) {
			temp[k] = Array[i];
			k ++;
      i ++;
		}else {
			temp[k] = Array[j];
			k ++;
      j ++;
		}
	}

	while(i <= mid) {
		temp[k] = Array[i];
		k ++;
    i ++;
	}

	while(j <= ub) {
		temp[k] = Array[j];
		k ++;
    j ++;
	}

	for(i = lb; i <= ub; i += 1) {
		Array[i] = temp[i - lb];
	}

}

static void DEBUG_Print_Array(long * Array, int Size){
  for (int i = 0; i < Size; i++) {
    printf("Index: [%s%d%s] Value: <%s%ld%s>\n", KRED, i, KRESET, KRED , Array[i] , KRESET);
  }
}
