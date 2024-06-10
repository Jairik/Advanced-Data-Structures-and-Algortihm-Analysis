#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "IntBinaryTree.h"

using namespace std;

int main() {
	srand(time(0));

	IntBinaryTree tree;
	int arrSize; //The size of the array to sort

	//Getting input from user
	cout << "Welcome to JJ's BST Sorting!" << endl;
	cout << "Enter the size of the array: ";
	cin >> arrSize;

	//Creating the array and placing random integers in it
	int *arr = new int[arrSize];
	for(int i = 0; i < arrSize; i++) {
		arr[i] = rand();
	}

	//Start timing via Chrono
	auto start = chrono::high_resolution_clock::now();
	
	//Placing it into a tree, then returning it in the array
	tree.loadArray(arr, arrSize);
	tree.sortFromInorder(arr);

	//End timing via Chrono, outputting the time (seconds)
	//to the standard output 
	auto end = std::chrono::high_resolution_clock::now();
	auto timeElasped = (std::chrono::duration_cast<chrono::microseconds>(end-start)).count();
   	double tElasped = static_cast<double>(timeElasped) /1000000.0; //convert to seconds
    cout << "Time elasped for array size " << arrSize << ": " << tElasped << endl;

	/*cout << "Tree:\n";
	tree.PrintTree(); */

	cout << endl;
	return 0;
}
