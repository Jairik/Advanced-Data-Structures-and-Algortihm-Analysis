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
#include <ostream>
//Timing with Chrono and randomly generating integers
#include <cstdlib>
#include <ctime>
#include <chrono>
//Getting the "algorithm"'s library sort algorithm
#include <algorithm>


using namespace std;

/* Function Prototype */
//Retrieving and validating input for the number of arrays to be tested
int getNumArrays();
/*Tetrieve and validate input for the number of elements in each array, in which is returned 
via an int pointer */
int *getSizes(int);
//Return a pointer to an array of randomly generated integers, given size and bounds
int *getRandomArray(int, int);
//Start the chrono timer
void startTimer();
//Stop the chrono timer and return time elasped
double endTimer();
//Helper function to clean up and simplify main, write the given output to the ofstream
void logTime(ofstream);


int main() {
    int numOfArrays; //Number of arrays to iterate through
    
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
}


int *getRandomArray(int size, int bounds) {
    int *randArr = new int[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    if(bounds == 0) { 
        for(int i = 0; i < size; i++) {
            *(randArr+i) = rand();
        }
    }
    //Create an array with no bounds
    else { 
        for(int i = 0; i < size; i++) {
            *(randArr+i) = rand()%(bounds+1);
        }
    }
    return randArr;    
}


void startTimer() {

}


double endTimer() {
    double timeElasped = 0;
    //some logic for timing here
    return timeElasped;
}