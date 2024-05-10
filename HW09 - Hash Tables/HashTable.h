#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>

using namespace std;

template <class T> class HashTable {
protected:
  int size = 0;
  T *tab = nullptr;
  int (*hf)(T &);
  T empty;
  T removed;

  int probe(int pos);

public:
  HashTable(int sz, int (*hashfct)(T &), T e, T r);
  virtual ~HashTable();
  void insert(T);
  void remove(T);
  bool find(T);
  void rehash(int sz);
  void print();
};

template <class T>
HashTable<T>::HashTable(int sz, int (*hashfct)(T &), T e, T r) {
  tab = new T[sz];
  size = sz;
  hf = hashfct;
  empty = e;
  removed = r;

  for (int i = 0; i < size; i++)
    tab[i] = empty;
}

template <class T> HashTable<T>::~HashTable() { delete[] tab; }

template <class T> int HashTable<T>::probe(int pos) {
  // Linear probe.
  return (pos + 1) % size;
}

template <class T> void HashTable<T>::insert(T item) {
  int pos = hf(item) % size;
  int initpos = pos;

  // If position is open probe loop is not done.
  while (tab[pos] != empty && tab[pos] != removed) {
    pos = probe(pos);
    if (pos == initpos)
      return;
  }

  tab[pos] = item;
}

template <class T> void HashTable<T>::remove(T item) {
  int pos = hf(item) % size;
  int initpos = pos;

  // If item is in first guess, probe loop is not done.
  while (tab[pos] != item) {
    pos = probe(pos);
    if (pos == initpos || tab[pos] == empty)
      return;
  }
  tab[pos] = removed;
}

template <class T> bool HashTable<T>::find(T item) {
  int pos = hf(item) % size;
  int initpos = pos;

  // If item is in first guess, probe loop is not done.
  while (tab[pos] != item) {
    pos = probe(pos);
    if (pos == initpos || tab[pos] == empty)
      return false;
  }

  return true;
}

template <class T> void HashTable<T>::rehash(int sz) {
  HashTable<T> newtable(sz, hf, empty, removed);
  for (int i = 0; i < size; i++) {
    if (tab[i] != empty && tab[i] != removed) {
      T item = tab[i];
      newtable.insert(item);
    }
  }

  delete[] tab;
  tab = newtable.tab;
  size = newtable.size;
  newtable.tab = nullptr;
}

template <class T> void HashTable<T>::print() {
  for (int i = 0; i < size; i++)
    cout << i << ": " << tab[i] << endl;
}

#endif /* HASHTABLE_H_ */
