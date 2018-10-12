#include "bmpimage.h"
// Modifyall functions in this file
/* check whether a header is valid or not
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

#ifdef TEST_HEADERVALID

int Is_BMPHeader_Valid(BMPHeader* header, FILE *fptr) {
    // Make sure this is a BMP file
    //Check for header->type
    if ((header->type) != 0X4D42) {
        printf("ERROR: This is not the correct file type\n");
        return 0;
    }
    
    // check the offset(header->offset)from beginning of file to image data
    // which is essentially the size of the BMP header
    // known as BMP_HEADER_SIZE for this exercise/assignment
    if (header->offset != BMP_HEADER_SIZE) {
        printf("ERROR: The header does not have the correct size\n");
        return 0;
    }
    
    // check for DIB header size == DIB_HEADER_SIZE
    // For this exercise/assignment
    // use header->DIB_header_size
    if (header->DIB_header_size != DIB_HEADER_SIZE) {
        printf("ERROR: The header does not have DIB header size\n");
        return 0;
    }
    
    // Make sure there is only one image plane
    //use header->planes
    
    if (header->planes != 1) {
        printf("ERROR: The header does not have one image plane\n");
        return 0;
    }
    
    // Make sure there is no compression
    
    if (header -> compression != 0) {
        printf("ERROR: The image has compression\n");
        return 0;
    }
    // ncolours and importantcolours should be 0
    
    if (header -> ncolours != 0) {
        printf("ERROR: Number of colors is not 0\n");
        return 0;
    }
    
    if (header -> importantcolours != 0) {
        printf("ERROR: Important colors is not 0\n");
        return 0;
    }
    
    // Make sure we are getting 24 bits per pixel
    // or 16 bits per pixel
    // only for this assignment
    if (header->bits != 16 &&  header->bits != 24) {
        printf("ERROR: Image is not 24 or 16 bit/pixel \n");
        return 0;
    }
    // check for file size, image size
    // based on bits, width, and height
    //check for imagesize using size-offset=imagesize, each element is a part of the header structure, so use -> accordingly
    
    if (header->size - header->offset != header->imagesize) {
        printf("ERROR: Image Size not consistant \n");
        return 0;
    }
    
    
    //use ftell(fptr) for file position(file_pos)
    int file_pos = ftell(fptr);
    //check if input file can be read: if (fseek(fptr, 0, SEEK_END) != 0)
    if (fseek(fptr, 0, SEEK_END) != 0){
        printf("ERROR: Input file can not be read\n");
        return 0;
    }
    //use ftell(fptr) for file file size(file_size)
    int file_size = ftell(fptr);
    //check (fseek(fptr, file_pos, SEEK_SET) != 0) for input file reading check
    if (fseek(fptr, file_pos, SEEK_SET) != 0) {
        printf("ERROR: Input file reading check failed\n");
        return 0;
    }
    //check if file_size is not equal to header->size
    if (file_size!=header->size) {
        printf("ERROR: file size is inconsistant witht the header info\n");
        return 0;
    }
    
    //number of rows= width of file * number of bits +31
    int check_size = (header->width*header->height)*header->bits+BMP_HEADER_SIZE*8;
    if (check_size!=header->size*8) {
        printf("ERROR: Image size inconsistant\n");
        printf("The number of row is :%d The number of Col is :%d\n",header->width,header->height);
        printf("The size of the img is: %d\n",check_size);
        printf("The real size is %d\n",header->size*8);
        return 0;
    }
    
    //multiply total value by 4
    //check if number of rows*height is the image size
    
    return TRUE;
}

#endif



#ifdef TEST_BMPOPENFILE
/* The input argument is the source file pointer.
 * The function returns an address to a dynamically allocated BMPImage
 * only if the file contains a valid image file
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image,
 * also return NULL
 * Any error messages should be printed to stderr
 */


BMPImage *BMP_Open(const char *filename) {
    //open file
    //read file
    FILE *fptr = fopen(filename,"r");
    
    if (fptr == NULL) {
        printf("ERROR: Fail to opent the file\n");
        return NULL;
    }
    
    //Allocate memory for BMPImage*;
    
    BMPImage *bmpImage = (BMPImage *)malloc(sizeof(BMPImage));
    //check for memory allocation errors
    if (bmpImage == NULL) {
        printf("ERROR: Fail to allocate memory for bmpImage\n");
        return NULL;
    }
    
    //Read the first 54 bytes of the source into the header
    
    int read_size = fread(&(bmpImage->header), sizeof(BMPHeader), 1, fptr);
    if (read_size != 1) {
        printf("ERROR: Fail to read header\n");
        return NULL;
    }
    //Compute data size, width, height, and bytes per pixel;
    //check for any error while reading
    
    //check if the header is valid
    if (Is_BMPHeader_Valid(&(bmpImage->header),fptr) == FALSE) {
        return NULL;
    }
    // Allocate memory for image data
    //(bmpImage->data = (unsigned char *)malloc(sizeof(unsigned char)*((int)((bmpImage->header).imagesize))))
    //check error
    
    bmpImage->data = (unsigned char *)malloc(sizeof(unsigned char)*((int)((bmpImage->header).imagesize)));
    
    if (bmpImage->data == NULL) {
        printf("ERROR: Fail to malloc bmp data\n");
        return NULL;
    }
    
    // read in the image data
    int data_read_size = fread(bmpImage->data, (bmpImage->header).imagesize, 1, fptr);
    if (data_read_size != 1) {
        printf("ERROR: Fail to read image data\n");
        return NULL;
    }
    
    
    //check for error while reading
    
    fclose(fptr);
    return bmpImage;
}
#endif


#ifdef TEST_BMPWRITEFUNC
/* The input arguments are the destination file , BMPImage *image.
 * The function write the header and image data into the destination file.
 */
int BMP_Write(const char * outfile, BMPImage* image)
{
    FILE *fptr = fopen(outfile, "w");
    //open file and check for error
    if (fptr == NULL) {
        printf("ERROR: Fail to initialize wrting file pointer\n");
        return FALSE;
    }
    //check error for writing
    
    // write and check for image data:(fwrite(image->data, sizeof(unsigned char), (image->header).imagesize, fptr) != (image->header).imagesize)
    if(fwrite(&(image->header),BMP_HEADER_SIZE,1,fptr) != 1){
        printf("ERROR: Fail to write header\n");
        return FALSE;
    }
    
    if(fwrite(image->data,(image->header).imagesize,1, fptr) != 1){
        printf("ERROR: Fail to write image\n");
        return FALSE;
    }
    fclose(fptr);
    return TRUE;
}

#endif
/* The input argument is the BMPImage pointer. The function frees memory of
 * the BMPImage.
 */
#ifdef TEST_BMPFREEFUNC
void BMP_Free(BMPImage* image) {
    //free image if image is true
    free(image->data);
    free(image);
    return;
}

#endif

