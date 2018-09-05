
#include "hw04.h"

void cleanup (FILE * fpin)
{
    fclose (fpin);
}

bool readData (FILE * fpin, DataPoint * *dp, int nval, int dim)
{
    int niter, diter;
    for (niter = 0; niter < nval; niter++)
    {
        for (diter = 0; diter < dim; diter++)
        {
            if (fscanf (fpin, "%d", &dp[niter]->data[diter]) == 0)
            {
                return false;
            }
        }
    }
    return true;
}


void writeCentroids (const char *filename, Centroid * *centroids, int kval)
{
    FILE * fpout = fopen (filename, "w");
    if (fpout == NULL)
    {
        fprintf (stderr, "File %s, cannot be open\n", filename);
        exit (1);
    }
    int kiter;
    qsort (centroids, kval, sizeof (Centroid *), Centroid_cmp);
    for (kiter = 0; kiter < kval; kiter++)
    {
        Centroid_print (centroids[kiter], fpout);
    }
    fclose (fpout);
}




#ifdef TEST_DIST
long long int
distance (const DataPoint * datapoint, const Centroid * centroid)
{
    
    int size = datapoint -> dimension;
    long long int difference = 0;
    for (int i=0; i<size; i++) {
        difference = datapoint->data[i] - centroid->data[i];
        sum += difference*difference;
        
    }
    return sum;
}

#endif

#ifdef TEST_CLOSESTCENTROID

int closestCentroid (int kval, DataPoint * datapoint, Centroid * *centroids)
{
    long long int minDis = distance(datapoint, centroids[0]);
    long long int currentDis;
    for (int i=1; i<kval; i++) {
        currentDis = distance(datapoint, centroids[i]);
        
        if (minDis > currentDis) {
            minDis = currentDis;
            mindex = i;
        }
    }
    
    
    return mindex;
}

#endif

#ifdef TEST_KMEAN
void kmean (int kval, int nval, DataPoint * *datapoints, Centroid * *centroids)
{
    bool done = false;
    int randomIndex = 0;
    int temp;
    for (int i=0; i<kval; i++) {
        Centroid_reset(centroids[i]);
        
    }
    for (int i=0; i<nval; i++) {
        randomIndex = rand()%kval;
        datapoints[i] -> cluster = randomIndex;
        Centroid_addPoint(centroids[randomIndex],datapoints[i]);
    }
    
    for (int i=0; i<kval; i++) {
        Centroid_findCenter(centroids[i]);
    }
    
    
    
    while (true) {
        done  = true;
        for (int i=0; i<nval; i++) {
            temp = closestCentroid(kval,datapoints[i],centroids);
            /*if(temp == 3)
             {
             printf("Something\n");
             }*/
            if (datapoints[i]->cluster != temp) {
                datapoints[i]->cluster = temp;
                done = false;
            }
        }
        if(done)
        {
            break;
        }
        for (int i=0; i<kval; i++) {
            Centroid_reset(centroids[i]);
        }
        for (int i=0; i<nval; i++) {
            Centroid_addPoint(centroids[datapoints[i]->cluster], datapoints[i]);
        }
        for (int i=0; i<kval; i++) {
            Centroid_findCenter(centroids[i]);
        }
        
    }
    
}

#endif

/*===== DO NOT MODIFY BELOW THIS ======*/
int
main (int argc, char * *argv)
{
    
    if (argc < 4)
    {
        fprintf (stderr, "argc is %d, not 4\n", argc);
        return EXIT_FAILURE;
    }
    
    FILE * fpin = fopen (argv[1], "r");
    if (fpin == NULL)
    {
        fprintf (stderr, "fopen %s fail\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    int kval = (int) strtol (argv[2], NULL, 10);
    if (kval <= 0)
    {
        fprintf (stderr, "kval is %d, must be positive\n", kval);
        return EXIT_FAILURE;
    }
    srand (randseed);
    
    int nval;
    fscanf (fpin, "%d", &nval);
    if (nval < kval)
    {
        fprintf (stderr, "nval= %d must be greater than kval = %d\n", nval,
                 kval);
        cleanup (fpin);
        return EXIT_FAILURE;
    }
    
    int dim;
    fscanf (fpin, "%d", &dim);
    if (dim < 2)
    {
        fprintf (stderr, "nval= %d must be greater than kval = %d\n", nval,
                 kval);
        cleanup (fpin);
        return EXIT_FAILURE;
    }
    
    DataPoint * *datapoint_array = DataPoint_createArray (nval, dim);
    if (datapoint_array == NULL)
    {
        printf ("Error in creating datapoint array\n");
        cleanup (fpin);
        return EXIT_FAILURE;
    }
    
    Centroid * *centroids = Centroid_createArray (kval, dim);
    if (centroids == NULL)
    {
        printf ("Error in creating centroids array\n");
        DataPoint_freeArray (datapoint_array, nval);
        cleanup (fpin);
        return EXIT_FAILURE;
    }
    
    if (readData (fpin, datapoint_array, nval, dim) == false)
    {
        printf ("Error in reading data array\n");
        cleanup (fpin);
        DataPoint_freeArray (datapoint_array, nval);
        return EXIT_FAILURE;
    }
    
    kmean (kval, nval, datapoint_array, centroids);
    
    writeCentroids (argv[3], centroids, kval);
    DataPoint_freeArray (datapoint_array, nval);
    Centroid_freeArray (centroids, kval);
    cleanup (fpin);
    return EXIT_SUCCESS;
}


