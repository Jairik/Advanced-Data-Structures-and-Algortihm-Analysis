#ifndef HASHTABLE_H_
#define HASHTABLE_H_

/*-----------------------------------------------------------------------------
  Author: JJ McCauley (original file provided by Dr. Spickler)
  Creation Date: 5/10/24
  Description: Modified HashTable.h file that uses the ListOfLists.h header
  file to operate as a hash table, using chaining instead of open-addressing
-----------------------------------------------------------------------------*/

#include <iostream>
#include <algorithm>
#include <vector>
#include "ListOfLists.h" //Including vector of vectors to implement chaining

using namespace std;

template <class T> class HashTable {
protected:
  ListOfLists<T> tab; //Data structure used to store (vector of vectors)
  int (*hf)(T &); //Storing the hash function


public:
  HashTable(int sz, int (*hashfct)(T &));
  virtual ~HashTable();
  void insert(T);
  void remove(T);
  bool find(T);
  void rehash(int sz);
  void print();
};

//Constructor - Instantiate the listoflists and hash function */
template <class T>
HashTable<T>::HashTable(int sz, int (*hashfct)(T &)) {

  tab = ListOfLists<T>(sz); //Instantiating the ListofLists
  hf = hashfct; //Storing the hash function
}

//Deconstructor - deletes the ListofLists
template <class T> HashTable<T>::~HashTable() {}

//Insert an item into the HashTable
template <class T> void HashTable<T>::insert(T item) {
  int pos = hf(item) % tab.size(); //Getting the index
  tab[pos].push_back(item); //Placing the new item at the vector at this position
}

/*Remove an item from the HashTable */
template <class T> void HashTable<T>::remove(T item) {
  int pos = hf(item) % tab.size(); //Getting index
  vector<T>& row = tab[pos]; //Storing the row by reference
  //Find the element in the list (getting the iterator)
  auto i = std::find(row.begin(), row.end(), item);
  //If the element exists, remove it
  if(i != row.end()) {
    row.erase(i);
  }
}

/*Find a given item in the HashTable 
Returns: If the item was found */
template <class T> bool HashTable<T>::find(T item) {
  int pos = hf(item) % tab.size(); //Getting the position
  //Using the algorithm library to find the given item within the vector at pos
  auto i = std::find(tab[pos].begin(), tab[pos].end(), item);
  return (i != tab[pos].end());
}

/*Restructure the HashTable when too many spots are filled, given a new size
Note: This approach accounts for rehashing with smaller & larger sizes*/
template <class T> void HashTable<T>::rehash(int sz) {
  ListOfLists<T> nTab = ListOfLists<T>(sz); //Make a new one with the new size
  int pos; //position for re-inserting old elements
  //Adding all old elements into the new ListOfLists
  for(int i = 0; i < tab.size(); i++) {
    if(!(tab[i].empty())) {
      vector<T> &tempVec = tab[i];
      for(int j = 0; j < tempVec.size(); j++) {
        pos = hf(tempVec[j]) % sz;
        nTab[pos].push_back(tempVec[j]);
      }
    }
  }
  tab = nTab; //setting member variable tab to newTab
}

/* Print all elements from each vectpr in the ListOfLists tab 
Note: This works since the [] operator is overloaded*/
template <class T> void HashTable<T>::print() {
  for (int i = 0; i < tab.size(); i++) {
    cout << i << ": ";
    //Print all elements from the vector (if there are any)
    if(!(tab[i].empty())) {
      vector<T> &tempVec = tab[i]; //Copied by reference for efficiency
      for(size_t j = 0; j < tempVec.size(); j++) {
        cout << tempVec[j] << " ";
      }
    }
    cout << endl;
  }
}

#endif /* HASHTABLE_H_ */
