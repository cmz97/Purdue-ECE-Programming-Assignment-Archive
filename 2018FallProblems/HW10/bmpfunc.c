#include "bmpfunc.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#ifdef TEST_FUNCGIVEN

int RGB2Gray(unsigned char red, unsigned char green, unsigned char blue){
	// this is a commonly used formula
	int gray = 0.2989 * red + 0.5870 * green + 0.1140 * blue;
	return gray;
}

#endif

//Modify below this line
#ifdef TEST_IMGTOGRAY

BMPImage * ImgToGray(BMPImage * image){
	// allocate space for the image
    BMPImage * gImg = malloc(sizeof(BMPImage));
	// the image has the same size
	// therefore the header has to stay the same
	// check for memory allocation failure 
    if (gImg == NULL) {
        printf("Error while malloc image in ImgToGray");
        return NULL;
    }
	//gray_image can be the name of the new image memory allotment
	//gray_image->header = image->header;
    gImg->header = image->header;
	//Assign the the imagesize as height * width
	
	//check for data allocation failure using :
    gImg->data = malloc(sizeof(unsigned char)*(gImg->header).imagesize);
    if (gImg->data == NULL) {
        printf("Error while malloc image->data in ImgToGray");
        return NULL;
    }
    
  int pixel = 0;
  int gray_val = 0;
	//Run loop for all pixels using height and width
	//convert each pixel of all channels to gray using the given RGB2GRAY function
   for (; pixel<(image->header).imagesize; pixel+=3 ) {
        gray_val = RGB2Gray(image -> data[pixel+2],image -> data[pixel + 1],image -> data[pixel]);
        //assign values to all pixels of gray_image for each channel
        gImg->data[pixel+2] = gray_val;
        gImg->data[pixel+1] = gray_val;
        gImg->data[pixel] = gray_val;
    }
	
		
	//return the result
    return gImg;
}


#endif

