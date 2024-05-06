#include <algorithm>
#include <cmath>
#include <deque>
#include <float.h>
#include <iostream>
#include <limits.h>
#include <vector>

#include "WGraph.h"

using namespace std;

template <class T, class W>
int FindMinTBC(vector<W> CurrDist, vector<bool> toBeChecked);

template <class T, class W>
vector<pair<T, W>> DijkstraAlgorithm(WGraph<T, W> &G, T start, W inf = 1000000);

template <class T, class W>
vector<pair<T, W>> FordAlgorithm(WGraph<T, W> &G, T start, W inf = 1000000);

void div(string s = "") {
  cout << "\n" << s << " ---------------------------------\n\n";
}

int main() {
  // Syntax for creating weighted graphs.
  WGraph<int, int> G;        // Undirected
  WGraph<int, int> G2(true); // Directed
  WGraph<int, int> G3(true);
  WGraph<int, int> G4(true);
  WGraph<char, double> G5(true);

  div("Integer Vertices");

  // Adding vertices and edges, undirected adds double edge.
  G.addVertices({1, 2, 3, 4, 5, 6});
  G.addVertex(7);
  G.addEdges(1, {{2, 4}, {3, 1}, {6, 10}});
  G.addEdges(2, {{3, 5}, {7, 4}});
  G.addEdges(3, {{4, 1}, {5, 3}});
  G.addEdges(4, {{1, 2}, {6, 5}});

  G.print();
  cout << endl;

  // Adding vertices and edges.
  G2.addVertices({1, 2, 3, 4, 5, 6, 7});
  G2.addEdges(1, {{2, 4}, {3, 1}, {6, 10}});
  G2.addEdges(2, {{3, 5}, {7, 4}});
  G2.addEdges(3, {{4, 1}, {5, 3}});
  G2.addEdges(4, {{1, 2}, {6, 5}});
  G2.addEdges(5, {{6, 2}, {7, 2}});
  G2.addEdges(6, {{7, 3}});
  G2.addEdges(7, {{1, 4}, {4, 4}});

  G2.print();
  cout << endl;

  // Adding vertices automatically with edge addition.
  G3.addEdge(1, 2, 5);
  G3.addEdge(1, 3, 2);
  G3.addEdge(1, 4, 6);
  G3.addEdge(2, {1, 4});
  G3.addEdge(2, {4, 1});
  G3.addEdge(3, 2, 5);
  G3.addEdge(3, {1, 1});
  G3.addEdge(4, {2, 2});
  G3.addEdge(4, 1, 3);

  G3.print();
  cout << endl;

  // Getting an edge list and copying to another.
  auto edgelist = G2.getEdgeList();
  G4.addEdges(edgelist);
  G4.print();
  cout << endl;

  // Sorting the vertices.
  G4.sortVertexList();
  G4.print();
  cout << endl;

  div("Character Vertices");

  // Using character vertices and double weights.
  G5.addEdges('a', {{'b', 1.2}, {'c', 3.1}});
  G5.addEdges('b', {{'c', -1.3}, {'d', 3.2}});
  G5.addEdges('c', {{'d', 1.9}});
  G5.addEdges('d', {{'a', 1.6}});
  G5.print();
  cout << endl;

  // Export of graph files for yEd.
  G4.saveGraphFileGML("Test001Graph");
  G.saveGraphFileGML("Test002Graph");
  G5.saveGraphFileGML("Test003Graph");

  div("Textbook Example #1");

  WGraph<char, int> TextEx(true);
  TextEx.addEdge('a', 'e', 1);
  TextEx.addEdge('a', 'h', 10);
  TextEx.addEdge('b', 'c', 2);
  TextEx.addEdge('d', 'a', 4);
  TextEx.addEdge('d', 'h', 1);
  TextEx.addEdge('e', 'f', 3);
  TextEx.addEdge('f', 'b', 1);
  TextEx.addEdge('f', 'c', 3);
  TextEx.addEdge('f', 'g', 7);
  TextEx.addEdge('f', 'i', 1);
  TextEx.addEdge('h', 'e', 5);
  TextEx.addEdge('h', 'i', 9);
  TextEx.addEdge('i', 'j', 2);
  TextEx.addEdge('j', 'g', 1);

  TextEx.print();
  cout << endl;

  // Export of graph files for yEd.
  TextEx.saveGraphFileGML("TextExample001Graph");

  div("Dijkstra's Algorithm on the Textbook Example #1");

  vector<pair<char, int>> dist = DijkstraAlgorithm(TextEx, 'd');
  for_each(dist.begin(), dist.end(), [](pair<char, int> p) {
    cout << p.first << " " << p.second << endl;
  });
  cout << endl;

  dist = DijkstraAlgorithm(TextEx, 'a');
  for_each(dist.begin(), dist.end(), [](pair<char, int> p) {
    cout << p.first << " " << p.second << endl;
  });
  cout << endl;

  dist = DijkstraAlgorithm(TextEx, 'f');
  for_each(dist.begin(), dist.end(), [](pair<char, int> p) {
    cout << p.first << " " << p.second << endl;
  });
  cout << endl;

  div("Ford's Algorithm on the Textbook Example #1");

  dist = FordAlgorithm(TextEx, 'd');
  for_each(dist.begin(), dist.end(), [](pair<char, int> p) {
    cout << p.first << " " << p.second << endl;
  });
  cout << endl;

  div("Textbook Example #2");

  WGraph<char, int> TextEx2(true);
  TextEx2.addEdge('a', 'b', 1);
  TextEx2.addEdge('b', 'e', -5);
  TextEx2.addEdge('c', 'd', 1);
  TextEx2.addEdge('c', 'g', 1);
  TextEx2.addEdge('c', 'h', 1);
  TextEx2.addEdge('d', 'a', 2);
  TextEx2.addEdge('d', 'e', 4);
  TextEx2.addEdge('d', 'i', 1);
  TextEx2.addEdge('e', 'f', 4);
  TextEx2.addEdge('g', 'd', -1);
  TextEx2.addEdge('h', 'g', -1);
  TextEx2.addEdge('i', 'f', 1);

  TextEx2.print();
  cout << endl;

  // Export of graph files for yEd.
  TextEx2.saveGraphFileGML("TextExample2_001Graph");

  div("Ford's Algorithm on the Textbook Example #2");

  dist = FordAlgorithm(TextEx2, 'c');
  for_each(dist.begin(), dist.end(), [](pair<char, int> p) {
    cout << p.first << " " << p.second << endl;
  });
  cout << endl;

  return 0;
}

