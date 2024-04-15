/* Top Comments Here*/

//Packages & header files used for timing trees
#include <iostream>
#include <chrono> //Timing
#include <cstdlib> //rand() function
#include <cmath>
#include "RBTree.h" //header file for Red-Black Tree
#include "AVLTree.h" //header file for AVL Tree
//Packages used for awaiting for user input
#include <thread> 
#include <mutex> 
#include <condition_variable>

using namespace std;

//Function that asks the user if they woud like to loop again
bool getLoopAgain();
//Helper function to getLoopAgain
void getInput(mutex &, bool &, condition_variable &);


int main() {
    //Seeding random number generator
    srand(time(0));
    //Making tree objects
    AVLTree<int> avl;
    RBTree<int> rb;
    //Makng other relevant variables
    int numNodes, lowerBound, upperBound, cycles, randNum, IPL;
    double averageIPL;
    bool loopAgain = false, nodeFound = false;
    cout << "Welcome to JJ's Tree Timer!" << endl;

    do {
        //Getting numNodes, lowerBound, upperBoard, and cycles
        cout << "Enter the amount of nodes that you would like to insert: ";
        cin >> numNodes; 
        cout << "Next, you will select the range..." << endl;
        cout << "Lower Bound: ";
        cin >> lowerBound;
        cout << "Higher Bound: ";
        cin >> upperBound;
        cout << "Now, enter the number of Cycles: ";
        cin >> cycles;

        //----------------------AVL-Tree-----------
        cout << "Timing Now..." << endl;
        cout << "------------------------" << endl << "AVL Tree: " << endl;
        //Starting the timer
        auto startAVLTimer = chrono::high_resolution_clock::now();

        //Inserting nodes
        for(int i = 0; i < numNodes; i++) {
            avl.insertNode((rand()%upperBound-lowerBound+1)+lowerBound); //insert a random node into the tree
        }

        //Find the average IPL and print it to the screen
        IPL = 1; //avl.getIPL(); //Set to 1 for testing
        averageIPL = (double)IPL/numNodes; //should cast to a double
        cout << "Average IPL prior to cycles: " << averageIPL;

        //Running insertion + deletion cycles
        for(int i = 0; i < cycles; i++) {
            avl.insertNode((rand()%upperBound-lowerBound+1)+lowerBound);
            nodeFound = false;
            while(!nodeFound) { //Checking if it is found. If it is not, try again.
                randNum = (rand()%upperBound-lowerBound+1)+lowerBound;
                if(avl.searchNode(randNum)) {
                    avl.remove(randNum);
                    nodeFound = true;
                }
            }
        }

        //Find the average IPL after the cycles and print it to the screen
        IPL = 1; //avl.getIPL(); //Set to 1 for testing
        averageIPL = (double)IPL/numNodes; //should cast to a double
        cout << "Average IPL after cycles: " << averageIPL;

        //End the timer and print the time
        auto endAVLTimer = std::chrono::high_resolution_clock::now();
	    auto timeElaspedAVL = (chrono::duration_cast<chrono::microseconds>(endAVLTimer-startAVLTimer)).count();
   	    double tElaspedAVL = static_cast<double>(timeElaspedAVL) /1000000.0; //convert to seconds
        cout << "Time Elasped for " << numNodes << " nodes and " << cycles << " cycles: " << timeElaspedAVL << endl;

        loopAgain = getLoopAgain();
    }
    while(loopAgain);
}

/*
template <class T>
void cycle(int n, int lower, int upper, T tree) {
    for(int i = 0; i < n; i++) {
        tree.insert((rand()%upper-lower+1)+lower); //insert a random node into the tree
        tree.delete((rand()%upper-lower+1)+lower); //delete a random node from the tree
    }
} */

//SILLY COMMENTS
bool getLoopAgain() {
    //Variables used with helper getInput function
    mutex mtx; 
    bool inputReceived = false;
    condition_variable conditionVariable;

    //Asking for user input
    cout << "Restarting the program in 5 seconds, press any key to discontinue: ";

    //Opening thread, passing shared resources by reference
    thread inputThread(getInput, ref(mtx), ref(inputReceived), ref(conditionVariable));
    unique_lock<std::mutex> lock(mtx);

    //Waiting for the getInput function to return something for 5 seconds
    if(!conditionVariable.wait_for(lock, chrono::seconds(5), [&](){ return inputReceived; })) {
        //If nothing is returned, print the following statement
        cout << endl << "Exiting Program... See Ya Later!" << endl;
    }

    inputThread.join(); //Rejoin the threads
    return inputReceived;
}

//SIlly Comments
void getInput(mutex &mtx, bool &inputReceived, condition_variable &conditionVariable) {
    //Waiting to receive input
    char input;
    if(cin >> input) {
        //Closing thread
        lock_guard<mutex> lock(mtx);
        //Setting boolean as true and notifying condition variable
        inputReceived = true;
        conditionVariable.notify_one();
    }
}