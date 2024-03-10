/*Author: JJ McCauley
Creation Date: 3/8/24
Last Update: 3/8/24
Description: ---
User Interface: User will be asked for a number of arrays to be tested via the console.
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
    int *currentArray; //Will hold the current array of random integers
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
        cout << "inside for loop, iteration " << i << endl;
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
    cout << "Returning Arrays" << endl;
    return sizeArr;
}


int *getRandomArray(int size) {
    int *randArr = new int[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    for(int i = 0; i < size; i++) {
        *(randArr+i) = rand();
    }
    return randArr;    
}

float *getRandomFloatArray(int size) {
    float *randArr = new float[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    for(int i = 0; i < size; i++) {
        *(randArr+i) = static_cast<float>(rand())/RAND_MAX;
    }
    return randArr;
}


chrono::time_point<std::chrono::high_resolution_clock> startTimer() {
    auto start = chrono::high_resolution_clock::now();
    return start;
}


double endTimer(chrono::time_point<std::chrono::high_resolution_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    auto timeElasped = std::chrono::duration_cast<chrono::microseconds>(end-start);
    //timeElasped = timeElasped/1000000; //convert to seconds
    return (timeElasped.count());
}

//Given an array, will apply bounds to it (change the numbers so it only falls within 0 and the bound)
int *applyBounds(int *array, int arraySize, int bounds) {
    for(int i = 0; i < arraySize; i++) {
        array[i] = array[i]%(bounds);
    }
    return array;
}

//Time a given sorting algorithm and add it to the output file
void logTime(int *array, int size, ofstream &outfile, sortPtr sort) {
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    sort(array, size);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
}

//Time a radix sorting algorithm and add it to the output file
void logTimeRadix(int *array, int size, ofstream &outfile, int radix) {
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    radixsort(array, size, radix);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
}

//Time a sorting algorithm from the algorithm library and add it to the output file
void logTimeAlgSort(int *array, int size, ofstream &outfile) {
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    std::sort(array, array+size);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
}


void logTimeCount(int *array, int size, ofstream &outfile) {
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    long lsize = static_cast<long>(size);
    countsort(array, lsize);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
}


void logTimeBucket(float *array, int size, ofstream &outfile) {
    long lsize = static_cast<long>(size);
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    BucketSort(array, lsize);
    auto timeElasped = endTimer(start);
    outfile << static_cast<double>(timeElasped/1000000) << ",";
}