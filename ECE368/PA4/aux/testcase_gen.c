#include <stdio.h>
#include <stdlib.h>
int main (int argc, char** argv){
    FILE* fptr = fopen(argv[1], "r");
    FILE* fptr2 = fopen(argv[2], "wb");
    int key;
    char operation;
    while (fscanf(fptr, "%d %c\n", &key, &operation) == 2){
        fwrite(&key, sizeof(int), 1, fptr2);
        fwrite(&operation, sizeof(char), 1, fptr2);
    }
    fclose(fptr);
    fclose(fptr2);
    return EXIT_SUCCESS;
}