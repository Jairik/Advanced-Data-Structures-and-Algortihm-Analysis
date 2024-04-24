#ifndef MULTISET_H
#define MULTISET_H

#include "RBTree.h"
#include <vector>

/* -------------------------- Multiset Header File ---------------------------- 
   Author: JJ McCauley
   Creation Date: 4/23/24
   Last Update: 4/23/24
   Notes: Inherits properties from the Red-Black Tree. This is also very similar
   to Sets, except for a few behavior changes.
   ---------------------------------------------------------------------------- */

   template <class T>
   class Multiset : public RBTree<T> {
    //Helper functions
    private:
        int size; //Increments or decrements based on insertions
        T* getInOrder(); //Returns array of inordered elements 
        void getInOrderHelper(RBTreeNode<T> *, T *&, int); 
        bool equalsOperatorHelper(RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *, RBTreeNode<T> *);
        void getInOrderVector(RBTreeNode<T> *, RBTreeNode<T> *, vector<T> &);
        void inOrderCopy(RBTreeNode<T> *); //Helper function for assignment operator
        bool findInArray(T, T *, int);
        int countHelper(RBTreeNode<T> *, T, int &);
    
    public:
        //Constructs and deconstructors
        Multiset();
        ~Multiset();
        Multiset(Multiset &);

        //Multiset-specific functions
        void clear(); //Clears the multiset
        int getSize() const; //Gets the size of the multiset
        bool find(T); //Searches the multiset for a given element
        bool isEmpty(); //Determines if the multiset is empty
        void toVector(vector<T> &);
        void toArray(T *&);
        void erase(T);
        void insert(T) override;
        int count(T); //Returns the number of elements that specifies the parameter

        //Operator Overloads
        Multiset<T>& operator=(const Multiset<T> &);
        bool operator==(const Multiset<T> &); 
        bool operator!=(const Multiset<T> &);
        bool operator>(Multiset<T> &);
        bool operator<(Multiset<T> &);
        bool operator>=(Multiset<T> &);
        bool operator<=(Multiset<T> &);
        Multiset<T> operator+(Multiset<T> &);// Multiset union
        Multiset<T> operator*(Multiset<T> &); //Multiset intersection
        Multiset<T> operator-(Multiset<T> &); //Multiset difference
        template <class U> friend ostream& operator<<(ostream&, Multiset<T>&);
        void displayInOrder(RBTreeNode<T> *, ostream &, int &, int); //Must be public for << operator
        RBTreeNode<T> *getRoot() const; //Helper function that must be public

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
    Multiset<T>::Multiset(Multiset<T> &copy) : RBTree<T>(copy) { this->size = copy.size; }

    /* Count - returns the count of a given element 
    Paramters: The element to check for
    Method: Calls the count helper function */
    template <class T>
    int Multiset<T>::count(T element) {
        int initialCount = 0;
        return countHelper(this->root, element, initialCount);
    }

    /* countHelper - helper function to Count
    Parameters: The current RBTreeNode pointer and the element to check for
    Method: Recursively transverses to the tree in-order, incrementing and returning count*/
    template <class T>
    int Multiset<T>::countHelper(RBTreeNode<T> *nodePtr, T elementToCheck, int &count) {
        if(nodePtr != this->NIL) {
            countHelper(nodePtr->left, elementToCheck, count);
            if(nodePtr->value == elementToCheck) {
                count++;
            }
            countHelper(nodePtr->right, elementToCheck, count);
        }
        return count;
    }

    /*Overloaded Assignment Operator
    Paramters: The set to be assigned 
    Method: Clear the current tree, then copy the current one to it*/
    template <class T>
    Multiset<T>& Multiset<T>::operator=(const Multiset<T> &rightMultiset) {
        if(this == &rightMultiset) {
            return *this;
        }
        this->clear(); //clearing the current tree
        this->root = this->NIL;
        inOrderCopy(rightMultiset.root);
        this->size = rightMultiset.size; 
        return *this;
    }

    /* inOrderCopy - copy set from the given tree to the current tree 
    Method: Perform an in-order transversal and insert them into this tree */
    template <class T>
    void Multiset<T>::inOrderCopy(RBTreeNode<T> *nodePtr) {
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
        int initialIterator = 0;
        getInOrderHelper(this->root, elementArray, initialIterator); //Get the in-order array
        return elementArray; //Returns the sorted in-order array
    }

    /* getInOrderHelper function - recursively adds elements to the elementArray
    Parameters: RBTreeNode<T> nodePtr - The current pointer in the tree
    int *elementArray - the array to be changed. Will be changed by reference
    int iterator - the current point in the array
    Returns: An array of in-order elements */
    template <class T>
    void Multiset<T>::getInOrderHelper(RBTreeNode<T> *nodePtr, T *&elementArray, int iterator) {
        if (nodePtr != this->NIL) {
		    getInOrderHelper(nodePtr->left, elementArray, iterator);
		    elementArray[iterator++] = nodePtr->value;
		    getInOrderHelper(nodePtr->right, elementArray, iterator);
	    } 
    }

    /* Size function - returns the size of the tree
    Returns: the size of the set */
    template <class T>
    int Multiset<T>::getSize() const {
        return size;
    }

    /* Find function - returns whether a given element was found
    Parameter: T element - the element to search for*/
    template <class T>
    bool Multiset<T>::find(T element) {
        return this->findNode(element); //Calls function from RBTree
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
    void Multiset<T>::toVector(vector<T> &v) {
        v.clear(); //clearing the vector of all contents
        getInOrderVector(this->root, this->NIL, v);
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
    void Multiset<T>::toArray(T *&a) {
        a = getInOrder();
    }

    /* erase function - deletes an element from the set 
    Parameter: The value to delete
    Method: Call the delete function from RBTree, then decrement size */
    template <class T>
    void Multiset<T>::erase(T elementToDelete) {
        if(find(elementToDelete)) { //If the element is in the set
            this->remove(elementToDelete);
            --size;
        }
        else { //If it is not in the set
            cout << "Element is not in the set" << endl;
        }
    }

    /* insert function - inserts an element into the set 
    Parameters: The value of the element to insert 
    Method: Inserts an element into the Red-Black tree
    Notes: An override is not necessary */
    template <class T>
    void Multiset<T>::insert(T elementToInsert) {
        RBTree<T>::insert(elementToInsert);
    } 

    template <class T>
    bool Multiset<T>::operator==(const Multiset<T> &rightSide) {
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
    bool Multiset<T>::operator!=(const Multiset<T> &rightSide) {
        if(this->size != rightSide.getSize()) { //If the sizes are not equal, we can skip the rest
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
    bool Multiset<T>::operator<(Multiset<T> &rightSide) {
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
    bool Multiset<T>::operator>(Multiset<T> &rightSide) {
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
    bool Multiset<T>::operator<=(Multiset<T> &rightSide) {
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
    bool Multiset<T>::operator>=(Multiset<T> &rightSide) {
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
    Method: Makes a new multiset, converts the multisets to arrays,
    then will loop through the array and add elements as they are
    seen, ensuring only the highest freuency of each element gets added */
    template <class T>
    Multiset<T> Multiset<T>::operator+(Multiset<T>& rightSide) {
        T *leftArray = this->getInOrder();
        int leftSize = this->size;
        T *rightArray = rightSide.getInOrder();
        int rightSize = rightSide.size;
        Multiset<T> newMultiset;
        int l, r = 0; //Iterators for left and right side
        
        //Loops through the arrays until all elements have been added
        while(l <= leftSize && r <= rightSize) {
            /* If all elements of the left array have been added or the leftArray's 
            element is greater than the rightArray, add the rightArray's element*/
            if(leftArray[l] > rightArray[r] || l >= leftSize) {
                newMultiset.insert(rightArray[r]);
                newMultiset.size++;
                r++;
            }
            /* If all elements of the right array have been added or the rightArray's 
            element is greater than the leftArray, add the leftArray's element*/
            else if(leftArray[l] < rightArray[r] || r >= rightSize) {
                newMultiset.insert(leftArray[r]);
                newMultiset.size++;
                l++;
            }
            /* If is neither of these conditions, then the elements must be equal, 
            in which case we add the element then increment both iterators */
            else { 
                newMultiset.insert(rightArray[r]);
                newMultiset.size++;
                l++;
                r++;
            }
        }
        delete rightArray; //Freeing up memory
        delete leftArray;
        return newMultiset;
    }

    /* Operator * overload - returns the intersection of two sets
    Method: Will store the two sets as arrays, and then combine their intersections into a vector. Will then insert
    each element of that vector onto a new set */
    template <class T>
    Multiset<T> Multiset<T>::operator*(Multiset<T> &rightSide) {
        T *rightArray = rightSide.getInOrder();
        T *leftArray = this->getInOrder();
        int rightSize = rightSide.size;
        int leftSize = this->size;
        Multiset<T> newMultiSet;
        int l = 0, r = 0; //Getting iterator for while loop

        //Iterate through this multiset's elements
        for(int i = 0; i < leftSize; i++) {
            T element = rightArray[i];
        }
        //Loops through the arrays until all elements have been added
        while(l <= leftSize && r <= rightSize) {
            if(leftArray[l] > rightArray[r]) {
                r++;
            }
            else if(leftArray[l] < rightArray[r]) {
                l++;
            }
            else { 
                newMultiSet.insert(rightArray[r]);
                newMultiSet.size++;
                l++;
                r++;
            }
        }
        delete rightArray; //Freeing up memory
        delete leftArray;
        return newMultiSet;
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
    Method: Store the set as two arrays, then will insert elements into a 
    new set as they are seen in leftArray and not found in rightArray */
    template <class T>
    Multiset<T> Multiset<T>::operator-(Multiset<T> &rightSide) {
        T *rightArray = rightSide.getInOrder(); //Store right side as array
        int rightSize = rightSide.getSize();
        T *leftArray = this->getInOrder();
        int leftSize = this->size;
        Multiset<T> newMultiset;

        for(int i = 0; i < rightSize; i++) {
            if(!(findInArray(leftArray[i], rightArray, rightSize))) {
                newMultiset.insert(leftArray[i]);
                newMultiset.size++;
            }
        }
        return newMultiset;
    }

    /* Operator << overload - prints out the set on a single line */
    template <class T> 
    ostream& operator<<(ostream& os, Multiset<T> &set) {
        RBTreeNode<T> *nodePtr = set.getRoot();
        int size = set.getSize();
        bool printComma = true;
        int count = 0;
        os<<"{";
        set.displayInOrder(nodePtr, os, count, size);
        os<<"}";
        return os;
    }

    /* displayInOrder helper - prints out the set */
    template <class T> 
    void Multiset<T>::displayInOrder(RBTreeNode<T> *nodePtr, ostream &sysout, int &count, int size) {
        if (nodePtr != this->NIL) {
            displayInOrder(nodePtr->left, sysout, count, size);
            sysout << nodePtr->value;
            if(count != size-1) {
                sysout << ", ";
            }
            count++; sysout << " c: " << count;
            displayInOrder(nodePtr->right, sysout, count, size);
        }
    }

    /* Helper function that retreives the root from the tree */
    template <class T>
    RBTreeNode<T>* Multiset<T>::getRoot() const {
        return RBTree<T>::root;
    }

#endif