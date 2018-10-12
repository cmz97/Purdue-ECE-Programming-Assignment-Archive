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

//Modify below this line and use code from HW10 for IMGTOGRAY()

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

#endif

//Write your own code for Adaptive Thresholding Function
#ifdef TEST_ADAPTIVETHRESHOLDING

BMPImage * AdaptiveThresholding(BMPImage * grayImage, int radius, int epsilon){
 	// allocate space for the image
	// the image has the same size(height and width)
	// therefore the header has to stay the same
    BMPImage * adaptive = malloc(sizeof(BMPImage));
    if (adaptive == NULL) {
        printf("Error while malloc image in AdaptiveThresholding");
        free(adaptive);
        return NULL;
    }
    adaptive->header = grayImage->header;
    
	// (gray_image->header).imagesize = (gray_image->header).width*(gray_image->header).height;
	if ((adaptive->data = malloc(sizeof(unsigned char)*(adaptive->header).imagesize)) == NULL) {
		fprintf(stderr, "Error allocating memory\n");
		free(adaptive);
		return NULL;
	}

	int pixel=0;
	//Run a nested loop for all elements using height and width
        //Find the maximum of top row, bottom rpw, left column and right column using radius
    for (int row = 0; row<(adaptive->header).height; row++) {
        for (int col=0; col<(adaptive->header).width; col++) {
            int toprow = MAX(0, row-radius);
            int bottomrow = MIN(height-1, row+radius);
            int leftcol = MAX(0, col-radius);
            int rightcol = MIN(width-1, col+radius);
            
            int sum = 0;
            for (int i=toprow; i<bottomrow; i++) {
                for (int j=leftcol; j<rightcol; j++) {
                    sum += grayImage->data[(i*(adaptive->header).width + j)*3];
                }
            }
            int avg = sum / ((bottomrow - toprow)*(rightcol - leftcol));
            if (avg - epsilon > grayImage->data[(row*(adaptive->header).width + col)*3]) {
                adaptive->data[(row*(adaptive->header).width + col)] = 255;
                adaptive->data[(row*(adaptive->header).width + col)+1] = 255;
                adaptive->data[(row*(adaptive->header).width + col)+2] = 255;
            }else{
                adaptive->data[(row*(adaptive->header).width + col)] = 255;
                adaptive->data[(row*(adaptive->header).width + col)+1] = 255;
                adaptive->data[(row*(adaptive->header).width + col)+2] = 255;
            }
        }
    }
    
    return adaptive;
	/*int toprow = MAX(0, row-radius);
     	 int bottomrow = MIN(height-1, row+radius);
     	 int leftcol = MAX(0, col-radius);
     	 int rightcol = MIN(width-1, col+radius);*/
    	//Calculate the avergage of all pixels
	//Run loop from toprow to bottom row
	//Inside which run a loop from left column to right column
		//calculate the location of each pixel using (row2*width + col2)*3;
         	//add all data values at every location point in data
		//keep a counter for averaging
	//Outside the second nested loop: 
	//calculate averge (using int)
	//check if average-epsilon is greater than grayImage->data[at that pixel point]
	//then assign adaptive thresholding image data as 0(black) for data value at pixel, pixel+1, pixel+2
     
        // else if average is lower then color shall be white(255) for data value at pixel, pixel+1, pixel+
//return the image after adaptive thresholding
}


#endif
