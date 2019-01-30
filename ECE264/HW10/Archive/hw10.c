#include "hw10.h"
//modify the main() function
#ifdef TEST_MAINFUNC

int main(int argc, char **argv){
  // check the arguments
    if (argc!=3) {
        return EXIT_FAILURE;
    }
  // open the BMP file
    BMPImage * img = BMP_Open(argv[1]);
    if (img == NULL) {
        return EXIT_FAILURE;
    }
  // convert to gray scale
	// check for error in converting to gray scale
    BMPImage * gray = ImgToGray(img);
    if (gray == NULL) {
        return EXIT_FAILURE;
    }
	// write the gray image to file
    if(BMP_Write(argv[2],gray)!=TRUE){
        return EXIT_FAILURE;
    }
	// free all the images
    BMP_Free(img);
    BMP_Free(gray);
	return EXIT_SUCCESS;
}

#endif
