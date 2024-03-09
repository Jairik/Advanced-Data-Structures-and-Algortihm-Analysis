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

/* Function Pointers to sort to the different functions, cleaning up main function */
//Function Ptr for all sorts but radix and bucket sort
using sortPtr = void(*)(int *, int); //Pass in the array and size
//Function Ptr for Radix Sort (takes in extra int parameter)
using radixPtr = void(*)(int *, int, int);
//Function Ptr for Bucket Sort (takes in extra long parameter)
using bucketPtr = void(*)(int *, int, long);
//Function Ptr for Count Sort (takes in long as size)
using countPtr = void(*)(int *, long);



/* Function Prototypes */
//Retrieving and validating input for the number of arrays to be tested
int getNumArrays();
/*Tetrieve and validate input for the number of elements in each array, in which is returned 
via an int pointer */
int *getSizes(int);
//Return a pointer to an array of randomly generated integers, given size
int *getRandomArray(int);
//Given bounds, will set a max and min of the array
int *applyBounds(int *, int, int);
//Start the chrono timer and return the start time
chrono::time_point<std::chrono::high_resolution_clock> startTimer();
//Stop the chrono timer and return time elasped, given start as parameter
long endTimer(chrono::time_point<std::chrono::high_resolution_clock>);
//Will time the given function and output the time to the outfile
void logTime(int *, int, ofstream &, sortPtr);
//Overloaded for sort() from algorithm library
void logTime(int *, int, ofstream &, sortPtr);
//Overloaded for radix sort
void logTime(int *, int, ofstream &, radixPtr, int);
//Overloaded for bucket sort
void logTime(int *, int, ofstream &, bucketPtr, long);
//Overloaded for algoritghms sort method
void logTime(int *, int, ofstream &);
//Overloaded for count sort
void logTime(int *, long, ofstream &, countPtr);


int main() {
    int *currentArray; //Will hold the current array of random integers
    cout << "Welcome to JJ's Sort Timer Program!" << endl; //Introduction message
    int numArrays = getNumArrays(); //Get the number of arrays and assign to numArrays
    int *arraySizes = getSizes(numArrays); //Hold the size of each array
    int size; //Stores the size of the current array

    ofstream outFile("SortTimes.csv"); //Open the file to output the data into
    if(!outFile.is_open()) {
        cerr << "Error - could not open file" << endl;
    }
    //Print the headers for the output file
    outFile << ",Merge Sort,Quick Sort,Comb Sort,Shell Sort,Heap Sort,Algorithm Library Sort,Radix Sort (Radix=10)";
    outFile << ",Radix Sort (Radix=100),Radix Sort (Radix=1000),Radix Sort (Radix=10000),Count Sort,Bucket Sort,";
    outFile << "Radix Sort (Radix=10 & Max=1000),Radix Sort (Radix=100 & Max=1000),Radix Sort (Radix=100 & Max=1000),";
    outFile << "Radix Sort (Radix=10000 & Max=1000),Count Sort (Max=1000)";

    //Iterate through each sorting algorthim
    for(int i = 0; i < numArrays; i++) {
        size = arraySizes[i];
        outFile << "\n" << size << ",";
        int *array = getRandomArray(arraySizes[i]);
        logTime(array, size, outFile, mergeSort);
        logTime(array, size, outFile, quickSort);
        logTime(array, size, outFile, combsort);
        logTime(array, size, outFile, Shellsort);
        logTime(array, size, outFile, heapsort);
        logTime(array, size, outFile);
        logTime(array, size, outFile, radixsort, 10);
        logTime(array, size, outFile, radixsort, 100);
        logTime(array, size, outFile, radixsort, 1000);
        logTime(array, size, outFile, radixsort, 10000);
        logTime(array, size, outFile, countsort);
        logTime(array, size, outFile, BucketSort);
        array = applyBounds(array, size, 1000);
        logTime(array, size, outFile, radixsort, 10);
        logTime(array, size, outFile, radixsort, 100);
        logTime(array, size, outFile, radixsort, 1000);
        logTime(array, size, outFile, radixsort, 10000);
        logTime(array, size, outFile, countsort);
    } 
    
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


chrono::time_point<std::chrono::high_resolution_clock> startTimer() {
    auto start = chrono::high_resolution_clock::now();
    return start;
}


long endTimer(chrono::time_point<std::chrono::high_resolution_clock> start) {
    auto end = std::chrono::high_resolution_clock::now();
    auto timeElasped = std::chrono::duration_cast<chrono::microseconds>(end-start);
    timeElasped = timeElasped*1000000; //convert to seconds
    return timeElasped.count();
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
    /* Call and time the given function, exporting the result to a csv file */
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    sort(array, size);
    auto timeElasped = endTimer(start);
    outfile << timeElasped << ",";
}

//Time a radix sorting algorithm and add it to the output file
void logTime(int *array, int size, ofstream &outfile, radixPtr sort, int radix) {
    /* Call and time the given function, exporting the result to a csv file */
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    sort(array, size, radix);
    auto timeElasped = endTimer(start);
    outfile << timeElasped << ",";
}

//Time a bucekt sorting algorithm and add it to the output file
void logTime(int *array, int size, ofstream &outfile, bucketPtr sort, long bucket) {
    /* Call and time the given function, exporting the result to a csv file */
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    sort(array, size, bucket);
    auto timeElasped = endTimer(start);
    outfile << timeElasped << ",";
}

//Time a sorting algorithm from the algorithm library and add it to the output file
void logTime(int *array, int size, ofstream &outfile) {
    /* Call and time the sort method from the algorithm library, exporting the result to a csv file */
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    std::sort(array, array+size);
    auto timeElasped = endTimer(start);
    outfile << timeElasped << ",";
}

//Time a sorting algorithm from the algorithm library and add it to the output file
void logTime(int *array, long size, ofstream &outfile) {
    /* Call and time the sort method from the algorithm library, exporting the result to a csv file */
    chrono::time_point<std::chrono::high_resolution_clock> start = startTimer();
    countsort(array, size);
    auto timeElasped = endTimer(start);
    outfile << timeElasped << ",";
}