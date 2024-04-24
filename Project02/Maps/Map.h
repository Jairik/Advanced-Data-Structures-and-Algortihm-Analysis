#ifndef MAP_H
#define MAP_H

#include "RBTree.h"
#include <vector>
#include <stdexcept> //Allows us to throw errors

/* ---------------------------- Map Header File ------------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/18/24
   Notes: Inherits the Red-Black tree properties
   Unlike the set implementations, I am going to try to do everything 
   through in-order transversals in the hopes of reducing segfaults
   ---------------------------------------------------------------------------- */

template <class T, class V> //T = key
class Map : public RBTree<T, V> {
    private:
        //Helper functions
        void calculateSize(RBTreeNode<T, V> *, int &);
        void copyMap(RBTreeNode<T,V> *, RBTreeNode<T,V> *);
        bool equalsOperatorHelper(RBTreeNode<T,V> *, RBTreeNode<T,V> *,RBTreeNode<T,V> *, RBTreeNode<T,V> *, bool &);
    public:
        //Constructors 
        Map();
        ~Map();
        Map(Map<T,V> &); 

        //Map-specific functions
        void insert(T, V);
        bool isEmpty();
        void clear();
        bool find(T);
        void erase(T);
        V get(T); //Get a u value based of a T key
        void set(T, V); //Set a T to a U value
        int size(); //Different approach this time

        //Overloaded Operators
        Map<T,V> operator=(Map<T,V> &);
        bool operator==(Map<T,V> &);
        bool operator!=(Map<T,V> &);
        template<class U, class K> friend ostream& operator<<(ostream&, Map<U,K> &);
    };

    //Default constructor
    template <class T, class V>
    Map<T, V>::Map() {}

    //deconstructor
    template <class T, class V>
    Map<T, V>::~Map() {}

    /* Copy constructor - copies a given map */
    template <class T, class V>
    Map<T, V>::Map(Map<T,V> &copy) {
        //Will implement logic later
    }

    /* Overriden insert function - replaces value at duplicate key */
    template <class T, class V>
    void Map<T, V>::insert(T newKey, V val) {
        RBTreeNode<T, V> *newnode = new RBTreeNode<T, V>(newKey, val, RED, NIL, NIL, NIL);
        RBTreeNode<T, V> *y = NIL;
        RBTreeNode<T, V> *x = root;

        while (x != NIL) {
            y = x;
            if (newKey < x->key)
                x = x->left;
            else if(newKey > x->key)
                x = x->right;
            else //keys must be equal
                x->value = val; //replace current value
                return;
        }
        newnode->parent = y;
        if (y == NIL)
            root = newnode;
        else if (newnode->value < y->value)
            y->left = newnode;
        else
            y->right = newnode;

        // Adjust the RB tree to retain the properties.
        insertFix(newnode);
    }

    /* isEmpty - will return whether the map is empty */
    template <class T, class V>
    bool Map<T, V>::isEmpty() {
        return(this->root == this->NILL);
    }

    /* find - will return whether a given key is in the map */
    template <class T, class V>
    bool Map<T, V>::find(T key) {
        findNode(key); //Call the RBTree method to find the given key
    }

    /* erase - will remove a given key off the map*/
    template <class T, class V>
    void Map<T, V>::erase(T key) {
        remove(key);
    }

    /* size - will return the size of the map
    method: call the helper function */
    template <class T, class V>
    int Map<T, V>::size() {
        int size = 0;
        calculateSize(this->root, size); //changes by reference
        return size;
    }

    /* calculateSize - helper function that finds the size
    Method: Perform an in-order transversal and increment size
    everytime a unique node is seen */
    template <class T, class V>
    void Map<T, V>::calculateSize(RBTreeNode<T, V> *nodePtr, int &size) {
        if (nodePtr != this->NIL) {
            calculateSize(nodePtr->right, size);
            size++; //As the node is found, increment size
            calculateSize(nodePtr->right, size);
        }
    }

    /* get - will return the value of the given key */
    template <class T, class V>
    V Map<T,V>::get(T findKey) {
        RBTreeNode<T,V> *nodePtr = this->root;
        while (nodePtr != this->NIL) {
            if (findKey < x->key)
                x = x->left;
            else if(findKey > x->key)
                x = x->right;
            else //keys must be equal
                return x->value;
        }
        //If key was not found, exception is thrown
        throw out_of_range("Key was not found in the map");
    }

    /* set - will insert a given key and value*/
    template <class T, class V>
    void Map<T,V>::set(T newKey, V val) {
        insert(newKey, val);
    }

    /* clear - clears the current map */
    template <class T, class V>
    void Map<T,V>::clear() {
        destroySubTree(this->root);
    }

    /* Assignment operator overload */
    template <class T, class V>
    Map<T, V> Map<T,V>::operator=(Map<T,V> &rightMap) {
        clear();
        copyMap(rightMap->root, rightMap->NIL);
        return *this;
    }

    /* copyMap - helper function that copies one map to another 
    Method: In-order transversal through the right Map*/
    template <class T, class V>
    void Map<T,V>::copyMap(RBTreeNode<T,V> *rNodePtr, RBTreeNode<T,V> *rNILPtr) {
        if(rNodePtr != rNILPtr) {
            copy(rNodePtr->left, rNILPtr);
            this->insert(rNodePtr->key, rNodePtr->value);
            copy(rNodePtr->right, rNILPtr);
        }
    }

    /* == operator overload - returns if the two maps are equal 
    Method: Calls helper function */
    template <class T, class V>
    bool Map<T,V>::operator==(Map<T,V> &rightMap) {
        bool allEqual = true;
        equalsOperatorHelper(this->root, this->NIL, rightMap->root, this->NIL, allEqual);
        return allEqual;        
    }

    /* != operator overload - returns if the two maps are not equal 
    Method: Calls helper function */
    template <class T, class V>
    bool Map<T,V>::operator!=(Map<T,V> &rightMap) {
        bool allEqual = true;
        equalsOperatorHelper(this->root, this->NIL, rightMap->root, this->NIL, allEqual);
        return !allEqual;
    }

    /* equalsOperatorHelper - modified boolean value to indicate
    if the two maps are equal
    Method: In-order transversal of two maps */
    template <class T, class V>
    bool Map<T,V>::equalsOperatorHelper(RBTreeNode<T,V> *lNodePtr, RBTreeNode<T,V> *lNILPtr,RBTreeNode<T,V> *rNodePtr, RBTreeNode<T,V> *rNILPtr, bool &areEqual) {
        if(rNodePtr != rNILPtr) {
            equalsOperatorHelper(lNodePtr->left, lNILPtr, rNodePtr->left, rNILPtr, areEqual);
            if(lNodePtr->key != rNodePtr->right || lNodePtr->value != rNodePtr->value) {
                areEqual = fasle;
                return; //Start exiting out of the function
            }
            equalsOperatorHelper(lNodePtr->right, lNILPtr, rNodePtr->right, rNILPtr, areEqual);
        }
    }

    

#endif