/*
Helper function for Dijkstra's Algorithm.

Parameters:
CurrDist - Vector of weights.
toBeChecked - Vector of bools.

Return: The index of the smallest value in CurrDist whose corresponding entry
in toBeChecked is true.
*/
template <class T, class W>
int FindMinTBC(vector<W> CurrDist, vector<bool> toBeChecked) {
  size_t index = 0;
  while (index < toBeChecked.size() && !toBeChecked[index])
    index++;

  if (index >= toBeChecked.size())
    return -1;

  for (size_t i = index + 1; i < CurrDist.size(); i++)
    if (toBeChecked[i] && CurrDist[i] < CurrDist[index])
      index = i;

  return index;
}

/*
Dijkstra's Algorithm for a simple weighted directed graph.

Parameters:
G - simple weighted directed graph.
start - starting vertex.
inf - value to use as infinity, defaulted to 1000000 but can be set by user.

Return: A vector pf pairs of vertex and weight type.  This is a list of
all the vertices and the shortest distances to each vertex.
This does not store the path from the start to each vertex.
*/
template <class T, class W>
vector<pair<T, W>> DijkstraAlgorithm(WGraph<T, W> &G, T start, W inf) {
  vector<pair<T, W>> results;
  int numvert = G.size();
  vector<T> vertices = G.getVertexList();
  vector<W> CurrDist(numvert);
  vector<bool> toBeChecked(numvert);

  for (size_t i = 0; i < CurrDist.size(); i++) {
    CurrDist[i] = inf;
    toBeChecked[i] = true;
  }

  CurrDist[G.getVertexPos(start)] = 0;

  int pos = FindMinTBC<T, W>(CurrDist, toBeChecked);
  while (pos >= 0) {
    toBeChecked[pos] = false;
    vector<pair<T, W>> Adj = G.getAdjacentList(vertices[pos]);

    for (size_t i = 0; i < Adj.size(); i++) {
      size_t avpos = find(vertices.begin(), vertices.end(), Adj[i].first) -
                     vertices.begin();
      if (avpos >= 0 && avpos < toBeChecked.size() && toBeChecked[avpos]) {
        if (CurrDist[avpos] > CurrDist[pos] + Adj[i].second)
          CurrDist[avpos] = CurrDist[pos] + Adj[i].second;
      }
    }
    pos = FindMinTBC<T, W>(CurrDist, toBeChecked);
  }

  for (size_t i = 0; i < CurrDist.size(); i++)
    results.push_back({vertices[i], CurrDist[i]});

  sort(results.begin(), results.end());
  return results;
}

/*
Ford's Algorithm for a simple weighted directed graph.

Parameters:
G - simple weighted directed graph.
start - starting vertex.
inf - value to use as infinity, defaulted to 1000000 but can be set by user.

Return: A vector pf pairs of vertex and weight type.  This is a list of
all the vertices and the shortest distances to each vertex.
This does not store the path from the start to each vertex.
*/
template <class T, class W>
vector<pair<T, W>> FordAlgorithm(WGraph<T, W> &G, T start, W inf) {
  vector<pair<T, W>> results;
  int numvert = G.size();
  vector<T> vertices = G.getVertexList();
  vector<W> CurrDist(numvert);

  for (size_t i = 0; i < CurrDist.size(); i++)
    CurrDist[i] = inf;

  CurrDist[G.getVertexPos(start)] = 0;

  bool finished = false;
  while (!finished) {
    finished = true;
    for (size_t pos = 0; pos < vertices.size(); pos++) {
      vector<pair<T, W>> Adj = G.getAdjacentList(vertices[pos]);

      for (size_t i = 0; i < Adj.size(); i++) {
        size_t avpos = find(vertices.begin(), vertices.end(), Adj[i].first) -
                       vertices.begin();
        if (CurrDist[avpos] > CurrDist[pos] + Adj[i].second) {
          CurrDist[avpos] = CurrDist[pos] + Adj[i].second;
          finished = false;
        }
      }
    }
  }

  for (size_t i = 0; i < CurrDist.size(); i++)
    results.push_back({vertices[i], CurrDist[i]});

  sort(results.begin(), results.end());
  return results;
}
