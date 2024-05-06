#include <algorithm>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#include "Graph.h"

using namespace std;

template <class T> void depthFirstSearch(Graph<T> &);
template <class T>
void DFS(Graph<T> &, vector<int> &, vector<T> &, int, int &,
         vector<pair<T, T>> &);
template <class T> void breadthFirstSearch(Graph<T> &G);

void div(string s = "") {
  cout << "\n" << s << " ---------------------------------\n\n";
}

int main() {
  Graph<int> G;         // undirected
  Graph<char> G2(true); // directed
  Graph<char> G3(true);
  Graph<int> G4;
  Graph<int> G5;

  div("Integer Vertices");

  // Adding vertices and then edges.
  G.addVertices({1, 2, 3, 4, 5, 6, 7});

  cout << G.numVertices() << endl;
  cout << G.size() << endl;

  G.addEdges(1, {2, 3, 7, 5});
  G.addEdges(2, {4, 2, 5});
  G.addEdges(3, {1, 2, 6, 7});
  G.addEdges(4, {6, 7});
  G.addEdges(5, {1, 4, 6});
  G.addEdges(6, {1, 5});
  G.addEdges(7, {2, 4});

  G.print();
  div("Character Vertices");

  // Adding vertices and then edges.
  G2.addVertices({'A', 'B', 'C', 'D', 'E'});
  G2.addEdges('A', {'B', 'E'});
  G2.addEdges('B', {'D', 'C'});
  G2.addEdges('C', {'B', 'A'});
  G2.addEdges('D', {'E', 'A'});
  G2.addEdges('E', {'B', 'C'});

  G2.print();
  cout << endl;

  // Adding vertices is automatic with adding edges. Isolated Vertices
  // would have to be added separately.
  G3.addEdges('A', {'B', 'E'});
  G3.addEdges('B', {'D', 'C'});
  G3.addEdges('C', {'B', 'A'});
  G3.addEdges('D', {'E', 'A'});
  G3.addEdges('E', {'B', 'C'});

  G3.print();
  cout << endl;

  // Can add edges using a vector of edges. Initializer lists work as well.
  G4.addEdges({{1, 2}, {2, 3}, {3, 4}, {4, 1}, {5, 6}, {6, 7}, {7, 5}});
  G4.print();
  cout << endl;

  // Can copy edges from one graph to another.
  auto edgelist = G4.getEdgeList();
  G5.addEdges(edgelist);
  G5.print();
  cout << endl;

  div("Textbook Examples Undirected Graph");

  Graph<char> GText;
  GText.addEdges('a', {'e', 'f', 'g', 'i'});
  GText.addEdges('b', {'g'});
  GText.addEdges('c', {'h'});
  GText.addEdges('d', {'h'});
  GText.addEdges('e', {'f', 'i'});
  GText.addEdges('f', {'i'});

  div("--- Print");
  GText.print();
  cout << endl;

  div("--- Vertex List Sorted");
  GText.sortVertexList();
  GText.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(GText);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(GText);
  cout << endl;

  div("Textbook Examples Directed Graph");

  Graph<char> GTextD(true);
  GTextD.addEdges('a', {'e', 'f'});
  GTextD.addEdges('b', {'g'});
  GTextD.addEdges('c', {'h'});
  GTextD.addEdges('h', {'d'});
  GTextD.addEdges('e', {'i'});
  GTextD.addEdges('f', {'e', 'i'});
  GTextD.addEdges('g', {'a'});
  GTextD.addEdges('i', {'a'});

  div("--- Print");
  GTextD.print();
  cout << endl;

  div("--- Vertex List Sorted");
  GTextD.sortVertexList();
  GTextD.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(GTextD);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(GTextD);
  cout << endl;

  // Saving GML graph files, can be opened and viewed in yEd.
  // Visit http://www.yworks.com for the freeware yEd program, cross-platform.
  GText.saveGraphFileGML("TestGraph001");
  GTextD.saveGraphFileGML("TestDGraph001");
  G.saveGraphFileGML("TestGraph_G");
  G2.saveGraphFileGML("TestGraph_G2");
  G3.saveGraphFileGML("TestGraph_G3");
  G4.saveGraphFileGML("TestGraph_G4");

  return 0;
}

/*
Depth First Search algorithm for our graph class.

Parameter: Graph G.
 */

template <class T> void depthFirstSearch(Graph<T> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  vector<pair<T, T>> Edges;
  int count = 1;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    DFS(G, num, vlist, pos, count, Edges);
  }

  for (pair<T, T> e : Edges)
    cout << e.first << " - " << e.second << endl;
}

/*
DFS recursive helper function for the Depth First Search algorithm.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - Edges: vector of edge data for the sequence of the Depth First Search
     visits and edges traversed.
 */
template <class T>
void DFS(Graph<T> &G, vector<int> &num, vector<T> &vlist, int pos, int &count,
         vector<pair<T, T>> &Edges) {
  vector<T> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i];

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      Edges.push_back({vlist[pos], vert});
      DFS(G, num, vlist, vPos, count, Edges);
    }
  }
}

/*
Breadth First Search algorithm for our graph class.

Parameter: Graph G.
 */
template <class T> void breadthFirstSearch(Graph<T> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  vector<pair<T, T>> Edges;
  int count = 1;
  deque<T> queue;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    size_t pos = find(num.begin(), num.end(), 0) - num.begin();
    num[pos] = count++;
    queue.push_back(vlist[pos]);
    while (!queue.empty()) {
      T vert = queue.front();
      queue.pop_front();
      vector<T> Adj = G.getAdjacentList(vert);
      for (size_t i = 0; i < Adj.size(); i++) {
        size_t AdjvPos =
            find(vlist.begin(), vlist.end(), Adj[i]) - vlist.begin();
        if (num[AdjvPos] == 0) {
          num[AdjvPos] = count++;
          queue.push_back(Adj[i]);
          Edges.push_back({vert, Adj[i]});
        }
      }
    }
  }

  for (pair<T, T> e : Edges)
    cout << e.first << " - " << e.second << endl;
}
