/*Author: JJ McCauley
Creation Date: 3/8/24
Last Update: 3/8/24
Description: This program works with the header file "Sorts.h" to time various different
comparison and non-comparison based sorting algorithms. The program will receive the number
of arrays to sort from the user and the sizes for each respective array, then will randomly
assign integers to those arrays. The main function will then call each sort, timing it's
execution and logging it in a csv file called "SortTImes.csv". The array will be bounded
to either a range or floats when necessary.
User Interface: User will be asked for a number of arrays to be tested and the
array sizes via the console.
Notes: Algorithms and code were taken from either Data Structures and Algorithms 
in C++ by Adam Drozdek or Introduction to Algorithms Fourth Edition by Cormen, 
Leiserson, Rivest, and Stein */

//Header file provided by Dr. Spickler containing the different sorting algortihms
#include "Sorts.h" 
//Allows communication via the standard output
#include <iostream>
//Allows output to a file
#include <fstream>
//Timing with Chrono and randomly generating integers
#include <cstdlib>
#include <ctime>
#include <chrono>
//Getting the "algorithm"'s library sort algorithm
#include <algorithm>

using namespace std;
using namespace chrono;

/* Function Pointer to sort to the different functions, cleaning up main function */
using sortPtr = void(*)(int *, int); //Pass in the array and size

/* Function Prototypes */
//Retrieving and validating input for the number of arrays to be tested
int getNumArrays();
/*Tetrieve and validate input for the number of elements in each array, in which is returned 
via an int pointer */
int *getSizes(int);
//Return a pointer to an array of randomly generated integers, given size
int *getRandomArray(int);
//Return a pointer to an array of randomly generated floats
float *getRandomFloatArray(int);
//Given bounds, will set a max and min of the array
int *applyBounds(int *, int, int);
//Start the chrono timer and return the start time
chrono::time_point<std::chrono::high_resolution_clock> startTimer();
//Stop the chrono timer and return time elasped, given start as parameter
double endTimer(chrono::time_point<std::chrono::high_resolution_clock>);
//Will time the given function and output the time to the outfile
void logTime(int *, int, ofstream &, sortPtr);
//Time the sort for the sorting method from the algorithm library
void logTimeAlgSort(int *, int, ofstream &);
//Overloaded for radix sort
void logTimeRadix(int *, int, ofstream &, int);
//Overloaded for bucket sort
void logTimeBucket(float *, int, ofstream &);
//Overloaded for count sort
void logTimeCount(int *, int, ofstream &);


int main() {
    cout << "Welcome to JJ's Sort Timer Program!" << endl; //Introduction message
    int numArrays = getNumArrays(); //Get the number of arrays and assign to numArrays
    int *arraySizes = getSizes(numArrays); //Hold the size of each array
    int size; //Stores the size of the current array

    ofstream outFile("SortTimes.csv"); //Open the file to output the data into
    if(!outFile.is_open()) {
        cout << "Error - could not open file" << endl;
    }
    //Print the headers for the output file
    outFile << ",Merge Sort,Quick Sort,Comb Sort,Shell Sort,Heap Sort,Algorithm Library Sort,Radix Sort (Radix=10)";
    outFile << ",Radix Sort (Radix=100),Radix Sort (Radix=1000),Radix Sort (Radix=10000),Count Sort,Bucket Sort,";
    outFile << "Radix Sort (Radix=10 & Max=1000),Radix Sort (Radix=100 & Max=1000),Radix Sort (Radix=100 & Max=1000),";
    outFile << "Radix Sort (Radix=10000 & Max=1000),Count Sort (Max=1000)";
    cout << "Sorting now..." << endl;
    //Iterate through each sorting algorthim
    for(int i = 0; i < numArrays; i++) {
        size = arraySizes[i];
        outFile << "\n" << size << ",";
        int *array = getRandomArray(size);
        logTime(array, size, outFile, mergeSort);
        logTime(array, size, outFile, quickSort);
        logTime(array, size, outFile, combsort);
        logTime(array, size, outFile, Shellsort);
        logTime(array, size, outFile, heapsort);
        logTimeAlgSort(array, size, outFile);
        logTimeRadix(array, size, outFile, 10);
        logTimeRadix(array, size, outFile, 100);
        logTimeRadix(array, size, outFile, 1000);
        logTimeRadix(array, size, outFile, 10000);
        logTimeCount(array, size, outFile);
        array = applyBounds(array, size, 1000);
        logTimeRadix(array, size, outFile, 10);
        logTimeRadix(array, size, outFile, 100);
        logTimeRadix(array, size, outFile, 1000);
        logTimeRadix(array, size, outFile, 10000);
        logTimeCount(array, size, outFile);
        float *fArray = getRandomFloatArray(size);
        logTimeBucket(fArray, size, outFile);
        cout << "Array " << i << " Sorted..." << endl;
    } 
    outFile.close();
    cout << "Sorting Completed! Check the SortTimes.csv file for the results." << endl;
}

