#ifndef SET_H
#define SET_H

#include "RBTree.h"
#include <vector>
#include <iostream>

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
        void clear(); //Clears the set
        int getSize(); //Gets the size of the set
        bool find(T); //Searches the set for a given element
        bool isEmpty(); //Determines if the set is empty
        vector<T> toVector();
        T *toArray();
        void erase(T);
        void insert(T) override;
        bool operator==(const Set<T>); 
        bool operator!=(const Set<T>);
        bool operator>(const Set<T>);
        bool operator<(const Set<T>);
        bool operator>=(const Set<T>);
        bool operator<=(const Set<T>);
        Set<T>& operator+(const Set<T>); //Set union
        Set<T>& operator*(const Set<T>); //Set intersection
        Set<T>& operator-(const Set<T>); //Set difference
        std::ostream& operator<<(std::ostream&, const Set<T>&);

    private:
        int size; //Increments or decrements based on insertions
        T *getInorder(); //Returns array of inordered elements 
        void getInOrderHelper(RBTreeNode<T>, T *&, int); //Helper function that recursively iterates through the tree in-order
        void sizeHelper(int &); //Helper function that transverses through the tree and increments size
        bool equalsOperatorHelper(RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *);
   };

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
    Set<T> &Set<T>::operator=(const Set<T> &rightSet) {
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
    void Set<T>::clear() {
        destroySubTree(this.root);
        size = 0; 
    }

    /* getInOrder function - returns an array of in-order elements
    Parameters: N/A
    Returns: An array of in-order elements */
    template <class T>
    T Set<T>::*getInOrder() {
        int numElements = getSize(); //Get the number of elements to allocate array
        T *elementArray = new int[numElements]; //Allocating space for elements
        getInOrderHelper(root, elementArray, 0); //Get the in-order array
        return elementArray; //Returns the sorted in-order array
    }

    /* getInOrderHelper function - recursively adds elements to the elementArray
    Parameters: RBTreeNode<T> nodePtr - The current pointer in the tree
    int *elementArray - the array to be changed. Will be changed by reference
    int iterator - the current point in the array
    Returns: An array of in-order elements */
    template <class T>
    void Set<T>::getInOrderHelper(RBTreeNode<T> nodePtr, T *&elementArray, int iterator) {
        if (nodePtr) {
		    getInOrderHelperInOrder(nodePtr->left);
		    elementArray[iterator++] = nodePtr->value;
		    getInOrderHelperInOrder(nodePtr->right);
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

    /* isEmpty function - returns if the set is empty */
    template <class T>
    bool Set<T>::isEmpty() {
        return(root); //Returns if the root is found
    }

    /* toVector function - converts a set to a vector 
    Returns: The set as a vector
    Method: Call the getInOrder function, then convert to a vector */
    template <class T>
    vector<T> Set<T>::toVector() {
        T *setAsArray = getInOrder();
        vector<T> vectorToReturn;
        int size = getSize();
        for(int i = 0; i < size; i++) {
            vectorToReturn.push_back(setAsArray[i]);
        }
    }

    /* toArray function - converts a set to an array 
    Returns: The set as an array
    Method: Call the getInOrder function */
    template <class T>
    T* Set<T>::toArray() {
        return getInOrder();
    }

    /* erase function - deletes an element from the set 
    Parameter: The value to delete
    Method: Call the delete function from RBTree, then decrement size */
    template <class T>
    void Set<T>::erase(T elementToDelete) {
        if(find(elementToDelete)) { //If the element is in the set
            remove(elementToDelete);
            --size;
        }
        else { //If it is not in the set
            std::cout << "Element is not in the set" << std::endl;
        }
    }

    /* insert function - inserts an element into the set 
    Parameters: The value of the element to insert
    Method: Overrides the Red-Black Tree's insert method to ensure no duplicate elements*/
    template <class T>
    void insert(T elementToInsert) override {
        RBTreeNode<T> *newnode = new RBTreeNode<T>(val, RED, NIL, NIL, NIL);
        RBTreeNode<T> *y = NIL;
        RBTreeNode<T> *x = root;

        while (x != NIL) {
            y = x;
            if (val < x->value){
                x = x->left;
            }
            else if (val > x->value) {
                x = x->right;
            }
            else { //val == x
                std::cout << "Set does not allow for duplicate node" << std::endl;
                delete newNode;
                return;
            }
        }
        newnode->parent = y;
        if (y == NIL) {
            root = newnode;
        }
        else if (newnode->value < y->value) {
            y->left = newnode;
        }
        else {
            y->right = newnode;
        }

        ++size;
        //  Adjust the RB tree to retain the properties.
        RBTree<T>::insertFix(newnode);
    }

    
    bool Set<T>::operator==(const Set<T> rightSide) {
        if(this.size != rightSide.size) { //If the sizes are not equal, we can skip the rest
            return false;
        }
        RBTreeNode<T> *leftNodePtr = this.root;
        RBTreeNode<T> *leftNILL = this.NIL;
        RBTreeNode<T> *rightNodePtr = rightSide.root;
        RBTreeNode<T> *rightNILL = rightSide.NIL;
        return equalsOperatorHelper(leftNodePtr, leftNILL, rightNodePtr, rightNILL);
    }
        
      
    bool Set<T>::operator!=(const Set<T> rightSide) {
        if(this.size != rightSide.size) { //If the sizes are not equal, we can skip the rest
            return true;
        }
        RBTreeNode<T> *leftNodePtr = this.root;
        RBTreeNode<T> *leftNILL = this.NIL;
        RBTreeNode<T> *rightNodePtr = rightSide.root;
        RBTreeNode<T> *rightNILL = rightSide.NIL;
        return !(equalsOperatorHelper(leftNodePtr, leftNILL, rightNodePtr, rightNILL));
    }

    /* equalsOperatorHelper - searches through the two trees in-order, and returns true if they are equal
    Parameters: lNodePtr: Pointer to current spot in left set
    lNILL: Pointer to NILL in left set
    rNodePtr: Pointer to current spot in right set
    rNILL: Pointer to NILL in right set*/
    template <class T>
    bool Set<T>::equalsOperatorHelper(RBTreeNode<T> *lNodePtr, RBTreeNode<T> *lNILL, RBTreeNode<T> *rNodePtr, RBTreeNode<T> *rNILL) {
        //Base case
        if(lNodePtr == rNILL && rNodePtr == lNILL) {
            return true;
        }

        //Else, if one is NILL and one is not, return false
        else if(lNodePtr == rNILL || rNodePtr == lNILL) {
            return false;
        }
        //Check the left subtrees for equality
        bool leftSubtreeEqual = equalsOperatorHelper(lNodePtr->left, lNILL, rNodePtr->left, rNILL);
        if(!leftSubTreeEqual) {
            return false;
        }

        //Check the current node for equality
        if (lNodePtr->value != rNodePtr->value) {
            return false;
        }

        //Check the right subtrees for equality
        bool rightSubtreeEqual = equalsOperatorHelper(lNodePtr->right, lNILL, rNodePtr->right, rNILL);
        return rightSubtreeEqual;  
    }

    /* Operator < overload - Returns whether leftSide is strict subset of rightSide
    Method: Store both sets as an array, then compare results. Could be optimized*/
    template <class T>
    bool Set<T>::operator<(const Set<T> rightSide) {
        //If leftSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this.size;
        int rightSize = rightSide.size;
        if (leftSize >= rightSize) {
            return false;
        }
        T *leftArray = this.getInOrder();
        T *rightArray = rightSide.getInOrder();
        int leftIterator = 0;
        for(int i = 0; i < rightSize, i++) {
            if(leftArray[leftIterator] == rightArray[i]) {
                leftIterator++;
            }
        }
        delete leftArray; //Freeing up memory
        delete rightArray;
        if(leftIterator == leftSize) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Operator > overload - Returns whether rightSide is strict subset of leftSide
    Method: Store both sets as an array, then compare results. Could be optimized*/
    template <class T>
    bool Set<T>::operator>(const Set<T> rightSide) {
        //If rightSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this.size;
        int rightSize = rightSide.size;
        if (leftSize <= rightSize) {
            return false;
        }
        T *leftArray = this.getInOrder();
        T *rightArray = rightSide.getInOrder();
        int rightIterator = 0;
        for(int i = 0; i < leftSize, i++) {
            if(leftArray[i] == rightArray[rightIterator]) {
                rightIterator++;
            }
        }
        delete leftArray; //Freeing up memory
        delete rightArray;
        if(rightIterator == rightSize) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Operator <= overload - Returns whether leftSide is subset of rightSide
    Method: Store both sets as an array, then compare results. Could be optimized*/
    template <class T>
    bool Set<T>::operator<=(const Set<T> rightSide) {
        int leftSize = this.size;
        int rightSize = rightSide.size;
        T *leftArray = this.getInOrder();
        T *rightArray = rightSide.getInOrder();
        int leftIterator = 0;
        for(int i = 0; i < rightSize, i++) {
            if(leftArray[leftIterator] == rightArray[i]) {
                leftIterator++;
            }
        }
        delete leftArray; //Freeing up memory
        delete rightArray;
        if(leftIterator == leftSize) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Operator > overload - Returns whether rightSide is subset of leftSide
    Method: Store both sets as an array, then compare results. Could be optimized*/
    template <class T>
    bool Set<T>::operator>=(const Set<T> rightSide) {
        int leftSize = this.size;
        int rightSize = rightSide.size;
        T *leftArray = this.getInOrder();
        T *rightArray = rightSide.getInOrder();
        int rightIterator = 0;
        for(int i = 0; i < leftSize, i++) {
            if(leftArray[i] == rightArray[rightIterator]) {
                rightIterator++;
            }
        }
        delete leftArray; //Freeing up memory
        delete rightArray;
        if(rightIterator == rightSize) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Operator + overload - returns the union of two sets 
    Method: Will make a new set equal to leftSide, then insert all elements from the rightSide by converting it
    to an array. This will still maintain the set property since duplicates cannot be inserted */
    template <class T>
    Set<T> Set<T>::operator+(const Set<T> rightSide) {
        Set<T> newSet = this;
        T *rightArray = rightSide.getInOrder();
        rightSize = rightSide.size;
        for(int i = 0; i < rightSize; i++) {
            newSet.insert(rightArray[i]);
        }
        delete rightArray; //Freeing up memory
        return newSet;
    }

    /* Operator * overload - returns the intersection of two sets
    Method: Will store the two sets as arrays, and then combine their intersections into a vector. Will then insert
    each element of that vector onto a new set */
    template <class T>
    Set<T> Set<T>::operator*(const Set<T> rightSide) {
        T *rightArray = rightSide.getInOrder();
        T *leftSide = this.getInOrder();
        int rightSize = rightSide.size;
        int leftSize = this.size;
        vector<T> newVector;
        Set<T> newSet;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < leftSize; i++) {
            if(findInArray(leftArray[i], rightSide, rightSize)) {
                newVector.pushBack(leftArray[i]);
            }
        }
    }

    /* FindInArray helper function - returns whether a given element in an array, if it exists
    Method: will iterate through a given array until the element is found, returning the index */
    template <class T>
    bool Set<T>::findInArray(T element, T *array, int arraySize) {
        for(int i = 0; i < arraySize; i++) {
            if(array[i] == element) {
                return true;
            }
        }
        return false; //Signal value stating that the element was not found
    }

    /* Operator - overload - returns the set difference 
    Method: Store the set as two arrays, then push elements into a vector if they are in
    the leftArray but not in the rightArray */
    template <class T>
    Set<T> Set<T>::operator-(const Set<T> leftSide) {
        T *rightArray = this.getInOrder();
        T *leftSide = leftSide.getInOrder();
        int rightSize = this.size;
        int leftSize = leftSide.size;
        vector<T> newVector;
        Set<T> newSet;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < rightSize; i++) {
            if(!(findInArray(left[i], rightSide, rightSize))) {
                newVector.pushBack(rightArray[i]);
            }
        }
    }

    /* Operator << overload - prints out the set on a single line */
    template <class T> 
    std::ostream& operator<<(std::ostream& os, const Set<T> set) {
        std:: cout << "{"
        RBTreeNode<T> *nodePtr = set.root;
        int size = set.size;
        bool printComma = true;
        int count = 0;
        set.displayInOrder(nodePtr, os, count, size);
        std::cout << "}" << std::endl;
    }

    /* displayInOrder helper - prints out the set */
    template<class T> 
    void Set<T>::displayInOrder(RBTreeNode *nodePtr, ostream &cout, int &count, int size) const {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
        cout << nodePtr->value;
        if(count != size-1) {
            cout << ", ";
            count++;
        }
		displayInOrder(nodePtr->right);
	}
}


#endif 