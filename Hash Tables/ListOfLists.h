#ifndef LISTOFLISTS_H_
#define LISTOFLISTS_H_

#include <vector>

using namespace std;

template <class T> class ListOfLists {
protected:
  vector<vector<T>> list;

public:
  ListOfLists(int rows = 0, int cols = 0);
  virtual ~ListOfLists();

  size_t size();
  void addRow(int m = 0);
  void addRows(int n = 1, int m = 0);
  void push_back(vector<T>);
  vector<T> &operator[](const size_t &);
};

template <class T> ListOfLists<T>::ListOfLists(int rows, int cols) {
  if (rows > 0)
    for (int i = 0; i < rows; i++)
      addRow(cols);
}

template <class T> ListOfLists<T>::~ListOfLists() {}

template <class T> size_t ListOfLists<T>::size() { return list.size(); }

template <class T> void ListOfLists<T>::addRow(int m) {
  vector<T> empty(m);
  list.push_back(empty);
}

template <class T> void ListOfLists<T>::addRows(int n, int m) {
  if (n > 0)
    for (int i = 0; i < n; i++)
      addRow(m);
}

template <class T> void ListOfLists<T>::push_back(vector<T> r) {
  list.push_back(r);
}

// This assumes that the list is not empty.  If the index is out of bounds
// it is trimmed to be in bounds.
template <class T> vector<T> &ListOfLists<T>::operator[](const size_t &sub) {
  if (sub < 0)
    return list[0];
  else if (sub >= size())
    return list[size() - 1];
  else
    return list[sub];
}

#endif /* LISTOFLISTS_H_ */
