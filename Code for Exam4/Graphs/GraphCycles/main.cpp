#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

#include "Graph.h"
#include "WGraph.h"

using namespace std;

template <class T> bool hasCycle(Graph<T> &);
template <class T, class W> bool hasCycle(WGraph<T, W> &);

template <class T> void depthFirstSearch(Graph<T> &);
template <class T>
void DFS(Graph<T> &, vector<int> &, vector<T> &, int, int &,
         vector<pair<T, T>> &);
template <class T> void breadthFirstSearch(Graph<T> &);
template <class T> bool detectCycles(Graph<T> &);
template <class T>
void CycleDFS(Graph<T> &, vector<int> &, vector<T> &, int, int &,
              vector<pair<T, T>> &, bool &);
template <class T> bool digraphDetectCycles(Graph<T> &G, int inf = 1000000000);
template <class T>
void digraphCycleDFS(Graph<T> &, vector<int> &, vector<T> &, int, int &, int,
                     bool &);

template <class T, class W> void depthFirstSearch(WGraph<T, W> &);
template <class T, class W>
void DFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &,
         vector<pair<T, T>> &);
template <class T, class W> void breadthFirstSearch(WGraph<T, W> &);

template <class T, class W> bool detectCycles(WGraph<T, W> &);
template <class T, class W>
void CycleDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &,
              vector<pair<T, T>> &, bool &);
template <class T, class W>
bool digraphDetectCycles(WGraph<T, W> &G, int inf = 1000000000);
template <class T, class W>
void digraphCycleDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &,
                     int, bool &);

void div(string s = "") {
  cout << "\n" << s << " ---------------------------------\n\n";
}

int main() {
  Graph<int> G;
  Graph<int> G2(true);
  Graph<int> G3;
  Graph<int> G4(true);

  G.addEdges(1, {2, 3, 7, 5});
  G.addEdges(2, {4, 5});
  G.addEdges(3, {1, 2, 6, 7});
  G.addEdges(4, {6, 7});
  G.addEdges(5, {1, 4, 6});
  G.addEdges(6, {1, 5});
  G.addEdges(7, {2, 4});

  div("--- Unweighted Undirected Graph");
  G.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(G);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(G);
  cout << endl;

  if (hasCycle(G))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  G.saveGraphFileGML("G");

  G2.addEdges(1, {2, 3, 7, 5});
  G2.addEdges(2, {4, 5});
  G2.addEdges(3, {1, 2, 6, 7});
  G2.addEdges(4, {6, 7});
  G2.addEdges(5, {1, 4, 6});
  G2.addEdges(6, {1, 5});
  G2.addEdges(7, {2, 4});

  div("--- Unweighted Directed Graph");
  G2.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(G2);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(G2);
  cout << endl;

  if (hasCycle(G2))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  G2.saveGraphFileGML("G2");

  G3.addEdge(1, 2);
  G3.addEdge(1, 4);
  G3.addEdge(2, 3);
  G3.addEdge(5, 6);
  G3.addEdge(4, 6);
  G3.addEdge(7, 8);
  G3.addEdge(7, 9);
  //   G3.addEdge(9, 8);
  //   G3.addEdge(4, 5);

  div("--- Another Unweighted Undirected Graph");
  G3.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(G3);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(G3);
  cout << endl;

  if (hasCycle(G3))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  G3.saveGraphFileGML("G3");

  div("--- Another Unweighted Directed Graph");
  G4.addEdge(1, 2);
  G4.addEdge(1, 4);
  G4.addEdge(2, 3);
  G4.addEdge(5, 6);
  G4.addEdge(4, 6);
  G4.addEdge(7, 8);
  G4.addEdge(7, 9);
  G4.addEdge(4, 8);
  G4.addEdge(1, 6);
  G4.addEdge(8, 5);
  //  G4.addEdge(6, 7);

  G4.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(G4);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(G4);
  cout << endl;

  if (hasCycle(G4))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  G4.saveGraphFileGML("G4");

  WGraph<int, int> WG1;
  WGraph<int, int> WG2;
  WGraph<int, int> WG3(true);
  WGraph<int, int> WG4(true);

  WG1.addEdges(1, {{2, 1}, {3, 5}, {7, 4}, {5, 7}});
  WG1.addEdges(2, {{4, 3}, {5, 5}});
  WG1.addEdges(3, {{1, 1}, {2, 3}, {6, 2}, {7, 3}});
  WG1.addEdges(4, {{6, 7}, {7, 1}});
  WG1.addEdges(5, {{1, 3}, {4, 1}, {6, 5}});
  WG1.addEdges(6, {{1, 1}, {5, 3}});
  WG1.addEdges(7, {{2, 8}, {4, 2}});

  div("--- Weighted Undirected Graph");
  WG1.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(WG1);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(WG1);
  cout << endl;

  WG1.saveGraphFileGML("WG1");

  if (hasCycle(WG1))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  WG4.addEdges(1, {{2, 1}, {3, 5}, {7, 4}, {5, 7}});
  WG4.addEdges(2, {{4, 3}, {5, 5}});
  WG4.addEdges(3, {{1, 1}, {2, 3}, {6, 2}, {7, 3}});
  WG4.addEdges(4, {{6, 7}, {7, 1}});
  WG4.addEdges(5, {{1, 3}, {4, 1}, {6, 5}});
  WG4.addEdges(6, {{1, 1}, {5, 3}});
  WG4.addEdges(7, {{2, 8}, {4, 2}});

  div("--- Weighted Directed Graph");
  WG4.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(WG4);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(WG4);
  cout << endl;

  WG4.saveGraphFileGML("WG4");

  if (hasCycle(WG4))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  WG2.addEdge(1, 2, 1);
  WG2.addEdge(1, 4, 3);
  WG2.addEdge(2, 3, 7);
  WG2.addEdge(5, 6, 1);
  WG2.addEdge(4, 6, 7);
  WG2.addEdge(7, 8, 2);
  WG2.addEdge(7, 9, 9);
  WG2.addEdge(4, 8, 5);
  WG2.addEdge(1, 6, 1);
  WG2.addEdge(8, 5, 4);
  //  WG2.addEdge(6, 7, 5);

  div("--- Another Weighted Undirected Graph");
  WG2.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(WG2);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(WG2);
  cout << endl;

  WG2.saveGraphFileGML("WG2");

  if (hasCycle(WG2))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  WG3.addEdge(1, 2, 1);
  WG3.addEdge(1, 4, 3);
  WG3.addEdge(2, 3, 7);
  WG3.addEdge(5, 6, 1);
  WG3.addEdge(4, 6, 7);
  WG3.addEdge(7, 8, 2);
  WG3.addEdge(7, 9, 9);
  WG3.addEdge(4, 8, 5);
  WG3.addEdge(1, 6, 1);
  WG3.addEdge(8, 5, 4);
  //  WG3.addEdge(6, 7, 5);

  div("--- Another Weighted Directed Graph");
  WG3.print();
  cout << endl;

  div("--- Depth First Search");
  depthFirstSearch(WG3);
  cout << endl;

  div("--- Breadth First Search");
  breadthFirstSearch(WG3);
  cout << endl;

  WG3.saveGraphFileGML("WG3");

  if (hasCycle(WG3))
    cout << "Cycle Detected" << endl;
  else
    cout << "No Cycle Detected" << endl;

  return 0;
}

