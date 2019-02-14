#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "shell_array.h"
#include <string.h>

int main(int argc, char ** argv)
{
  // argv[1]: mode -l for list, -a for array
  // argv[2]: inputName
  // argv[3]: outputName

  int sizeofInputArr = 0;
  Node * head = NULL;
  long * inputArr = NULL; //input array reading from file
  double n_comp = 0; //number of comparision

  if (argc != 4) {
    printf("Wrong Argument Count (usage: 3 Argument)\n");
    return EXIT_FAILURE;
  }
  if (strcmp(argv[1],"-a") == 0) {
    inputArr = Array_Load_From_File(argv[2], &sizeofInputArr);
    Array_Shellsort(inputArr, sizeofInputArr, &n_comp);
    Array_Save_To_File(argv[3], inputArr, sizeofInputArr);
    free(inputArr);
    printf("Array Sorting\n");
    return EXIT_SUCCESS;
  }else if (strcmp(argv[1],"-l") == 0) {
    head = List_Load_From_File(argv[2]);
    List_Shellsort(head,&n_comp);
    List_Save_To_File(argv[3],head);
    printf("List Sorting\n");
    //FREE HEAD
    return EXIT_SUCCESS;
  }
  printf("Wrong Argument (usage: -l or -a)\n");
  return EXIT_FAILURE;

}
