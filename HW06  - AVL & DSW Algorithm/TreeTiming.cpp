/*Author: JJ McCauley (BST Code provided by Dr. Spickler)
Creation Date: 4/5/24
Last Update: 4/5/24
Description: This program aims to time AVL Insertion and BST Insertion + DSW Algorithm, allowing for the
user to choose array size and data range. An array will then be created with random integers within that
range, and the time elasped will be outputted to the console.
User Interface: N/A
Notes: N/A */

//Header files include code for AVL and DSW Algorithm
#include "AVLTree.h"
#include "BinaryTree.h"

//Cleaning code
using namespace std;

//Libraries Used
#include <iostream> //Communication with the console
#include <chrono> //Used for timing insertion to the trees

//Function Prototypes
int getNumNodes(); //Receive the number of nodes from the user
void getDataRange(int *); //Receive the range of integers to be inserted
void getRandArray(int *&, int, int *); //Will get the random array of integers to be inserted
bool getIterateAgain(); //Receive whether the user would like to iterate again

int main() {
    int numNodes; //Number of nodes to be inserted
    int dataRange[2]; //Holds the range of data
    int *randData; //Holds an array of numNodes random integers withing dataRange
    bool iterateAgain = false; //Allow the restart the process without restarting the program
    AVLTree<int> avlt;
    BinaryTree<int> bst;

    cout << "Welcome to JJ's Timing Algorithm" << endl;

    do {
        //Collecting user input
        numNodes = getNumNodes();
        getDataRange(dataRange);
        getRandArray(randData, numNodes, dataRange);

        /* Testing AVL Times */

        //Starting the timer
        cout << "Timing AVL..." << endl;
        auto start = chrono::high_resolution_clock::now();

        //Iterating through the array and inserting numNodes nodes
        for(int i = 0; i < numNodes; i++) {
            avlt.insertNode(randData[i]);
        }

        //Ending the timer
        auto end = std::chrono::high_resolution_clock::now();
        auto timeElasped = (std::chrono::duration_cast<chrono::microseconds>(end-start)).count();
        double tElasped = static_cast<double>(timeElasped) /1000000.0; //converting to seconds
        cout << "Time Elasped for AVL Insertion: " << tElasped << " seconds" << endl;

        /* Testing BST + DSW Times */

        //Starting the timer
        cout << "Timing BST & DSW..." << endl;
        start = chrono::high_resolution_clock::now();

        //Iterating through the array and inserting numNodes nodes. Then, creating backbone.
        for(int i = 0; i < numNodes; i++) {
            bst.insertNode(randData[i]);
        }
        bst.balance();

        //Ending the timer
        end = std::chrono::high_resolution_clock::now();
        timeElasped = (std::chrono::duration_cast<chrono::microseconds>(end-start)).count();
        tElasped = static_cast<double>(timeElasped) /1000000.0; //converting to seconds
        cout << "Time Elasped for BST Insertion + DSW Algorithm: ";
        cout << tElasped << " seconds" << endl;

        //Asking the user if they would like to run the program again
        char userChoice;
        cout << "Would you like to test another array count? (Y/N)" << endl;
        cin >> userChoice;
        if(userChoice == 'Y' || userChoice == 'y') {
            iterateAgain = true;
        }
        else {
            iterateAgain = false;
        }
    }
    while(iterateAgain);
    cout << "Thank you for using JJ's program, see ya!" << endl;
}

/*Description: Receives the number of nodes from the user, validating them to ensure
that the choice is positive
Parameters: N/A
Return: integer numNodes- the number of nodes the user selected
Notes: N/A*/
int getNumNodes() {
    int numNodes;
    bool valid = false;
    while(!valid) {
        cout << "Enter the number of nodes: ";
        cin >> numNodes;
        if(numNodes < 0) {
            cout << "Invalid input, please try again" << endl;
        }
        else {
            valid = true;
        }
    }
    return numNodes;
}

/*Description: This function generates random arrays of numNodes size within 
the specified bounds. This is implemented to more accurately examine the 
insertion times of the BST and AVL Tree, removing the step of randomly 
calculating integers.
Parameters: int *randData- stores the random array that will be replaced
int numNodes- the number of random integer nodes
int *range- an array that holds the upper and lower range
Return: N/A
Notes: N/A*/
void getRandArray(int *&randData, int numNodes, int *range) {
    int lowerBound, upperBound;
    randData = new int[numNodes]; //Allocating the proper memory to avoid segfaults
    srand(time(0)); //seeding the random number generator
    //Storing the upper and lower range in seperate variables
    lowerBound = range[0];
    upperBound = range[1];
    
    //Iterate numNodes times and assign random numbers within lowerBound and upperBound
    for(int i = 0; i < numNodes; i++) {
        *(randData+i) = (rand()%(upperBound-lowerBound))+lowerBound;
    }
}

/*Description: Receives an upper bound and lower bound from the user, validating the input
Parameters: int *bounds- an pointer to a 2-element array of lower bound and upper bound
Return: N/A
Notes: N/A */
void getDataRange(int *bounds) {
    int lowBound, highBound;
    bool valid = false;
    while(!valid) {
        cout << "Enter the lower bound & upper bound, seperated by a space" << endl;
        cin >> lowBound >> highBound; //Collecting the low & high bound
        if(lowBound > highBound || lowBound < 0 || highBound < 0) {
            cout << "Invalid input, please try again" << endl;
        }
        else {
            valid = true;
        }
    }
}

