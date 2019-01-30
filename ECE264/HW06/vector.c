//
// MODIFY THIS FILE AS DIRECTED
//
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "vector.h"



#ifdef TEST_COMP
int cmp(const void *a, const void *b) 
{ 
    //typecast the inputs into Vector * form.
        //For example: Vector *typecasted_b = (Vector *)b;
    //compare typecased_a->x and typecasted_b->x, and return appropriate values.
    Vector *typecasted_a = (Vector *)a;
    Vector *typecasted_b =(Vector *)b;
    if (typecasted_b->x - typecasted_a->x > 0) {
        return -1;
    }
    
    if (typecasted_b->x - typecasted_a->x == 0) {
        return 0;
    }
    return 1;

} 
#endif

#ifdef TEST_COUNT
int numberOfElements(char* in_file_name)
{
    //initialize file_pointer, and open file in read mode.
    FILE * fp;
    fp = fopen(in_file_name,"r");
        //Please note that we are working with binary files. 
    
    //use fseek(file_pointer, 0, SEEK_END); to point to the end of the file.
    fseek(fp, 0, SEEK_END);
    long where = ftell(fp);
    //use long where = ftell(file_pointer); to get the size of the file.
    float numelem = where / sizeof(Vector);
    //use float numelem = where / sizeof(Vector); to obtain the number of elements
    fclose(fp);
    //printf("Number of ELEMENT:%f\n\n",numelem);
    return numelem;
    //return numelem; to send the number of elements back to main().
}
#endif

#ifdef TEST_FILL
void fillVector(Vector* vector, int count, char * in_file_name)
{
    // open binary file to read after initializing file_pointer 
    FILE * fp;
    fp = fopen(in_file_name,"r");
    fread(vector, sizeof(Vector), count, fp);
    //    for (int i=0; i<count; i++) {
    //        printf("PreVector_%d ( %d, %d, %d)\n",i,vector[i].x,vector[i].y,vector[i].z);
    //    }
    //How to read the file?
        //use fread(vector, sizeof(Vector), count, file_pointer)
    fclose(fp);
}
#endif

#ifdef TEST_WRITE
void writeFile(Vector* vector, int count, char* out_file_name)
{
    // open binary file to write after initializing file_pointer
    FILE * fp;
    fp = fopen(out_file_name,"w");
    //    for (int i=0; i<count; i++) {
    //        printf("AftVector_%d ( %d, %d, %d)\n",i,vector[i].x,vector[i].y,vector[i].z);
    //    }
    //How to write to the file?
        //use fwrite(vector, sizeof(Vector), count, file_pointer)
    fwrite(vector, sizeof(Vector), count, fp);
    fclose(fp);
}
#endif
