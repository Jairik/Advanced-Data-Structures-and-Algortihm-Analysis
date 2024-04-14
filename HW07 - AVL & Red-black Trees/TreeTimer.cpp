/* Top Comments Here*/

//Packages & header files used
#include <iostream>
#include <chrono> //Timing
#include <cstdlib> //rand() function
#include <cmath>
#include "RBTree.h" //header file for Red-Black Tree
#include "AVLTree.h" //header file for AVL Tree

using namespace std;

/* INSTRUCTIONS 1a
i. The number of nodes to insert into the tree (call it n).
ii. The range of integers values to insert, the interval [0, m].
iii. The number of insertion/deletion cycles they want to do. In an insertion/deletion cycle, you
will insert a random number into the tree, then you will find a different random number and
check if it is in the tree and if so delete the value. If the value is not in the tree you will find
another random number and so on until you get one in the tree and delete it*/

//Function Prototypes

//Insert a given number of nodes within a given range into the given object
template <class T> void insert(int, int, int, T);

//Given the given number of nodes within a given range, will run a 
//insert/deletion cycle on T tree
template <class T> void runCycle(int, int, int, T);


int main() {
    //Making tree objects
    AVLTree<int> avl;
    RBTree<int> rb;
    //Makng other relevant variables
    int numNodes, lowerBound, upperBound, cycles;
    bool loopAgain = false;
    do {
        cout << "Welcome to JJ's Program!" << endl;
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

        //Starting the timer

        //All program logic in here
    }
    while(loopAgain);
}


//SILLY COMMENTS HERE
template <class T>
void insert(int n, int lower, int upper, T tree) {
    for(int i = 0; i < n; i++) {
        tree.insert((rand()%upper-lower+1)+lower); //insert a random node into the tree
    }
}