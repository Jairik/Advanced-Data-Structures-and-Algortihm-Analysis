#ifndef MULTISET_H
#define MULTISET_H

#include "RBTree.h"
#include <vector>

/* -------------------------- Multiset Header File ---------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/18/24
   Notes: Inherits properties from the Red-Black Tree
   ---------------------------------------------------------------------------- */

   template <class T>
   class Multiset : public RBTree<T> {
    //Helper functions
    private:
        int size; //Increments or decrements based on insertions
        T* getInOrder(); //Returns array of inordered elements 
        void getInOrderHelper(RBTreeNode<T> *, RBTreeNode<T> *, T *&, int); //Helper function that recursively iterates through the tree in-order
        void sizeHelper(int &); //Helper function that transverses through the tree and increments size
        bool equalsOperatorHelper(RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *);
        void getInOrderVector(RBTreeNode<T> *, RBTreeNode<T> *, vector<T> &);
        void displayInOrder(RBTreeNode<T> *, ostream &, int &, int);
        bool findInArray(T, T *, int);
        int countHelper(RBTreeNode<T> *, T, int &);
    
    public:
        //Constructs and deconstructors
        Multiset();
        ~Multiset();
        Multiset(const Multiset &);

        //Multiset-specific functions
        void clear(); //Clears the multiset
        int getSize(); //Gets the size of the multiset
        bool find(T); //Searches the multiset for a given element
        bool isEmpty(); //Determines if the multiset is empty
        vector<T> toVector();
        T* toArray();
        void erase(T);
        void insert(T) override;
        int count(T); //Returns the number of elements that specifies the parameter

        //Operator Overloads
        Multiset<T>& operator=(const Multiset<T> &);
        bool operator==(const Multiset<T>); 
        bool operator!=(const Multiset<T>);
        bool operator>(const Multiset<T>);
        bool operator<(const Multiset<T>);
        bool operator>=(const Multiset<T>);
        bool operator<=(const Multiset<T>);
        Multiset<T>& operator+(const Multiset<T>); //Multiset union
        Multiset<T>& operator*(const Multiset<T>); //Multiset intersection
        Multiset<T>& operator-(const Multiset<T>); //Multiset difference
        template <class U> friend ostream& operator<<(ostream&, const Multiset<T>&);

   };

    //Default Constructor
    template <class T> 
    Multiset<T>::Multiset() { size = 0; }

    //Default Deconstructor - Automatically called
    template <class T>
    Multiset<T>::~Multiset() { size = 0; }

    /*Copy Constructor - Copies a given Multiset
    Parameters: The set to be copied 
    Notes: Will automatically call the RBTree copy constructor that I added */
    template <class T>
    Multiset<T>::Multiset(const Multiset<T> &copy) : RBTree<T>(copy) { this.size = copy.size; }

    /* Count - returns the count of a given element 
    Paramters: The element to check for
    Method: Calls the count helper function */
    template <class T>
    int Multiset<T>::count(T element) {
        int count = 0;
        count = countHelper(this->root, element, count);
        return count;
    }

    /* countHelper - helper function to Count
    Parameters: The current RBTreeNode pointer and the element to check for
    Method: Recursively transverses to the tree in-order, incrementing and returning count*/
    template <class T>
    int Multiset<T>::countHelper(RBTreeNode<T> *nodePtr, T elementToCheck, int &count) {
        
    }

    /*Overloaded Assignment Operator
    Paramters: The set to be assigned 
    Method: Clear the current tree, then copy the current one to it*/
    template <class T>
    Multiset<T>& Multiset<T>::operator=(const Multiset<T> &rightMultiset) {
        clear(); 
        RBTreeNode<T> *tempPtr; //Temp ptr so the copy function can return something
        tempPtr = this.copy(rightMultiset.root, rightMultiset.NIL);
        this.size = rightMultiset.size; //Multisetting the sizes to be equal
        return *this; //Return the current tree
    }

    /* Clear function - clears the current tree of all elements 
    Parameters: N/A
    Method: Destroy the current subtree */
    template <class T>
    void Multiset<T>::clear() {
        this->destroySubTree(this->root);
        this->root = this->NIL;
        size = 0; 
    }

    /* getInOrder function - returns an array of in-order elements
    Parameters: N/A
    Returns: An array of in-order elements */
    template <class T>
    T* Multiset<T>::getInOrder() {
        int numElements = getSize(); //Get the number of elements to allocate array
        T *elementArray = new T[numElements]; //Allocating space for elements
        getInOrderHelper(this->root, this->NIL, elementArray, 0); //Get the in-order array
        return elementArray; //Returns the sorted in-order array
    }

    /* getInOrderHelper function - recursively adds elements to the elementArray
    Parameters: RBTreeNode<T> nodePtr - The current pointer in the tree
    int *elementArray - the array to be changed. Will be changed by reference
    int iterator - the current point in the array
    Returns: An array of in-order elements */
    template <class T>
    void Multiset<T>::getInOrderHelper(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr, T *&elementArray, int iterator) {
        if (nodePtr != nilPtr) {
		    getInOrderHelper(nodePtr->left);
		    elementArray[iterator++] = nodePtr->value;
		    getInOrderHelper(nodePtr->right);
	    } 
    }

    /* Size function - returns the size of the tree
    Returns: the size of the set */
    template <class T>
    int Multiset<T>::getSize() {
        return size;
    }

    /* Find function - returns whether a given element was found
    Parameter: T element - the element to search for*/
    template <class T>
    bool Multiset<T>::find(T element) {
        return findNode(element); //Calls function from RBTree
    }

    /* isEmpty function - returns if the set is empty */
    template <class T>
    bool Multiset<T>::isEmpty() {
        return(this->root  == this->NIL); //Returns if the root is found
    }

    /* toVector function - converts a set to a vector 
    Returns: The set as a vector
    Method: Call the getInOrder function, then convert to a vector */
    template <class T>
    vector<T> Multiset<T>::toVector() {
        vector<T> vectorToReturn;
        getInOrderVector(this->root, this->NIL, vectorToReturn);
        return vectorToReturn;
    }

    template <class T>
    void Multiset<T>::getInOrderVector(RBTreeNode<T> *nodePtr, RBTreeNode<T> *nilPtr, vector<T> &vector) {
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
    T* Multiset<T>::toArray() {
        return getInOrder();
    }

    /* erase function - deletes an element from the set 
    Parameter: The value to delete
    Method: Call the delete function from RBTree, then decrement size */
    template <class T>
    void Multiset<T>::erase(T elementToDelete) {
        if(find(elementToDelete)) { //If the element is in the set
            remove(elementToDelete);
            --size;
        }
        else { //If it is not in the set
            cout << "Element is not in the set" << endl;
        }
    }

    /* insert function - inserts an element into the set 
    Parameters: The value of the element to insert
    Method: Overrides the Red-Black Tree's insert method to ensure no duplicate elements*/
    template <class T>
    void Multiset<T>::insert(T elementToInsert) {
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
                cout << "Multiset does not allow for duplicate node" << endl;
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

        this->size++;
        //  Adjust the RB tree to retain the properties.
        RBTree<T>::insertFix(newNode);
    }

    template <class T>
    bool Multiset<T>::operator==(const Multiset<T> rightSide) {
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
    bool Multiset<T>::operator!=(const Multiset<T> rightSide) {
        if(this.size != rightSide.size) { //If the sizes are not equal, we can skip the rest
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
    bool Multiset<T>::equalsOperatorHelper(RBTreeNode<T> *lNodePtr, RBTreeNode<T> *lNIL, RBTreeNode<T> *rNodePtr, RBTreeNode<T> *rNIL) {
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
    bool Multiset<T>::operator<(const Multiset<T> rightSide) {
        //If leftSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this.size;
        int rightSize = rightSide.size;
        if (leftSize >= rightSize) {
            return false;
        }
        T *leftArray = this.getInOrder();
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
    bool Multiset<T>::operator>(const Multiset<T> rightSide) {
        //If rightSide size is equal or greater, then it cannot be a strict subset and we can skip remaining steps
        int leftSize = this.size;
        int rightSize = rightSide.size;
        if (leftSize <= rightSize) {
            return false;
        }
        T *leftArray = this.getInOrder();
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
    bool Multiset<T>::operator<=(const Multiset<T> rightSide) {
        int leftSize = this.size;
        int rightSize = rightSide.size;
        T *leftArray = this.getInOrder();
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
    bool Multiset<T>::operator>=(const Multiset<T> rightSide) {
        int leftSize = this.size;
        int rightSize = rightSide.size;
        T *leftArray = this.getInOrder();
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
    Multiset<T> &Multiset<T>::operator+(const Multiset<T> rightSide) {
        Multiset<T> newMultiset = this;
        T *rightArray = rightSide.getInOrder();
        int rightSize = rightSide.size;
        for(int i = 0; i < rightSize; i++) {
            newMultiset.insert(rightArray[i]);
        }
        delete rightArray; //Freeing up memory
        return newMultiset;
    }

    /* Operator * overload - returns the intersection of two sets
    Method: Will store the two sets as arrays, and then combine their intersections into a vector. Will then insert
    each element of that vector onto a new set */
    template <class T>
    Multiset<T> &Multiset<T>::operator*(const Multiset<T> rightSide) {
        T *rightArray = rightSide.getInOrder();
        T *leftArray = this.getInOrder();
        int rightSize = rightSide.size;
        int leftSize = this.size;
        vector<T> newVector;
        Multiset<T> newMultiset;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < leftSize; i++) {
            if(findInArray(leftArray[i], rightArray, rightSize)) {
                newVector.pushBack(leftArray[i]);
            }
        }
    }

    /* FindInArray helper function - returns whether a given element in an array, if it exists
    Method: will iterate through a given array until the element is found, returning the index */
    template <class T>
    bool Multiset<T>::findInArray(T element, T *array, int arraySize) {
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
    Multiset<T>& Multiset<T>::operator-(const Multiset<T> leftSide) {
        T *rightArray = this.getInOrder();
        T *leftArray = leftSide.getInOrder();
        int rightSize = this.size;
        int leftSize = leftSide.size;
        vector<T> newVector;
        Multiset<T> newMultiset;
        int i = 0; //Getting iterator for while loop
        for(int i = 0; i < rightSize; i++) {
            if(!(findInArray(left[i], rightArray, rightSize))) {
                newVector.pushBack(rightArray[i]);
            }
        }
    }

    /* Operator << overload - prints out the set on a single line */
    template <class T> 
    ostream& operator<<(ostream& os, const Multiset<T> set) {
         cout << "{";
        RBTreeNode<T> *nodePtr = set.root;
        int size = set.size;
        bool printComma = true;
        int count = 0;
        set.displayInOrder(nodePtr, os, count, size);
        cout << "}" << endl;
        return os;
    }

    /* displayInOrder helper - prints out the set */
    template<class T> 
    void Multiset<T>::displayInOrder(RBTreeNode<T> *nodePtr, ostream &sysout, int &count, int size) {
	if (nodePtr) {
		displayInOrder(nodePtr->left);
        sysout << nodePtr->value;
        if(count != size-1) {
            sysout << ", ";
            count++;
        }
		displayInOrder(nodePtr->right);
	}
}

#endif