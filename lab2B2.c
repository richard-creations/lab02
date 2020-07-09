#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const char DATA_FILE_NAME[] = "TestData.txt";

typedef struct functionRuntimes
{
    char *name;           //name of the function being tested
    double **times;       //run times
    double *avg;          //average runtime
    int numTestCases;     //number of times to repeat each test size
    int numTestCaseSizes; //number of test sizes
    int *testCaseSizes;   //array containing the test sizes
} functionRuntimes;

//Functions used to test the runtimes
functionRuntimes timeAlgorithm(char *, int, int, int[], void (*f)(FILE *));
FILE *generateTestInput(int, int, int);
void computeAvg(functionRuntimes fRT);
void printRuntimeTable(functionRuntimes fRT);
void freeFunctionRuntimes(functionRuntimes fRT);

//Functions whose runtime will be tested (and helper functions)
void insertionSortInitial(FILE *input);
void insertionSort(int *points, int low, int high);
void quickSortOptInitial(FILE *input);
void quickSortOpt(int *points, int low, int high);
int partition(int *points, int low, int high);

void mysteryRuntime1(FILE *input);
void mysteryRuntime2(FILE *input);
void mysteryRuntime3(FILE *input);

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 * (if you make alterations plan to revert them before submission)
 */
int main(int argc, char *argv[])
{
    functionRuntimes fRT;
    int sizes1[] = {100000, 250000, 500000, 750000, 1000000};
    int sizes2[] = {10000, 20000, 40000, 80000};

    srand(time(0));
    fRT = timeAlgorithm("Insertion Sort", 10, 5, sizes1, insertionSortInitial);
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("quicksort (uses insertion sort when sorting <30 numbers)", 10, 5, sizes1, quickSortOptInitial);
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    return 0;
}

