// Implementation file for the IntBinaryTree class
#include <iostream>
#include <cmath> //Used for the log function to determine height
#include <algorithm>
#include "IntBinaryTree.h"
using namespace std;

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

void IntBinaryTree::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
//****************************************************************

void IntBinaryTree::PrintTree(TreeNode *t, int Indent, int Level) {
	if (t != NULL) {
		PrintTree(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "\n";
		PrintTree(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left.
//****************************************************************

void IntBinaryTree::PrintTree(int Indent, int Level) {
	if (root != NULL)
		PrintTree(root, Indent, Level);
}

//****************************************************************
// This function calls the helper function to create an empty
// complete Binary Tree, calculating the height based on the size
//****************************************************************
void IntBinaryTree::createCompleteBT(int *arr, int arrSize) {
	int height = ceil(log2(arrSize))+1;
	int startHeight = 1;
	int cIndex = 0;
	auto maxElementIterator = max_element(arr, arr+arrSize);
	maxInt = *(maxElementIterator);
	IntBinaryTree::root = IntBinaryTree::makeCompleteBinaryTree(height, startHeight, arr, cIndex, arrSize);
}

//****************************************************************
// This function make a complete binary tree, given a height h. 
// It does this by recursively creating new nodes for the left and
// right children of the root, until the height becomes the same as
// the current height iterated. Helper function to createCompleteBT()
//****************************************************************
IntBinaryTree::TreeNode* IntBinaryTree::makeCompleteBinaryTree(int height, int currentHeight, int *arr, int &cIndex, int arrSize) {
    // If the height is 0 or less, making the tree already complete
    if (height <= 0 || currentHeight > height) {
        return nullptr;
    }

    TreeNode *node = new TreeNode();

    node->left = makeCompleteBinaryTree(height, currentHeight + 1, arr, cIndex, arrSize);
    node->right = makeCompleteBinaryTree(height, currentHeight + 1, arr, cIndex, arrSize);

    // If it's a leaf node, assign value from the array
    if (currentHeight == height) {
        if (cIndex < arrSize) {
            node->value = arr[cIndex++];
        } 
		else {
            node->value = maxInt+1;
        }
    }

    return node;
}

//****************************************************************
// This function iterate through the array, storing the root into
// the array and then updating the tree, recursively calling itself
// to update the values in the left and right subtrees
//****************************************************************
void IntBinaryTree::orderTree(IntBinaryTree::TreeNode *node, int &iterator, int height) {
	//If we are at the end of the array
	if(node) {
		iterator++;
		orderTree(node->left, iterator, height);
		orderTree(node->right, iterator, height);
		//if it falls within the leaf nodes, 
		if(iterator < height) {
			int smaller;
			if(node->left->value > node->right->value) {
				smaller = node->right->value;
			}
			else {
				smaller = node->left->value;
			}
			node->value = smaller;
		}
	}
}

//****************************************************************
// Gets called in the main, calling the above helper function
// to change the array by value
//****************************************************************
void IntBinaryTree::sortTree(int size) {
	int iterator = 0;
	int height = ceil(log2(size))+1;
	orderTree(root, iterator, height);
}

//****************************************************************
// Returns the smallest leaf node to be added to the array in the
// main function
//****************************************************************
int IntBinaryTree::getRoots(int size) {
	int minVal = root->value;
	TreeNode *temp = root; //Node used for iterating through an array
	while(temp->left || temp->right) { //search while it is not a leaf node
		if(temp->value == temp->right->value) {
			temp = temp->right;
		}
		else {
			temp = temp->right;
		}
		minVal = temp->value;
		temp->value = maxInt;
		sortTree(size);
		return minVal;
	}
}

