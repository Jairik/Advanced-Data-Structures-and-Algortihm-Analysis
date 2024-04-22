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
        boolean operator==(const Set<T>); 
        boolean operator!=(const Set<T>);

    private:
        int size; //Increments or decrements based on insertions
        T *getInorder(); //Returns array of inordered elements 
        void getInOrderHelper(RBTreeNode<T>, T *&, int) //Helper function that recursively iterates through the tree in-order
        void sizeHelper(int &); //Helper function that transverses through the tree and increments size
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
    void Set<T>::clear() {
        destroySubTree(root);
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
        for(int i = size; i < 0; i--) {
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
    template <class t>
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
        insertFix(newnode);
    }

    
    boolean Set<T>::operator==(const Set<T> rightSide) {
        if(this.size != rightSide.size) { //If the sizes are not equal, we can skip the rest
            return false;
        }
        RBTreeNode<T> *leftNodePtr = this.root;
        RBTreeNode<T> *leftNILL = this.NIL;
        RBTreeNode<T> *rightNodePtr = rightSide.root;
        RBTreeNode<T> *rightNILL = rightSide.NIL;
        return equalsOperatorHelper(leftNodePtr, leftNILL, rightNodePtr, rightNILL);
    }
        
      
    boolean Set<T>::operator!=(const Set<T> rightSide) {
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
    boolean Set<T>::equalsOperatorHelper(RBTreeNode<T> *lNodePtr, RBTreeNode<T> *lNILL, RBTreeNode<T> *rNodePtr, RBTreeNode<T> *lNILL) {
        if (lnodePtr) {
		    getInOrderHelperInOrder(nodePtr->left);
		    elementArray[iterator++] = nodePtr->value;
		    displayInOrder(nodePtr->right);
	    } 
    }


#endif 