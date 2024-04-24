#ifndef MAP_H
#define MAP_H

#include "RBTree.h"
#include <vector>

/* ---------------------------- Map Header File ------------------------------- 
   Author: JJ McCauley
   Creation Date: 4/18/24
   Last Update: 4/18/24
   Notes: Inherits the Red-Black tree properties
   ---------------------------------------------------------------------------- */

template <class T, class V> //T = key
class Map : public RBTree<T, V> {
    private:
        //Helper functions
    public:
        //Constructors 
        map();
        ~map();

        //Map-specific functions
        void insert(T, V);
        bool find(T);
        void erase(T);
        bool isEmpty();
        V get(T); //Get a u value based of a T key
        void set(T, V); //Set a T to a U value
        int size(); //Different approach this time
        void clear();

        //Overloaded Operators
        map<T, V> operator=(map<T>, V &right);
        bool operator==(map<T, V> &right);
        bool operator!=(map<T, V> &right);
        template<class U, class K> friend ostream& operator<<(ostream& os, map<U,K> &);
   };

   //Implementations here


#endif