#include <algorithm>
#include <iostream>
#include <vector>

#include "Graph.h"
#include "WGraph.h"

using namespace std;

template <class T, class W> bool connected(WGraph<T, W> &);
template <class T, class W>
void ConnDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &);

template <class T> bool connected(Graph<T> &);
template <class T>
void ConnDFS(Graph<T> &, vector<int> &, vector<T> &, int, int &);

void div() { cout << "\n---------------------------------\n\n"; }

int main() {
  WGraph<char, int> G;

  G.addEdge('a', 'b', 6);
  G.addEdge('a', 'c', 5);
  G.addEdge('b', 'c', 9);
  G.addEdge('b', 'e', 13);
  G.addEdge('c', 'd', 16);
  G.addEdge('c', 'f', 12);
  G.addEdge('d', 'e', 15);
  G.addEdge('d', 'f', 7);
  G.addEdge('e', 'g', 8);
  G.addEdge('f', 'g', 3);

  G.sortVertexList();
  G.print();
  G.saveGraphFileGML("G");

  cout << "G" << (connected(G) ? " is connected" : " is not connected") << endl;

  div();

  G.addEdge('a', 'b', 6);
  G.addEdge('a', 'c', 5);
  G.addEdge('b', 'c', 9);
  G.addEdge('b', 'e', 13);
  G.addEdge('c', 'd', 16);
  G.addEdge('c', 'f', 12);
  G.addEdge('d', 'e', 15);
  G.addEdge('d', 'f', 7);
  G.addEdge('e', 'g', 8);
  G.addEdge('f', 'g', 3);

  G.addEdge('x', 'y', 5);
  G.addEdge('y', 'z', 12);
  G.addEdge('z', 'x', 7);

  G.sortVertexList();
  G.print();
  G.saveGraphFileGML("G2");

  cout << "G" << (connected(G) ? " is connected" : " is not connected") << endl;

  div();

  G.addEdge('g', 'z', 15);

  G.sortVertexList();
  G.print();
  G.saveGraphFileGML("G3");

  cout << "G" << (connected(G) ? " is connected" : " is not connected") << endl;

  return 0;
}

/*
Connected algorithm for our graph class.  Simply calls the DFS recursive
helper function.  If the recursion visits all the nodes then the count
will be the graph size + 1.  Otherwise the graph is not connected.

Parameter: WGraph G.

Notes: If the graph is directed this will check strong connectedness.
 */
template <class T, class W> bool connected(WGraph<T, W> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  ConnDFS(G, num, vlist, 0, count);
  return (static_cast<size_t>(count) == G.getVertexList().size() + 1);
}

/*
ConnDFS recursive helper function for the connected algorithm.

Parameters:
 - WGraph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 */
template <class T, class W>
void ConnDFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist, int pos,
             int &count) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;
    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0)
      ConnDFS(G, num, vlist, vPos, count);
  }
}

/*
Connected algorithm for our graph class.  Simply calls the DFS recursive
helper function.  If the recursion visits all the nodes then the count
will be the graph size + 1.  Otherwise the graph is not connected.

Parameter: Graph G.

Notes: If the graph is directed this will check strong connectedness.
 */
template <class T> bool connected(Graph<T> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  ConnDFS(G, num, vlist, 0, count);
  return (static_cast<size_t>(count) == G.getVertexList().size() + 1);
}

/*
ConnDFS recursive helper function for the connected algorithm.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 */
template <class T>
void ConnDFS(Graph<T> &G, vector<int> &num, vector<T> &vlist, int pos,
             int &count) {
  vector<T> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i];
    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0)
      ConnDFS(G, num, vlist, vPos, count);
  }
}
