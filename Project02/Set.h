#ifndef SET_H
#define SET_H

#include "RBTree.h"
#include <vector>

/* ---------------------------- Set Header File ---------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/18/24
   Description: <One paragraph describing the set of functions the file contains>
   Notes: Inherits properties from the Red-Black Tree
   ---------------------------------------------------------------------------- */

   template <class T>
   class Set : public RBTree<T> {
    public:
        //Member functions
        Set();
        ~Set();
        Set(const Set &);
        Set<T>& operator=(const Set<T>);
        void Clear(); //Clears the set
        int getSize(); //Gets the size of the set
        bool find(T); //Searches the set for a given element
        bool isEmpty(); //Determines if the set is empty
    private:
        int size; //Increments or decrements based on insertions
        T *getInorder(); //Returns array of inordered elements 
        void getInorderHelper(RBTreeNode<T>, int *&, int); //Helper function that recursively iterates through the tree in-order
        void printInOrder(); //Prints the set's elements in-order
        void sizeHelper(int &); //Helper function that transverses through the tree and increments size
   };

   //Implementations here

    //Default Constructor
    template <class T> 
    Set<T>::Set() { size = 0; }

    //Default Deconstructor - Automatically called
    template <class T>
    Set<T>::~Set() { size = 0; }

    /*Copy Constructor - Copies a given Set
    Parameters: The set to be copied */
    template <class T>
    Set<T>::Set(const Set<T> &copy) : RBTree<T>(copy) {
        //Will automatically call the RBTree copy contructor
        this.size = copy.size;
    }

    /*Overloaded Assignment Operator
    Paramters: The set to be assigned 
    Method: Clear the current tree, then copy the current one to it*/
    template <class T>
    Set<T>& Set<T>::operator=(const Set<T> &rightSet) {
        clear(); 
        RBTreeNode<T> *tempPtr; //Temp ptr so the copy function can return something
        tempPtr = this.copy(rightSet.root, rightSet.NIL);
        this.size = rightSet.size; //Setting the sizes to be equal
        return *this; //Return the current tree
    }

    /* Clear function - clears the current tree of all elements 
    Parameters: N/A
    Method: Destroy the current subtree */
    template <class T>
    void Set<T>::Clear() {
        destroySubTree(this->root);
        size = 0; 
    }

    /* getInOrder function - returns an array of in-order elements
    Parameters: N/A
    Returns: An array of in-order elements */
    template <class T>
    T Set<T>::*getInOrder() {
        int numElements = getSize(); //Get the number of elements to allocate array
        int *elementArray = new int[numElements]; //Allocating space for elements
        getInOrderHelper(this.root, elementArray, 0); //Get the in-order array
        return elementArray; //Returns the sorted in-order array
    }

    /* getInOrderHelper function - recursively adds elements to the elementArray
    Parameters: RBTreeNode<T> nodePtr - The current pointer in the tree
    int *elementArray - the array to be changed. Will be changed by reference
    int iterator - the current point in the array
    Returns: An array of in-order elements */
    template <class T>
    void Set<T>::getInOrderHelper(RBTreeNode<T> nodePtr, int *&elementArray, int iterator) {
        if (nodePtr) {
		    getInOrderHelperInOrder(nodePtr->left);
		    elementArray[iterator++] = nodePtr->value;
		    displayInOrder(nodePtr->right);
	    } 
    }

    /* Size function - returns the size of the tree
    Returns: the size of the set */
    template <class T>
    int Set<T>::getSize() {
        return size;
    }

    /* Find function - returns whether a given element was found
    Parameter: T element - the element to search for*/
    template <class T>
    bool Set<T>::find(T element) {
        return findNode(element); //Calls function from RBTree
    }

    /* isEmtpy function - returns if the set is empty */
    template <class T>
    bool Set<T>::isEmpty() {
        return(root); //Returns if the root is found
    }

    


#endif 