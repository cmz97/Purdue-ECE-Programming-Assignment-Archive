// ***
// *** Please modify this file, as indicated
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "sort.h"


void printArray(int * arr, int size)
{
  int ind;
  for (ind = 0; ind < size; ind ++)
    {
      fprintf(stdout, "%d\n", arr[ind]);
    }
}



//============================ONLY EDIT BELOW THIS COMMENT============================//
#ifdef TEST_COMP
int comparator(const void *a, const void *b) 
{ 
    //type cast both the parameters to the type const int*) a: 
	//FOR EXAMPLE: const int* ia = (const int *) a;
    const int* ia = (const int *) a;
    const int* ib = (const int *) b;
    
    	//if parameter2 > parameter1; return -1
    if (*ib - *ia > 0) {
        return -1;
    }
	//if parameter2 == parameter1; return 0
    if (*ib - *ia == 0) {
        return 0;
    }
	//if parameter2 < parameter1; return 1
    if (*ib -  *ia < 0) {
        return 1;
    }
    
    return 0; //potential error
} 
#endif


#ifdef TEST_COUNT
int countFromFile(char* file_name)
{
  // open file to read
    FILE *fp;
    fp = fopen(file_name,"r"); //read
    int count = 0;
    
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
    
    while(!feof(fp)){
        int c = fgetc(fp);
        if(c == '\n')count++;
    }
  // count the number of integers using a loop
  // at the end of the loop close file_pointer
    fclose(fp);
    return count;
}
#endif

#ifdef TEST_FILL
void fillArray(int* arr, int count, char* file_name)
{
  // open file to read
  //How to read the file?
    FILE *fp;
    fp = fopen(file_name,"r"); //read
	// run a loop, from index = 0 to "count", and use: fscanf(file_pointer, "%d", &arr[index]);
    for (int i=0; i<count; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
	// at the end of the loop close file_pointer
}
#endif

#ifdef TEST_MAIN
int main(int argc, char * * argv)
{
  // input file will be specified from the terminal - test files are made available in inputs folder
    
  // check for missing input file, if so, "return EXIT_FAILURE;"
    if (argc != 2)
    {
        fprintf(stderr, "need the name of input file\n");
        return EXIT_FAILURE;
    }
  // use argv[1] to save the file name, you will use this file name to call the countFromFile(), and fillArray() functions
      //FOR EXAMPLE: char* file_name = argv[1];
    
    char* file_name = argv[1];
    // file open fill return false too:
    FILE *fp;
    fp = fopen(file_name,"r"); //read
    if (fp == NULL) {
        printf("error while attemp to open file");
        return EXIT_FAILURE;
    }
    
  // call the countFromFile(file_name); and store the number of elements in the file.
    int numOfLine = countFromFile(file_name);
  // allocate memory to store the numbers (initialize an array)
    int * arr = malloc(sizeof(int) * numOfLine);
  // check for malloc fail, if so, "return EXIT_FAILURE;"
    if (arr == NULL) // malloc fail
    {
        fprintf(stderr, "malloc fail\n");
        //fclose (file_name);
        return EXIT_FAILURE;
    }
    
  // call the fillArray(arr, count, file_name); and store the values from the file in the array.
    fillArray(arr, numOfLine, file_name);
  // Use qsort() function, after defining the comparator() function - "qsort (arr, count, sizeof(int), comparator);"
    qsort(arr,numOfLine,sizeof(int),comparator);
  // call the printArray() function provided to you.
    printArray(arr,numOfLine);
     
    free(arr);
  return EXIT_SUCCESS;
}
#endif