/*Description: This function asks the user for a number of arrays via the console, 
validates the input to ensure that it is positive, and returns that number.
Parameters: N/A
Return: int: Return the number of arrays the user would like to sort
Notes: N/A */
int getNumArrays() {
    int numArrays;
    bool valid = false;
    while(!valid) {
        cout << "Enter the number of arrays you would like to sort: ";
        cin >> numArrays;
        if(numArrays < 0 || numArrays > 9999) {
            cout << "Invalid number, please try again";
        }
        else {
            valid = true;
        }
    }
    return numArrays;
}

/*Description: This function asks the user for the array of size of each array
to be sorted, validating the input.
Parameters: int numofArrays: The number of arrays the user would like to sort
Return: int pointer: A pointer to an array of array sizes
Notes: N/A */
int *getSizes(int numOfArrays) {
    int size;
    bool valid;
    int *sizeArr = new int[numOfArrays]; //An array for the different sizes
    for(int i = 0; i < numOfArrays; i++) {
        valid = false;
        while(!valid) {
            cout << "Enter size of array " << i+1 << ": ";
            cin >> size;
            if(size < 0 || size > 99999999) {
                cout << "Invalid size, please try again" << endl;
            }
            else {
                valid = true;
            }
        }
        *(sizeArr+i) = size;
    }
    return sizeArr;
}

