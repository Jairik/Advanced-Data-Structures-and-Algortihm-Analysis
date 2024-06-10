#ifndef SET_H
#define SET_H

#include "RBTree.h"
#include <vector>
#include <iostream>
using namespace std; //Simplifying

/* ---------------------------- Set Header File ---------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/24/24
   Notes: Inherits properties from the Red-Black Tree
   ---------------------------------------------------------------------------- */

   template <class T>
   class Set : public RBTree<T> {

    //Helper functions
    private:
        int size; //Increments or decrements based on insertions
        T* getInOrder(); //Returns array of inordered elements 
        void getInOrderHelper(RBTreeNode<T> *, RBTreeNode<T> *, T *&, int &); 
        bool equalsOperatorHelper(RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *);
        void getInOrderVector(RBTreeNode<T> *, RBTreeNode<T> *, vector<T> &);
        void displayInOrder(RBTreeNode<T> *, RBTreeNode<T> *, ostream &, int &);
        bool findInArray(T, T *, int);
        void inOrderCopy(RBTreeNode<T> *);
        void copySet(RBTreeNode<T> *, RBTreeNode<T> *);
    
    public:
        //Constructs and deconstructors
        Set();
        ~Set();
        Set(Set<T> &);

        //Set-specific functions
        void clear(); //Clears the set
        int getSize() const; //Gets the size of the set
        bool find(T); //Searches the set for a given element
        bool isEmpty(); //Determines if the set is empty
        void toVector(vector<T> &);
        void toArray(T* &);
        void erase(T);
        void insert(T) override;

        //Operator Overloads
        Set<T>& operator=(Set<T> &);
        bool operator==(const Set<T>); 
        bool operator!=(const Set<T>);
        bool operator>(Set<T>);
        bool operator<(Set<T>);
        bool operator>=(Set<T>);
        bool operator<=(Set<T>);
        Set<T> operator+(Set<T>); //Set union
        Set<T> operator*(Set<T>); //Set intersection
        Set<T> operator-(Set<T>); //Set difference
        template <class U> friend ostream& operator<<(ostream&, Set<U> &);

   };

    //Default Constructor
    template <class T> 
    Set<T>::Set() { size = 0; }

    //Default Deconstructor - Automatically called
    template <class T>
    Set<T>::~Set() { size = 0; }

    /*Copy Constructor - Copies a given Set
    Parameters: The set to be copied 
    Notes: Will automatically call the RBTree copy constructor that I added */
    template <class T>
    Set<T>::Set(Set<T> &copy) : RBTree<T>(copy) { this->size = copy.size; }

    /*Overloaded Assignment Operator
    Paramters: The set to be assigned 
    Method: Clear the current tree, then copy the current one to it*/
    template <class T>
    Set<T>& Set<T>::operator=(Set<T> &rightSet) {
        clear();
        copySet(rightSet.root, rightSet.NIL);
        return *this;
    }

    /*copySet - helper function that copies one set to another 
    Method: In-order transversal through the right set*/
    template <class T>
    void Set<T>::copySet(RBTreeNode<T> *rNodePtr, RBTreeNode<T> *rNILPtr) {
        if(rNodePtr != rNILPtr) {
            copySet(rNodePtr->left, rNILPtr);
            this->insert(rNodePtr->value);
            copySet(rNodePtr->right, rNILPtr);
        }
    }

    /* inOrderCopy - copy set from the given tree to the current tree 
    Method: Perform an in-order transversal and insert them into this tree */
    template <class T>
    void Set<T>::inOrderCopy(RBTreeNode<T> *nodePtr) {
        if(nodePtr != this->NIL) {
            inOrderCopy(nodePtr->left);
            this->insert(nodePtr->value);
            inOrderCopy(nodePtr->right);
        }
    }

    /* Clear function - clears the current tree of all elements 
    Parameters: N/A
    Method: Destroy the current subtree */
    template <class T>
    void Set<T>::clear() {
        RBTree<T>::destroySubTree(this->root);
        size = 0; 
    }

    /* getInOrder function - returns an array of in-order elements
    Parameters: N/A
    Returns: An array of in-order elements */
    template <class T>
    T* Set<T>::getInOrder() {
        int numElements = getSize(); //Get the number of elements to allocate array
        T *elementArray = new T[numElements]; //Allocating space for elements
        int iterator = 0;
        getInOrderHelper(this->root, this->NIL, elementArray, iterator); //Get the in-order array
        return elementArray; //Returns the sorted in-order array
    }

    /* getInOrderHelper function - recursively adds elements to the elementArray
    Parameters: RBTreeNode<T> nodePtr - The current pointer in the tree
    int *elementArray - the array to be changed. Will be changed by reference
    int iterator - the current point in the array
    Returns: An array of in-order elements */
    template <class T>
    void Set<T>::getInOrderHelper(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr, T *&elementArray, int &iterator) {
        if (nodePtr != nilPtr) {
		    getInOrderHelper(nodePtr->left, nilPtr, elementArray, iterator);
		    elementArray[iterator++] = nodePtr->value;
		    getInOrderHelper(nodePtr->right, nilPtr, elementArray, iterator);
	    } 
    }

    /* Size function - returns the size of the tree
    Returns: the size of the set */
    template <class T>
    int Set<T>::getSize() const{
        return size;
    }

    /* Find function - returns whether a given element was found
    Parameter: T element - the element to search for*/
    template <class T>
    bool Set<T>::find(T element) {
        return RBTree<T>::findNode(element); //Calls function from RBTree
    }

    /* isEmpty function - returns if the set is empty */
    template <class T>
    bool Set<T>::isEmpty() {
        return(this->root  == this->NIL); //Returns if the root is found
    }

    /* toVector function - puts a set into a vector
    Parameters: The vector to be set as the set
    Method: Call the getInOrder function on the vector */
    template <class T>
    void Set<T>::toVector(vector<T> &v) {
        v.clear(); //clearing the vector of all contents
        getInOrderVector(this->root, this->NIL, v);
    }

    template <class T>
    void Set<T>::getInOrderVector(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr, vector<T> &vector) {
        if(nodePtr != nilPtr) {
            getInOrderVector(nodePtr->left, nilPtr, vector);
            vector.push_back(nodePtr->value);
            getInOrderVector(nodePtr->right, nilPtr, vector);
        }
    }

    /* toArray function - converts a set to an array 
    Returns: The set as an array
    Method: Call the getInOrder function */
    template <class T>
    void Set<T>::toArray(T *&a) {
        a = getInOrder();
    }

    /* erase function - deletes an element from the set 
    Parameter: The value to delete
    Method: Call the delete function from RBTree, then decrement size */
    template <class T>
    void Set<T>::erase(T elementToDelete) {
        if(find(elementToDelete)) { //If the element is in the set
            this->remove(elementToDelete);
            --size;
        }
    }

    /* insert function - inserts an element into the set 
    Parameters: The value of the element to insert
    Method: Overrides the Red-Black Tree's insert method to ensure no duplicate elements*/
    template <class T>
    void Set<T>::insert(T elementToInsert) {
        RBTreeNode<T> *newNode = new RBTreeNode<T>(elementToInsert, this->getRed(), this->NIL, this->NIL, this->NIL);
        
        RBTreeNode<T> *y = this->NIL;
        RBTreeNode<T> *x = this->root;

        while (x != this->NIL) {
            y = x;
            if (elementToInsert < x->value){
                x = x->left;
            }
            else if (elementToInsert > x->value) {
                x = x->right;
            }
            else { //elementToInsert == x
                delete newNode;
                return;
            }
        }
        newNode->parent = y;
        if (y == this->NIL) {
            this->root = newNode;
        }
        else if (newNode->value < y->value) {
            y->left = newNode;
        }
        else {
            y->right = newNode;
        }

        size++; 
        //  Adjust the RB tree to retain the properties.
        RBTree<T>::insertFix(newNode);
    }

    template <class T>
    bool Set<T>::operator==(const Set<T> rightSide) {
        if(this->size != rightSide.size) { //If the sizes are not equal, we can skip the rest
            return false;
        }
        RBTreeNode<T> *leftNodePtr = this->root;
        RBTreeNode<T> *leftNIL = this->NIL;
        RBTreeNode<T> *rightNodePtr = rightSide.root;
        RBTreeNode<T> *rightNIL = rightSide.NIL;
        return equalsOperatorHelper(leftNodePtr, leftNIL, rightNodePtr, rightNIL);
    }
        
    template <class T>
    bool Set<T>::operator!=(const Set<T> rightSide) {
        if(this->size != rightSide.size) { //If the sizes are not equal, we can skip the rest
            return true;
        }
        RBTreeNode<T> *leftNodePtr = this->root;
        RBTreeNode<T> *leftNIL = this->NIL;
        RBTreeNode<T> *rightNodePtr = rightSide.root;
        RBTreeNode<T> *rightNIL = rightSide.NIL;
        return !(equalsOperatorHelper(leftNodePtr, leftNIL, rightNodePtr, rightNIL));
    }

    /* equalsOperatorHelper - searches through the two trees in-order, and returns true if they are equal
    Parameters: lNodePtr: Pointer to current spot in left set
    lNIL: Pointer to NIL in left set
    rNodePtr: Pointer to current spot in right set
    rNIL: Pointer to NIL in right set*/
    template <class T>
    bool Set<T>::equalsOperatorHelper(RBTreeNode<T> *lNodePtr, RBTreeNode<T> *lNIL, RBTreeNode<T> *rNodePtr, RBTreeNode<T> *rNIL) {
        //Base case
        if(lNodePtr == rNIL && rNodePtr == lNIL) {
            return true;
        }

        //Else, if one is NIL and one is not, return false
        else if(lNodePtr == rNIL || rNodePtr == lNIL) {
            return false;
        }
        //Check the left subtrees for equality
        bool leftSubtreeEqual = equalsOperatorHelper(lNodePtr->left, lNIL, rNodePtr->left, rNIL);
        if(!leftSubtreeEqual) {
            return false;
        }

        //Check the current node for equality
        if (lNodePtr->value != rNodePtr->value) {
            return false;
        }

        //Check the right subtrees for equality
        bool rightSubtreeEqual = equalsOperatorHelper(lNodePtr->right, lNIL, rNodePtr->right, rNIL);
        return rightSubtreeEqual;  
    }

    /* Operator < overload - Returns whether leftSide is strict subset of rightSide
    Method: Store both sets as an array, then compare results. Could be optimized*/
    template <class T>
    bool Set<T>::operator<(Set<T> rightSide) {
        //If leftSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this->size;
        int rightSize = rightSide.size;
        if (leftSize >= rightSize) {
            return false;
        }
        T *leftArray = this->getInOrder();
        T *rightArray = rightSide.getInOrder();
        int leftIterator = 0;
        for(int i = 0; i < rightSize; i++) {
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
    bool Set<T>::operator>(Set<T> rightSide) {
        //If rightSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this->size;
        int rightSize = rightSide.size;
        if (leftSize <= rightSize) {
            return false;
        }
        T *leftArray = this->getInOrder();
        T *rightArray = rightSide.getInOrder();
        int rightIterator = 0;
        for(int i = 0; i < leftSize; i++) {
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
    bool Set<T>::operator<=(Set<T> rightSide) {
        int leftSize = this->size;
        int rightSize = rightSide.size;
        T *leftArray = this->getInOrder();
        T *rightArray = rightSide.getInOrder();
        int leftIterator = 0;
        for(int i = 0; i < rightSize; i++) {
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
    bool Set<T>::operator>=(Set<T> rightSide) {
        int leftSize = this->size;
        int rightSize = rightSide.size;
        T *leftArray = this->getInOrder();
        T *rightArray = rightSide.getInOrder();
        int rightIterator = 0;
        for(int i = 0; i < leftSize; i++) {
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
    Set<T> Set<T>::operator+(Set<T> rightSide) {
        Set<T> newSet = *this;
        T *rightArray = rightSide.getInOrder();
        int rightSize = rightSide.size;
        for(int i = 0; i < rightSize; i++) {
            newSet.insert(rightArray[i]);
            newSet.size++;
        }
        delete rightArray; //Freeing up memory
        return newSet;
    }

    /* Operator * overload - returns the intersection of two sets
    Method: Will store the two sets as arrays, and then combine their intersections into a vector. Will then insert
    each element of that vector onto a new set */
    template <class T>
    Set<T> Set<T>::operator*(Set<T> rightSide) {
        T *rightArray = rightSide.getInOrder();
        T *leftArray = this->getInOrder();
        int rightSize = rightSide.size;
        int leftSize = this->size;
        Set<T> newSet;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < leftSize; i++) {
            if(findInArray(leftArray[i], rightArray, rightSize)) {
                newSet.insert(leftArray[i]);
                newSet.size++;
            }
        }
        return newSet;
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
    Method: Store the set as two arrays, then will insert elements into a 
    new set as they are seen in leftArray and not found in rightArray */
    template <class T>
    Set<T> Set<T>::operator-(Set<T> rightSide) {
        T *rightArray = rightSide.getInOrder();
        T *leftArray = this->getInOrder();
        int rightSize = rightSide.size;
        int leftSize = this->size;
        Set<T> newSet;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < rightSize; i++) {
            if(!(findInArray(leftArray[i], rightArray, rightSize))) {
                newSet.insert(leftArray[i]);
            }
        }
        return newSet;
    }

    /* Operator << overload - prints out the set on a single line */
    template <class T> 
    ostream& operator<<(ostream& os, Set<T> &set) {
        os << "{";
        RBTreeNode<T> *nodePtr = set.root;
        int count = 0;
        set.displayInOrder(nodePtr, set.NIL, os, count);
        os << "}\n";
        return os;
    }

    /* displayInOrder helper - prints out the set */
    template<class T> 
    void Set<T>::displayInOrder(RBTreeNode<T> *nodePtr, RBTreeNode<T> *NILPtr, ostream &sysout, int &count) {
        if(nodePtr != NILPtr) {
            displayInOrder(nodePtr->left, NILPtr, sysout, count);
            sysout << nodePtr->value;
            if(count != this->size) {
                sysout << ", ";
                count++;
            }
            displayInOrder(nodePtr->right, NILPtr, sysout, count);
        }
    }


#endif 