#include <algorithm>
#include <iostream>
#include <vector>

#include "WGraph.h"

using namespace std;

template <class T, class W> WGraph<T, W> KruskalAlgorithm(WGraph<T, W> &);
template <class T, class W> WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &); 
template <class T, class W> bool detectCycles(WGraph<T, W> &);
template <class T, class W>
void CycleDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &,
              vector<pair<T, T>> &, bool &);

void div() { cout << "\n---------------------------------\n\n"; }

int main() {
  // An undirected connected weighted graph.
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

  cout << "Sorted Vertex List: " << endl;
  G.sortVertexList();
  G.print();

  div();

  // WGraph<char, int> MST = KruskalAlgorithm(G);
  // MST.sortVertexList();
  // MST.print();
  // MST.saveGraphFileGML("MST");

  cout << "Minimal Spanning Tree - Jarnik Prim Algorithm" << endl;
  WGraph<char, int> MST = JarnikPrimAlgorithm(G); //Getting minimal spanning tree
  cout << "algorithm ran" << endl;
  MST.sortVertexList(); //Sorting for cleaner appearance
  cout << "Vertexes sorted" << endl;
  MST.print(); //Printing to the console
  cout << "What the actual fuck " <<endl;
  MST.saveGraphFileGML("Minimal_Spanning_Tree"); //Saving to graph file
  cout << "Wrote to GML file" << endl;

  return 0;
}


/* Jarnik-Prim Algorithm 
Description: Finds the minimal spanning tree (MST) of a graph
Parameter: A weighted, connected, undirected graph
Returns: The mimimal spanning tree*/
template <class T, class W> 
WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &g) {

  //Booleans for conditional statements
  bool isIncident;
  bool formsCycle;
  WGraph<T,W> MST; //Creating an undirected weighted graph to hold the Minimal-Spanning Tree

  //Getting and sorting all of the edges in a vector called edges
  vector<pair<T, pair<T, W>>> edges = g.getEdgeList();
  if(edges.empty()) { return MST; } //If there are no edges, return empty MST
  sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a.second.second < b.second.second; });

  //Getting necessary sizes for the for-loop
  int numVerticies = g.numVertices(); //|verticies|
  cout << "Num of verticies: " << numVerticies << endl;
  int numEdges = edges.size(); //|edges|
  cout << "Num of Edges: " << numEdges << endl;

  //Looping over verticies
  for(int i = 1; i < numVerticies-1; i++) {
    //Looping over edges
    for(int j = 1; j < numEdges; j++) {

      //Checking to see if adding the jth edge forms a cycle
      WGraph<T, W> tempMST = MST;
      tempMST.addEdge(edges[j]);
      formsCycle = detectCycles(tempMST);

      //Getting incident conditional
      isIncident = (!(MST.getAdjacentList(edges[j].first).empty()) || 
                   !(MST.getAdjacentList(edges[j].second.first).empty()));
      /*If the jth edge does not form a cycle with the current MST AND 
      if the jth edge connects to a vertex already in the current MST*/
      if(!formsCycle && !isIncident) {
        cout << "Inserting edge" << endl;
        //insert the jth edge and break edge iteration
        MST.addEdge(edges[j]);
        break;
      }
    }
  }
  return MST; //Returning the minimal spanning tree
}


/*
Kruskal's Algorithm for finding a minimal spanning tree for a weighted,
connected, undirected graph.  The algorithm does not check that the graph is
connected, it is assumed that this is the case.

Parameter: Weighted Connected Undirected Graph G.
*/
template <class T, class W> WGraph<T, W> KruskalAlgorithm(WGraph<T, W> &G) {
  WGraph<T, W> MST;
  vector<pair<T, pair<T, W>>> edges = G.getEdgeList();

  sort(edges.begin(), edges.end(),
       [](auto &a, auto &b) { return a.second.second < b.second.second; });

  int MSTedgecount = 0;
  int Gvertcount = G.size();
  for (size_t i = 0; i < edges.size() && MSTedgecount < Gvertcount - 1; i++) {
    // If the edge is already in the graph move to the next one.
    if (MST.getEdgePos(edges[i].first, edges[i].second.first) != -1)
      continue;

    WGraph<T, W> TestMST = MST;
    TestMST.addEdge(edges[i]);
    if (!detectCycles(TestMST)) {
      MST.addEdge(edges[i]);
      MSTedgecount++;
    }
  }

  return MST;
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
