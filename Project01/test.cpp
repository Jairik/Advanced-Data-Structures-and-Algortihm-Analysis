//TEST PROG FOR JJ
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

#include "Sorts.h"

int main() {
    int size = 1000000;
    int *randArr = new int[size];
    srand(time(0)); //Seed the random number generator
    //Create an array with bounds, with '0' being a signal value
    for(int i = 0; i < size; i++) {
        *(randArr+i) = rand()%1000;
    }
    radixsort(&randArr, size, 10000);
    for(int i = 0; i < size; i++) {
        cout << randArr[i] << ", ";
    }
}