/*
Calls the respective cycle function depending on if it is a directed graph or
not.

Parameter: Graph G.
*/

template <class T> bool hasCycle(Graph<T> &G) {
  if (G.isDirected())
    return digraphDetectCycles(G);
  else
    return detectCycles(G);
}

/*
Calls the respective cycle function depending on if it is a directed graph or
not.

Parameter: Weighted Graph G.
*/
template <class T, class W> bool hasCycle(WGraph<T, W> &G) {
  if (G.isDirected())
    return digraphDetectCycles(G);
  else
    return detectCycles(G);
}

//////////////////////////////////////////
//////////////////////////////////////////
// Unweighted Graph Functions
//////////////////////////////////////////
//////////////////////////////////////////

/*
Depth First Search algorithm for an unweighted graph.

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
Breadth First Search algorithm for an unweighted graph.

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

/*
Cycle detection algorithm for an undirected unweighted graph.  This portion
sets up the counting array and edge tracker and then calls the recursive
depth first search algorithm to cycle check.

Parameter: Graph G.
*/
template <class T> bool detectCycles(Graph<T> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  vector<pair<T, T>> Edges;
  int count = 1;
  bool cycle = false;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    CycleDFS(G, num, vlist, pos, count, Edges, cycle);
  }

  return cycle;
}

/*
Recursive depth first search algorithm to cycle check, for an undirected
unweighted graph.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - Edges: vector of edge data for the sequence of the Depth First Search
     visits and edges traversed.
 - cycle: boolean output parameter that results in true if a cycle exists.
     Should be set to false on the call.
*/
template <class T>
void CycleDFS(Graph<T> &G, vector<int> &num, vector<T> &vlist, int pos,
              int &count, vector<pair<T, T>> &Edges, bool &cycle) {
  vector<T> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i];

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      Edges.push_back({vlist[pos], vert});
      CycleDFS(G, num, vlist, vPos, count, Edges, cycle);
    } else if (find(Edges.begin(), Edges.end(), make_pair(vert, vlist[pos])) ==
               Edges.end()) {
      cycle = true;
      return;
    }
  }
}

/*
Cycle detection algorithm for a directed unweighted graph.  This portion
sets up the counting array and edge tracker and then calls the recursive
depth first search algorithm to cycle check.

Parameter: Graph G.
*/
template <class T> bool digraphDetectCycles(Graph<T> &G, int inf) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  bool cycle = false;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    digraphCycleDFS(G, num, vlist, pos, count, inf, cycle);
  }

  return cycle;
}

