#include "hw11.h"
//Modify this file
#ifdef TEST_MAIN

int main(int argc, char **argv){
  // check the arguments - please read readme about validity of arguments
    if (argc!=5) {
        printf("Argument Error\n");
        return EXIT_FAILURE;
    }
  // check radius and epsilon values -  read readme for the validity of argument
    if (strtol(argv[3],NULL,10) < 0) {
        printf("ERROR: Radius needs to larger than or equal to 0");
        return EXIT_FAILURE;
    }
    int radius = strtol(argv[3],NULL,10);
    
    if (strtol(argv[4],NULL,10) < 0) {
        printf("ERROR: Epsilon needs to larger than or equal to 0");
        return EXIT_FAILURE;
    }
    
    int epsilon = strtol(argv[4],NULL,10);
  // open the BMP file
    BMPImage * img = BMP_Open(argv[1]);
    if (img == NULL) {
        printf("ERROR: Fail to open BMP file\n");
        return EXIT_FAILURE;
    }
  // convert to gray scale
	// check for error in converting to gray scale
    BMPImage * gray = ImgToGray(img);
    if (gray == NULL) {
        printf("ERROR: Fail to convert to gray\n");
        return EXIT_FAILURE;
    }
  // call adaptive threshold function
    BMPImage * threshold = AdaptiveThresholding(gray,radius,epsilon);
    if (threshold == NULL) {
        printf("ERROR: Fail to convert to thresholding\n");
        return EXIT_FAILURE;
    }
    
    BMP_Free(img);
    BMP_Free(gray);
    BMP_Free(threshold);
  // check for errors after calling adaptive threshold
	// write the adaptive threshold image to file
	// free all the images
	return EXIT_SUCCESS;
}

#endif
