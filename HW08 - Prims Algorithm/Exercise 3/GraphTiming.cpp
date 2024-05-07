//Author: JJ McCauley
//Graph Timing - Prims vs. Kruskal's

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono> 
#include <iostream>
#include <vector>
#include <queue> //For copied implementation
#include <map> //For copied implementation
#include <climits> //For copied implementation

#include "WGraph.h"

using namespace std;

template <class T, class W> WGraph<T, W> KruskalAlgorithm(WGraph<T, W> &);
template <class T, class W> WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &); 
template <class T, class W> W totalWeight(WGraph<T, W> &);
template <class T, class W> bool detectCycles(WGraph<T, W> &);
template <class T, class W> bool connected(WGraph<T, W> &);
template <class T, class W>
void ConnDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &);
template <class T, class W>
void CycleDFS(WGraph<T, W> &, vector<int> &, vector<T> &, int, int &,
              vector<pair<T, T>> &, bool &);
void div() { cout << "\n---------------------------------\n\n"; }

int main() {
  //An undirected connected weighted graph.
  WGraph<int, int> G;
  //Setting iterations size
  int numOfIterations, numOfVerticies;
  //Seeding random number generator
  srand(time(0));
  int randV1, randV2, randW, startV, endV; //Making variables

  //Getting user input
  cout << "Enter the maximum number of edges: ";
  cin >> numOfIterations;
  cout << "Enter the maximum number of verticies: ";
  cin >> numOfVerticies;

  //inserting numOfIterations into the graph
  for(int i = 0; i < numOfIterations-1; i++) {
    //Getting random numbers
    randV1 = (rand()%numOfVerticies) + 1;
    randV2 = (rand()%numOfVerticies) + 1;
    randW = (rand()%100) + 1;
    //Ensuring the 2 verticies are not the same
    while(randV1 == randV2) {
      randV2 = (rand()%numOfVerticies) + 1;
    }
    //Add the edge to G
    G.addEdge(randV1, randV2, randW);
  }

  cout << endl << "Random numbers have been generated, ensuring connectivity now..." << endl;

  //Checking if the graph is connected
  if(!connected(G)) {
    cout << "Graph was not connected, ending program now";
    exit(0); //ending the program
  }
  else {
	  cout << "Graph is connected!" << endl;
  }

  G.sortVertexList();
  cout << "Size of G: " << G.size() << endl;
  cout << "Total weight of G: " << totalWeight(G) << endl;
  cout << "Inserting into graphs now..." << endl;

  div();

  cout << "Minimal Spanning Tree - Kruskal Algorithm" << endl;
  auto startKTimer = chrono::high_resolution_clock::now(); //Starting the timer
  WGraph<int, int> MST1 = KruskalAlgorithm(G); //Getting minimal spanning tree

  //ending the timer
  auto endKTimer = std::chrono::high_resolution_clock::now();
	auto timeElaspedK = (chrono::duration_cast<chrono::microseconds>(endKTimer-startKTimer)).count();
  double tElapsedK = static_cast<double>(timeElaspedK) /1000000.0; //convert to seconds
  
  MST1.saveGraphFileGML("Kruskal_Minimal_Spanning_Tree"); //Saving to graph file
  cout << "Size of Kruskal's MST: " << MST1.size() << endl;
  cout << "Total weight of Kruskal's MST: " << totalWeight(MST1) << endl;
  cout << "Elasped time for Kruskal's Algorithm: " << tElapsedK << endl;

  div();

  cout << "Minimal Spanning Tree - Jarnik Prim Algorithm" << endl;
  auto startPTimer = chrono::high_resolution_clock::now(); //Starting the timer
  WGraph<int, int> MST = JarnikPrimAlgorithm(G); //Getting minimal spanning tree

  //ending the timer
  auto endPTimer = std::chrono::high_resolution_clock::now();
	auto timeElaspedP = (chrono::duration_cast<chrono::microseconds>(endPTimer-startPTimer)).count();
  double tElapsedP = static_cast<double>(timeElaspedP) /1000000.0; //convert to seconds
  
  MST.saveGraphFileGML("JarnikPrim_Minimal_Spanning_Tree"); //Saving to graph file
  cout << "Size of Jarnik Prim's MST: " << MST.size() << endl;
  cout << "Total weight of Jarnik Prim's MST: " << totalWeight(MST) << endl;
  cout << "Elasped time for Jarnik Prim's Algorithm: " << tElapsedP << endl << endl;

  return 0;
}

//Calculate the total weight of a given graph
template <class T, class W>
W totalWeight(WGraph<T, W> &g) {
  //Getting the edges
  vector<pair<T, pair<T, W>>> edges = g.getEdgeList();
  //Declaring a total weight variable
  W totalWeight = 0;
  //Looping through all edges in the graph
  size_t size = edges.size();
  for(int i = 0; i < size; i++) {
    totalWeight += edges[i].second.second; //adding current weight to the total
  }
  //Returning the value divided by 2 (accounting for duplicate edges)
  return totalWeight/2;
}

/* Jarnik-Prim Algorithm 
Description: Finds the minimal spanning tree (MST) of a graph
Parameter: A weighted, connected, undirected graph
Returns: The mimimal spanning tree
Notes: Code is likely incorrect and will likely mess up timing results*/
template <class T, class W> 
WGraph<T, W> JarnikPrimAlgorithm(WGraph<T, W> &g) {
  WGraph<T, W> MST;
  bool isIncident;
  vector<pair<T, pair<T, W>>> edges = g.getEdgeList();
  vector<T> verticies = g.getVertexList();

  sort(edges.begin(), edges.end(),
       [](auto &a, auto &b) { return a.second.second < b.second.second; });

  //Insert the first edge & vertex
  MST.addEdge(edges[0]);
  MST.addVertex(verticies[0]);

  int MSTedgecount = 0;
  int gvertcount = g.size();
  for (size_t i = 0; i < edges.size() && MSTedgecount < gvertcount - 1; i++) {
    // If the edge is already in the graph move to the next one.
    if (MST.getEdgePos(edges[i].first, edges[i].second.first) != -1)
      continue;
    //Testing for incidence
    vector<T> MSTVerticies = MST.getVertexList();
    isIncident = false;
    //Checking if the vertex is in the vertex list
    for(size_t v = 0; v < MSTVerticies.size() && !isIncident; v++) {
      if(MSTVerticies[v] == edges[i].first || MSTVerticies[v] == edges[i].second.first) {
        isIncident = true;
      }
    }
    if(isIncident) {
      //Testing for cycles
      WGraph<T, W> TestMST = MST;
      TestMST.addEdge(edges[i]);
      if (!detectCycles(TestMST)) {
        MST.addEdge(edges[i]);
        MSTedgecount++;
      }
    }
  }
  return MST;
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
