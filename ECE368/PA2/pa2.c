#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "shell_array.h"

int main(int argc, char ** argv)
{
  // argv[1]: mode -l for list, -a for array
  // argv[2]: inputName
  // argv[3]: outputName

  int sizeofInputArr = 0;
  long * inputArr = NULL; //input array reading from file
  double n_comp = 0; //number of comparision
  inputArr = Array_Load_From_File(argv[2], &sizeofInputArr);
  Array_Shellsort(inputArr, sizeofInputArr, &n_comp);
  Array_Save_To_File(argv[3], inputArr, sizeofInputArr);
  free(inputArr);

  return EXIT_SUCCESS;
}
