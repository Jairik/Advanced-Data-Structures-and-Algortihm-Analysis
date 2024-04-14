#include <iostream>
#include <vector>

using namespace std;

/*
 Definitions:
 A complete binary tree is where all the levels of the tree are filled completely
 except the lowest level nodes which are filled from as left as possible.

 In a max-heap, a parent node is always larger than or equal to its children
 nodes.

 In a min-heap, a parent node is always smaller than or equal to its
 children nodes.


 This is a vector (array) implementation of the max-heap. In the array
 implementation, since the tree is complete, it can be written in contiguous
 memory.  The array locations are the nodes written left to right by level.

 In this case if a node is at position i then its:
 Parent = (i - 1) / 2    (Take floor, i.e. integer division)
 Left Child = 2*i + 1
 Right Child = 2*i + 2
 */

template<class T> class Heap {
private:
	vector<T> data;

	int parent(int i) {
		return (i - 1) / 2;
	}
	int left(int i) {
		return 2 * i + 1;
	}
	int right(int i) {
		return 2 * i + 2;
	}

	void Heapify(int);
	void MakeHeap();

public:
	Heap() {
	}
	Heap(vector<T>);
	Heap(T[], int);

	void insert(T);
	T dequeue();
	bool empty();

	template<class U>
	friend ostream& operator<<(ostream &strm, const Heap<U> &obj);
};

template<class T> Heap<T>::Heap(vector<T> v) {
	data = v;
	MakeHeap();
}

template<class T> Heap<T>::Heap(T A[], int s) {
	data.insert(data.end(), A, A + s);
	MakeHeap();
}

template<class T> void Heap<T>::MakeHeap() {
	int lastnonleaf = data.size() / 2 - 1;
	for (int i = lastnonleaf; i >= 0; i--)
		Heapify(i);
}

template<class T> void Heap<T>::insert(T item) {
	data.push_back(item);

	int i = data.size() - 1;
	while (i != 0 && data[parent(i)] < data[i]) {
		swap(data[parent(i)], data[i]);
		i = parent(i);
	}
}

template<class T> void Heap<T>::Heapify(int i) {
	int largest = i;
	int l = left(i);
	int r = right(i);

	if (l < data.size() && data[l] > data[largest]) {
		largest = l;
	}

	if (r < data.size() && data[r] > data[largest]) {
		largest = r;
	}

	if (largest != i) {
		swap(data[i], data[largest]);
		Heapify(largest);
	}
}

template<class T> T Heap<T>::dequeue() {
	T retitem = data[0];
	data[0] = data[data.size() - 1];
	data.pop_back();
	Heapify(0);
	return retitem;
}

template<class T> bool Heap<T>::empty() {
	return data.empty();
}

template<class U> ostream& operator<<(ostream &strm, const Heap<U> &obj) {
	strm << "[";
	for (unsigned long i = 0; i < obj.data.size(); i++)
		if (i < obj.data.size() - 1)
			strm << obj.data[i] << ", ";
		else
			strm << obj.data[i] << "]";

	return strm;
}
