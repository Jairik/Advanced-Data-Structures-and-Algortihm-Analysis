#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "RBTree.h"
#include <vector>
#include <string> //for demo

/* -------------------------- Multimap Header File ---------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/24/24
   Notes: Inherits the Red-Black tree properties
   ---------------------------------------------------------------------------- */

template <class T, class V> //T = key, V = value
class Multimap : public RBTree<T,V> {
    private:
        //Helper functions
        void calculateSize(RBTreeNode<T, V> *, int &);
        void copyMultimap(RBTreeNode<T,V> *, RBTreeNode<T,V> *);
        bool equalsOperatorHelper(RBTreeNode<T,V> *, RBTreeNode<T,V> *,RBTreeNode<T,V> *, RBTreeNode<T,V> *, bool &);
        void inOrderDisplay(RBTreeNode<T,V> *, RBTreeNode<T,V> *, ostream &, int &);

    public:
        //Constructors 
        Multimap();
        ~Multimap();

        //Multimap-specific functions
        void insert(T, V);
        bool isEmpty();
        void clear();
        bool find(T);
        void erase(T);
        vector<V> get(T); 
        void set(T, V); 
        int size(); 

        //Overloaded Operators
        Multimap<T,V> operator=(Multimap<T,V> &);
        bool operator==(Multimap<T,V> &);
        bool operator!=(Multimap<T,V> &);
        template<class U, class K> friend ostream& operator<<(ostream&, Multimap<U,K> &);
   };

   //Default constructor
    template <class T, class V>
    Multimap<T,V>::Multimap() {}

    //deconstructor
    template <class T, class V>
    Multimap<T,V>::~Multimap() {}

    /* Overriden insert function - appeneds value at duplicate key */
    template <class T, class V>
    void Multimap<T, V>::insert(T newKey, V val) {
        RBTreeNode<T, V> *newnode = new RBTreeNode<T, V>(newKey, val, RED, this->NIL, this->NIL, this->NIL);
        RBTreeNode<T, V> *y = this->NIL;
        RBTreeNode<T, V> *x = this->root;

        while (x != this->NIL) {
            y = x;
            if (newKey < x->key)
                x = x->left;
            else if(newKey > x->key)
                x = x->right;
            else {//keys must be equal - append values
                x->value.push_back(val);
                delete newnode;
                return;
            }
        }
        newnode->parent = y;
        if (y == this->NIL)
            this->root = newnode;
        else if (newnode->key < y->key)
            y->left = newnode;
        else
            y->right = newnode;

        // Adjust the RB tree to retain the properties.
        this->insertFix(newnode);
    }

    /* isEmpty - will return whether the map is empty */
    template <class T, class V>
    bool Multimap<T, V>::isEmpty() {
        return(this->root == this->NIL);
    }

    /* find - will return whether a given key is in the map */
    template <class T, class V>
    bool Multimap<T, V>::find(T key) {
        return RBTree<T,V>::findNode(key); //Call the RBTree method to find the given key
    }

    /* erase - will remove a given key off the map*/
    template <class T, class V>
    void Multimap<T, V>::erase(T key) {
        RBTree<T,V>::remove(key);
    }

    /* size - will return the size of the map
    method: call the helper function */
    template <class T, class V>
    int Multimap<T, V>::size() {
        int size = 0;
        calculateSize(this->root, size); //changes by reference
        return size;
    }

    /* calculateSize - helper function that finds the size
    Method: Perform an in-order transversal and increment size
    everytime a unique node is seen */
    template <class T, class V>
    void Multimap<T, V>::calculateSize(RBTreeNode<T, V> *nodePtr, int &size) {
        if (nodePtr != this->NIL) {
            calculateSize(nodePtr->right, size);
            size++; //As the node is found, increment size
            calculateSize(nodePtr->right, size);
        }
    }

    /* get - will return the value of the given key */
    template <class T, class V>
    vector<V> Multimap<T,V>::get(T findKey) {
        if(!find(findKey)) {
            //If key was not found, exception is thrown
            throw out_of_range("Key was not found in the map");
        }
        RBTreeNode<T,V> *f = RBTree<T,V>::findNodeHelper(findKey);
        return f->value; //returns the vector
    }

    /* set - will insert a given key and value*/
    template <class T, class V>
    void Multimap<T,V>::set(T newKey, V val) {
        insert(newKey, val);
    }

    /* clear - clears the current multimap */
    template <class T, class V>
    void Multimap<T,V>::clear() {
        RBTree<T,V>::destroySubTree(this->root);
    }

    /* Assignment operator overload */
    template <class T, class V>
    Multimap<T, V> Multimap<T,V>::operator=(Multimap<T,V> &rightMultimap) {
        clear();
        copyMultimap(rightMultimap.root, rightMultimap.NIL);
        return *this;
    }

    /* copyMultimap - helper function that copies one map to another 
    Method: In-order transversal through the right Multimap*/
    template <class T, class V>
    void Multimap<T,V>::copyMultimap(RBTreeNode<T,V> *rNodePtr, RBTreeNode<T,V> *rNILPtr) {
        if(rNodePtr != rNILPtr) {
            copyMultimap(rNodePtr->left, rNILPtr);
            for(int i = 0; i < rNodePtr->value.size(); i++) {
                this->insert(rNodePtr->key, rNodePtr->value[i]);
            }
            copyMultimap(rNodePtr->right, rNILPtr);
        }
    }

    /* == operator overload - returns if the two maps are equal 
    Method: Calls helper function */
    template <class T, class V>
    bool Multimap<T,V>::operator==(Multimap<T,V> &rightMultimap) {
        bool allEqual = true;
        equalsOperatorHelper(this->root, this->NIL, rightMultimap.root, rightMultimap.NIL, allEqual);
        return allEqual;        
    }

    /* != operator overload - returns if the two maps are not equal 
    Method: Calls helper function */
    template <class T, class V>
    bool Multimap<T,V>::operator!=(Multimap<T,V> &rightMultimap) {
        bool allEqual = true;
        equalsOperatorHelper(this->root, this->NIL, rightMultimap.root, rightMultimap.NIL, allEqual);
        return !allEqual;
    }

    /* equalsOperatorHelper - modified boolean value to indicate
    if the two maps are equal
    Method: In-order transversal of two maps */
    template <class T, class V>
    bool Multimap<T,V>::equalsOperatorHelper(RBTreeNode<T,V> *lNodePtr, RBTreeNode<T,V> *lNILPtr,RBTreeNode<T,V> *rNodePtr, RBTreeNode<T,V> *rNILPtr, bool &areEqual) {
        if(rNodePtr != rNILPtr && lNodePtr != lNILPtr) {
            equalsOperatorHelper(lNodePtr->left, lNILPtr, rNodePtr->left, rNILPtr, areEqual);
            if(lNodePtr->key != rNodePtr->key || lNodePtr->value != rNodePtr->value) {
                areEqual = false;
                return areEqual; //Start exiting out of the function
            }
            equalsOperatorHelper(lNodePtr->right, lNILPtr, rNodePtr->right, rNILPtr, areEqual);
        }
        return areEqual;
    }

    /* << operator overload 
    Method: Call the displayInOrder helper function */
    template <class T, class V>
    ostream& operator<<(ostream& os, Multimap<T,V> &map) {
        os << "{";
        int count = 0;
        map.inOrderDisplay(map.root, map.NIL, os, count);
        os << "}" << endl;
        return os;
    }

    /* inOrderDisplay helper function
    Method: Prints out elements in an in-order fashion */
    template <class T, class V>
    void Multimap<T,V>::inOrderDisplay(RBTreeNode<T,V> *nodePtr, RBTreeNode<T,V> *NILPtr, ostream& sysout, int &count) {
        if(nodePtr != NILPtr) {
            inOrderDisplay(nodePtr->left, NILPtr, sysout, count);
            sysout << "(" << nodePtr->key << ", ";
            //printing the vector
            for(int i = 0; i < nodePtr->value.size(); i++) {
                sysout << nodePtr->value[i];
                if(i != nodePtr->value.size()+1) {
                    sysout << ", ";
                }
            }
            sysout << ")";
            if(count != size()-1) {
                sysout << ", ";
                count++;
            }
            inOrderDisplay(nodePtr->right, NILPtr, sysout, count);
        }
    }

#endif