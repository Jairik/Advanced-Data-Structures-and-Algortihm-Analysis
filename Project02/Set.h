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

    private:
        //Helper functions
   };

   //Implementations here

    //Default Constructor
    template <class T> 
    Set<T>::Set() {
        //Make a new set object
    }

    //Default Deconstructor - Deletes the tree
    template <class T>
    Set<T>::~Set() {
        //Will be called automatically, nothing to do here
    }

    //Copy Constructor - Copies a given Set
    template <class T>
    Set<T>::Set(const Set<T> &copy) : RBTree<T>(copy) {
        RBTree(copy.RBTree); //This prolly wont work but idk
    }


#endif 