/*
Recursive depth first search algorithm to cycle check, for a directed unweighted
graph.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - cycle: boolean output parameter that results in true if a cycle exists.
     Should be set to false on the call.
*/
template <class T>
void digraphCycleDFS(Graph<T> &G, vector<int> &num, vector<T> &vlist, int pos,
                     int &count, int inf, bool &cycle) {
  vector<T> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i];

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      digraphCycleDFS(G, num, vlist, vPos, count, inf, cycle);
    } else if (num[vPos] != inf) {
      cycle = true;
      return;
    }
  }
  num[pos] = inf;
}

//////////////////////////////////////////
//////////////////////////////////////////
// Weighted Graph Functions
//////////////////////////////////////////
//////////////////////////////////////////

/*
Depth First Search algorithm for a weighted graph.

Parameter: Weighted Graph G.
*/
template <class T, class W> void depthFirstSearch(WGraph<T, W> &G) {
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
DFS recursive helper function for the Depth First Search algorithm, for a
weighted graph.

Parameters:
 - Weighted Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - Edges: vector of edge data for the sequence of the Depth First Search
     visits and edges traversed.
 */
template <class T, class W>
void DFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist, int pos,
         int &count, vector<pair<T, T>> &Edges) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      Edges.push_back({vlist[pos], vert});
      DFS(G, num, vlist, vPos, count, Edges);
    }
  }
}

/*
Breadth First Search algorithm for a weighted graph.

Parameter: Weighted Graph G.
 */
template <class T, class W> void breadthFirstSearch(WGraph<T, W> &G) {
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
      vector<pair<T, W>> Adj = G.getAdjacentList(vert);
      for (size_t i = 0; i < Adj.size(); i++) {
        size_t AdjvPos =
            find(vlist.begin(), vlist.end(), Adj[i].first) - vlist.begin();
        if (num[AdjvPos] == 0) {
          num[AdjvPos] = count++;
          queue.push_back(Adj[i].first);
          Edges.push_back({vert, Adj[i].first});
        }
      }
    }
  }

  for (pair<T, T> e : Edges)
    cout << e.first << " - " << e.second << endl;
}

/*
Cycle detection algorithm for an undirected weighted graph.  This portion
sets up the counting array and edge tracker and then calls the recursive
depth first search algorithm to cycle check.

Parameter: Weighted Graph G.
*/
template <class T, class W> bool detectCycles(WGraph<T, W> &G) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  vector<pair<T, T>> Edges;
  int count = 1;
  bool cycle;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    CycleDFS(G, num, vlist, pos, count, Edges, cycle);
  }

  return cycle;
}

/*
Recursive depth first search algorithm to cycle check, for an undirected
weighted graph.

Parameters:
 - Weighted Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - Edges: vector of edge data for the sequence of the Depth First Search
     visits and edges traversed.
 - cycle: boolean output parameter that results in true if a cycle exists.
     Should be set to false on the call.
*/
template <class T, class W>
void CycleDFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist, int pos,
              int &count, vector<pair<T, T>> &Edges, bool &cycle) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      Edges.push_back({vlist[pos], vert});
      CycleDFS(G, num, vlist, vPos, count, Edges, cycle);
    } else if (find(Edges.begin(), Edges.end(), make_pair(vert, vlist[pos])) ==
               Edges.end()) {
      cycle = true;
      return;
    }
  }
}

/*
Cycle detection algorithm for a directed weighted graph.  This portion
sets up the counting array and edge tracker and then calls the recursive
depth first search algorithm to cycle check.

Parameter: Weighted Graph G.
*/
template <class T, class W> bool digraphDetectCycles(WGraph<T, W> &G, int inf) {
  vector<T> vlist = G.getVertexList();
  vector<int> num(vlist.size());
  int count = 1;
  bool cycle;

  while (find(num.begin(), num.end(), 0) < num.end()) {
    int pos = find(num.begin(), num.end(), 0) - num.begin();
    digraphCycleDFS(G, num, vlist, pos, count, inf, cycle);
  }

  return cycle;
}

/*
Recursive depth first search algorithm to cycle check, for a directed weighted
graph.

Parameters:
 - Graph G
 - num: vector of integer counts to track visitation
 - vlist: vector of vertex names, used to determine positions of the
     vector/edge data in the graph.
 - pos: position of the vertex being processed/visited by the algorithm.
 - count: The current visit count.
 - cycle: boolean output parameter that results in true if a cycle exists.
     Should be set to false on the call.
*/
template <class T, class W>
void digraphCycleDFS(WGraph<T, W> &G, vector<int> &num, vector<T> &vlist,
                     int pos, int &count, int inf, bool &cycle) {
  vector<pair<T, W>> Adj = G.getAdjacentList(vlist[pos]);
  num[pos] = count++;

  for (size_t i = 0; i < Adj.size(); i++) {
    T vert = Adj[i].first;

    size_t vPos = find(vlist.begin(), vlist.end(), vert) - vlist.begin();
    if (vPos < vlist.size() && num[vPos] == 0) {
      digraphCycleDFS(G, num, vlist, vPos, count, inf, cycle);
    } else if (num[vPos] != inf) {
      cycle = true;
      return;
    }
  }
  num[pos] = inf;
}