/*************************************** Functions to have their runtimes tested *********************************************/

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime1(FILE *input)
{
    int temp;
    int size;
    int i = 0;
    int *array;

    if (fscanf(input, "%d", &size) != 1)
    {
        exit(-1);
    }
    array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        exit(-1);
    }

    while (fscanf(input, "%d", &temp) == 1 && i < size)
    {
        array[i] = temp;
        i++;
    }

    while (size > 1)
    {
        size = size / 2;
        array[size / 2] = array[size];
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime2(FILE *input)
{
    int temp;
    int size;
    int i = 0, j = 0;
    int *array;

    if (fscanf(input, "%d", &size) != 1)
    {
        exit(-1);
    }
    array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        exit(-1);
    }

    while (fscanf(input, "%d", &temp) == 1 && i < size)
    {
        array[i] = temp;
        i++;
    }

    i = 0;
    while (j < size)
    {
        array[j] = array[i];

        i++;
        if (i >= size)
        {
            j++;
            i = 0;
        }
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime3(FILE *input)
{
    int temp;
    int size;
    int n;
    int i = 0;
    int *array;

    if (fscanf(input, "%d", &size) != 1)
    {
        exit(-1);
    }
    array = (int *)malloc(size * sizeof(int));
    if (array == NULL)
    {
        exit(-1);
    }

    while (fscanf(input, "%d", &temp) == 1 && i < size)
    {
        array[i] = temp;
        i++;
    }

    for (i = 0; i < size; i++)
    {
        for (n = size - 1; n > 1; n /= 1.01)
        {
            array[n - 1] = array[n];
        }
    }

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSortInitial(FILE *input)
{
    int i;
    int size;
    int *array;

    fscanf(input, "%d", &size);
    array = (int *)malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
    {
        fscanf(input, "%d", &array[i]);
    }

    insertionSort(array, 0, size - 1);

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i])
        {
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSort(int *points, int low, int high)
{
    int i, j;
    double temp;

    for (i = low + 1; i <= high; i++)
    {
        for (j = i; j > low && points[j] < points[j - 1]; j--)
        {
            temp = points[j];
            points[j] = points[j - 1];
            points[j - 1] = temp;
        }
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOptInitial(FILE *input)
{
    int i;
    int size;
    int *array;

    fscanf(input, "%d", &size);
    array = (int *)malloc(size * sizeof(int));

    for (i = 0; i < size; i++)
    {
        fscanf(input, "%d", &array[i]);
    }

    quickSortOpt(array, 0, size - 1);

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i]){
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOpt(int *points, int low, int high)
{
    if (high < low + 30)
    {
        insertionSort(points, low, high);
    }
    else
    {
        int pivot = partition(points, low, high);

        quickSortOpt(points, low, pivot - 1);
        quickSortOpt(points, pivot + 1, high);
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
int partition(int *points, int low, int high)
{
    int pivot = rand() % (high - low + 1) + low;
    int pivotValue = points[pivot];
    int i = low + 1;
    int j = high;
    int temp;

    points[pivot] = points[low];
    points[low] = pivotValue;

    while (i < j)
    {
        while (i <= high && points[i] <= pivotValue)
        {
            i++;
        }
        while (j >= low && points[j] > pivotValue)
        {
            j--;
        }
        if (i < j) //swap out of order elements
        {
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
        }
    }
    if (i <= high && points[i] <= pivotValue)
    {
        i++;
    }

    points[low] = points[i - 1];
    points[i - 1] = pivotValue;

    return i - 1;
}

/*************************************** Functions for finding and printing runtime *********************************************/

/*
Give your asymptotic estimates for the runtimes of the following 3 functions:

mysteryRuntime1:  O( N )
mysteryRuntime2:  O( N^2  )
mysteryRuntime3:  O( N^2  )
*/

/* TO BE COMPLETED BY YOU
 * Fill in the missing parts of the code (see TODOs below)
 */
functionRuntimes timeAlgorithm(char *name, int numTestCases, int numTestCaseSizes, int testCaseSizes[], void (*f)(FILE *))
{
    /* Call and calculate the runtime of the provided function f */
    clock_t start, end;
    int i, j;
    FILE *testData;

    //create functionRuntimes variable to return
    functionRuntimes fRT;
    //TODO: copy passed data into the fRT variable
    fRT.name = name;
    fRT.numTestCases = numTestCases;
    fRT.numTestCaseSizes = numTestCaseSizes;
    fRT.testCaseSizes = testCaseSizes;
    fRT.avg = malloc(sizeof(double) * numTestCaseSizes);

    //TODO: initialize and fill in the runtimes table
    fRT.times = malloc(sizeof(double *) * numTestCaseSizes); /* instead malloc an array of double*s of size numTestCaseSizes */

    for (i = 0; i < numTestCaseSizes; i++)
    {
        fRT.times[i] = malloc(sizeof(double) * numTestCases); /* instead malloc an array of doubles of size numTestCases */

        for (j = 0; j < numTestCases; j++)
        {
            //Generate test data for the function f
            testData = generateTestInput(0, testCaseSizes[i], testCaseSizes[i]);

            //Run f on the generated test data
            start = clock();
            f(testData);
            end = clock();
            fclose(testData);

            //Enter the elapsed number of seconds into the times array for fRT
            fRT.times[i][j] = (double)(end - start) / CLOCKS_PER_SEC;
        }
    }

    //TODO: Calculate the average runtimes (call computeAvg here)
    computeAvg(fRT);
    return fRT;
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
FILE *generateTestInput(int min, int max, int size)
{
    int i;
    FILE *data = fopen(DATA_FILE_NAME, "w");

    if (data == NULL)
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }

    //add size to start of file
    fprintf(data, "%d ", size);
    //Fill the file with random data
    for (i = 0; i < size; i++)
    {
        fprintf(data, "%d ", rand() % (max - min + 1) + min);
    }
    fclose(data);

    data = fopen(DATA_FILE_NAME, "r");
    if (data == NULL)
    {
        printf("Failed to create file %s\n", DATA_FILE_NAME);
        exit(-1);
    }
    return data;
}

/* TO BE COMPLETED BY YOU
 * Calculate and insert the average runtime for each set of test data into fRT
 */
void computeAvg(functionRuntimes fRT)
{
    int n = fRT.numTestCaseSizes;
    double sum;

    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < fRT.numTestCases; j++)
        {
            sum += fRT.times[i][j];
        }
        fRT.avg[i] = sum / fRT.numTestCases;
    }
}

/* TO BE COMPLETED BY YOU
 * Print the information in fRT as a 2d table.  Display 3 digits after the decimal point.  You can assume all of the runtimes are <= 99.999 seconds.
 */
void printRuntimeTable(functionRuntimes fRT)
{
    printf("%s\n", fRT.name);
    printf("Test size      ");
    for (int i = 0; i < fRT.numTestCases; i++)
    {
        printf("\tTest #%d", i);
    }
    printf("\tAverage\n");

    for (int i = 0; i < fRT.numTestCaseSizes; i++)
    {
        printf("%d     ", fRT.testCaseSizes[i]);

        for (int j = 0; j < fRT.numTestCases; j++)
        {
            printf("\t%.3f ", fRT.times[i][j]);
        }
        printf("\t%.3f ", fRT.avg[i]);
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

/* TO BE COMPLETED BY YOU
 * Free all of the dynamically allocated memory in fRT
 */
void freeFunctionRuntimes(functionRuntimes fRT)
{
    //free(fRT.&name);
    for (int i = 0; i < fRT.numTestCaseSizes; i++)
    {
        free(fRT.times[i]);
    }
    free(fRT.times);
    free(fRT.avg);
}
