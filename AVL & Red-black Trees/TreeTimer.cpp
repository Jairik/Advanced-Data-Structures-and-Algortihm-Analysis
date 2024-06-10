//Author: JJ McCauley

//Packages & header files used for timing trees
#include <iostream>
#include <chrono> //Timing
#include <cstdlib> //rand() function
#include <cmath>
#include "RBTree.h" //header file for Red-Black Tree
#include "AVLTree.h" //header file for AVL Tree

using namespace std;

//Function that asks the user if they woud like to loop again
bool getLoopAgain();


int main() {
    //Seeding random number generator
    srand(time(0));
    //Making tree objects
    AVLTree<int> avl;
    RBTree<int> rb;
    //Makng other relevant variables
    int numNodes, lowerBound, upperBound, cycles, randNum, avlIPL, rbIPL;
    double averageAVLIPL, averageRBIPL;
    bool loopAgain = true, nodeFound = false;
    cout << "Welcome to JJ's Tree Timer!" << endl;

    while(loopAgain) {
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

        /*----------------------AVL-Tree----------------------*/

        cout << "Timing Now..." << endl;
        cout << "------------------------" << endl << "AVL Tree: " << endl;
        //Starting the timer
        auto startAVLTimer = chrono::high_resolution_clock::now();

        //Inserting nodes
        for(int i = 0; i < numNodes; i++) {
            avl.insertNode(rand()%(upperBound-lowerBound+1)+lowerBound); //insert a random node into the tree
        }

        //Find the average IPL and print it to the screen
        avlIPL = avl.getIPL(); //Set to 1 for testing
        averageAVLIPL = (double)avlIPL/numNodes; //should cast to a double
        cout << "Average IPL prior to cycles: " << averageAVLIPL << endl;

        //Running insertion + deletion cycles
        for(int i = 0; i < cycles; i++) {
            avl.insertNode(rand()%(upperBound-lowerBound+1)+lowerBound);
            nodeFound = false;
            while(!nodeFound) { //Checking if it is found. If it is not, try again.
                randNum = rand()%(upperBound-lowerBound+1)+lowerBound;
                if(avl.searchNode(randNum)) {
                    avl.remove(randNum);
                    nodeFound = true;
                }
            }
        }

        //Find the average IPL after the cycles and print it to the screen
        avlIPL = avl.getIPL(); 
        averageAVLIPL = (double)avlIPL/numNodes; //should cast to a double
        cout << "Average IPL after cycles: " << averageAVLIPL << endl;

        //End the timer and print the time
        auto endAVLTimer = std::chrono::high_resolution_clock::now();
	    auto timeElaspedAVL = (chrono::duration_cast<chrono::microseconds>(endAVLTimer-startAVLTimer)).count();
   	    double tElapsedAVL = static_cast<double>(timeElaspedAVL) /1000000.0; //convert to seconds
        cout << endl << "Time Elasped for " << numNodes << " nodes and " << cycles << " cycles: " << tElapsedAVL << " seconds" << endl << endl;


        /*----------------------Red-Black-Tree----------------------*/

        cout << "------------------------" << endl << "Red-Black Tree: " << endl;
        //Starting the timer
        auto startRBTimer = chrono::high_resolution_clock::now();

        //Inserting nodes
        for(int i = 0; i < numNodes; i++) {
            rb.insert(rand()%(upperBound-lowerBound+1)+lowerBound); //insert a random node
        }

        //Find the average IPL and print it to the screen
        rbIPL = rb.getIPL(); //Set to 1 for testing
        averageRBIPL = (double)rbIPL/numNodes; //should cast to a double
        cout << "Average IPL prior to cycles: " << averageRBIPL << endl;

        //Running insertion + deletion cycles
        for(int i = 0; i < cycles; i++) {
            rb.insert(rand()%(upperBound-lowerBound+1)+lowerBound);
            nodeFound = false;
            while(!nodeFound) { //Checking if it is found. If it is not, try again.
                randNum = rand()%(upperBound-lowerBound+1)+lowerBound;
                if(rb.find(randNum)) {
                    rb.remove(randNum);
                    nodeFound = true;
                }
            }
        }

        //Find the average IPL after the cycles and print it to the screen
        rbIPL = rb.getIPL();
        averageRBIPL = (double)rbIPL/numNodes; //should cast to a double
        cout << "Average IPL after cycles: " << averageRBIPL << endl;

        //End the timer and print the time
        auto endRBTimer = std::chrono::high_resolution_clock::now();
	    auto timeElaspedRB = (chrono::duration_cast<chrono::microseconds>(endRBTimer-startRBTimer)).count();
   	    double tElapsedRB = static_cast<double>(timeElaspedRB) /1000000.0; //convert to seconds
        cout << endl << "Time Elasped for " << numNodes << " nodes and " << cycles << " cycles: " << tElapsedRB << " seconds" << endl;    

        /* --- Ask user if they would like to loop again ---*/
        loopAgain = getLoopAgain();
    }
    cout << "See ya soon!" << endl;
}

/*Description: Helper function that asks the user if they would like to loop again, returning the result
  Parameters: N/A
  Return: int: bool lAgain: If the user would like to play again
  Notes: N/A */
bool getLoopAgain() {
    char c;
    bool lAgain = false;
    cout << "Would you like to loop again (Y/N)? ";
    cin >> c;
    if(c == 'y' || c == 'Y') {
        lAgain = true;
    }
    return lAgain;
}


/* This didn't quite work as expected, I am going to keep it here because I would love to implement it
later in the future. For now, however, I will go for something more basic.
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
} */