/*Description: This function will create the arrays of random integers, returning the
new array.
Parameters: int size: The size of the array to be assigned
Return: int pointer: A pointer to an array random integers
Notes: N/A */
int *getRandomArray(int size) {
    int *randArr = new int[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    for(int i = 0; i < size; i++) {
        *(randArr+i) = rand();
    }
    return randArr;    
}

/*Description: This function will create the arrays of random floats, returning the
new array.
Parameters: int size: The size of the array to be assigned
Return: float pointer: A pointer to an array of random float values
Notes: N/A */
float *getRandomFloatArray(int size) {
    float *randArr = new float[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    for(int i = 0; i < size; i++) {
        *(randArr+i) = static_cast<float>(rand())/RAND_MAX;
    }
    return randArr;
}

/*Description: This helper function starts the Chrono timer
Parameters: N/A
Return: chrono::time_point<std::chrono::high_resolution_clock>: A value holding 
the start time
Notes: N/A */
chrono::time_point<std::chrono::high_resolution_clock> startTimer() {
    auto start = chrono::high_resolution_clock::now();
    return start;
}

/*Description: This helper function ends the chrono timer, returning the amount
of time taken to execute.
Parameters: start: The start time
Return: double: Will return the time it took to execute the program, in milliseconds.
Notes: N/A */
double endTimer(chrono::time_point<std::chrono::high_resolution_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    auto timeElasped = std::chrono::duration_cast<chrono::microseconds>(end-start);
    //timeElasped = timeElasped/1000000; //convert to seconds
    return (timeElasped.count());
}

/*Description: This function applies a "bound" to an array, returning the new 
array with a maximum of "bounds"-1
Parameters: int pointer array: The current array that should be bounded
int arraySize: the size of the array
int bounds: The maximum range that should be allowed in the array
Return: int pointer: a pointer to the new array
Notes: N/A */
int *applyBounds(int *array, int arraySize, int bounds) {
    for(int i = 0; i < arraySize; i++) {
        array[i] = array[i]%(bounds);
    }
    return array;
}

/*Description: This function will create a new array copy called arrayCopy, ensuring
that the original array does not get modified. It will then start the chronos timer, calling
the startTimer helper funciton, then will run the provided sorting algorithm, end the timer 
using the helper function, and output the result to the SortTimes.csv file
Parameters: int *array: A pointer to the current array to be sorted
const int size: The size of the current array
ofstream &outfile: The output file for the result to be written to
sortPtr sort: A function pointer pointing to the sort algorithm to be ran
Return: N/A
Notes: N/A */
void logTime(int *array, const int size, ofstream &outfile, sortPtr sort) {
    //Make a copy of the current, unsorted array for the algorithm to sort
    int *arrayCopy = new int[size]; 
    for(int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }

    //Time the sort using the new array copy
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    sort(arrayCopy, size);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
    
    delete[] arrayCopy; //freeing memory 
}

/*Description: This function will create a new array copy called arrayCopy, ensuring
that the original array does not get modified. It will then start the chronos timer, calling
the startTimer helper funciton, then will run radix sort, end the timer 
using the helper function, and output the result to the SortTimes.csv file
Parameters: int *array: A pointer to the current array to be sorted
int size: The size of the current array
ofstream &outfile: The output file for the result to be written to
int radix: The current radix to pass through the radixSort function
Return: N/A
Notes: N/A */
void logTimeRadix(int *array, int size, ofstream &outfile, int radix) {
     //Make a copy of the current, unsorted array for the algorithm to sort
    int *arrayCopy = new int[size]; 
    for(int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }

    //Time the sort using the new array copy
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    radixsort(arrayCopy, size, radix);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
    delete[] arrayCopy; //freeing memory 
}

/*Description: This function will create a new array copy called arrayCopy, ensuring
that the original array does not get modified. It will then start the chronos timer, calling
the startTimer helper funciton, then will run the Algorith's Library Sorting function,
end the timer using the helper function, and output the result to the SortTimes.csv file
Parameters: int *array: A pointer to the current array to be sorted
int size: The size of the current array
ofstream &outfile: The output file for the result to be written to
Return: N/A
Notes: N/A */
void logTimeAlgSort(int *array, int size, ofstream &outfile) {
     //Make a copy of the current, unsorted array for the algorithm to sort
    int *arrayCopy = new int[size]; 
    for(int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }

    //Time the sort using the new array copy
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    std::sort(arrayCopy, arrayCopy+size);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";

    delete[] arrayCopy; //freeing memory 
}

/*Description: This function will create a new array copy called arrayCopy, ensuring
that the original array does not get modified. It will then start the chronos timer, calling
the startTimer helper funciton, then will run the Count sorting algorithm, end the timer 
using the helper function, and output the result to the SortTimes.csv file
Parameters: int *array: A pointer to the current array to be sorted
int size: The size of the current array
ofstram &outfile: The output file for the result to be written to
Return: N/A
Notes: N/A */
void logTimeCount(int *array, int size, ofstream &outfile) {
     //Make a copy of the current, unsorted array for the algorithm to sort
    int *arrayCopy = new int[size]; 
    for(int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }

    //Time the sort using the new array copy
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    long lsize = static_cast<long>(size);
    countsort(arrayCopy, lsize);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";

    delete[] arrayCopy; //freeing memory 
}

/*Description: This function will create a new array copy called arrayCopy, ensuring
that the original array does not get modified. It will then start the chronos timer, calling
the startTimer helper funciton, then will run the Bucket Sorting algorithm, end the timer 
using the helper function, and output the result to the SortTimes.csv file
Parameters: float *array: A pointer to the current array to be sorted
int size: The size of the current array
ofstram &outfile: The output file for the result to be written to
Return: N/A
Notes: N/A */
void logTimeBucket(float *array, int size, ofstream &outfile) {
     //Make a copy of the current, unsorted array for the algorithm to sort
    int *arrayCopy = new int[size]; 
    for(int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }

    //Time the sort using the new array copy
    long lsize = static_cast<long>(size);
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    BucketSort(arrayCopy, lsize);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";

    delete[] arrayCopy; //freeing memory 
}
