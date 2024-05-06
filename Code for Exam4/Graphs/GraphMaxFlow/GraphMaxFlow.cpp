#include <deque>
#include <iostream>
#include <tuple>
#include <vector>

#include "WGraph.h"

using namespace std;

template <class T, class W> class flowedge {
public:
  T from, to;
  W cap, flow;

  flowedge(T f, T t, W w = 0, W fl = 0) {
    from = f;
    to = t;
    cap = w;
    flow = fl;
  }

  friend ostream &operator<<(ostream &strm, const flowedge &obj) {
    strm << obj.from << " -> " << obj.to << " : " << obj.cap << " : "
         << obj.flow;
    return strm;
  }

  bool operator<(const flowedge &rhs) { return cap < rhs.cap; }
  bool operator>(const flowedge &rhs) { return cap > rhs.cap; }
  bool operator==(const flowedge &rhs) {
    return (cap == rhs.cap) && (from == rhs.from) && (to == rhs.to);
  }
};

template <class T, class W> class vertexlabel {
public:
  T vertex, parent;
  W flow;
  bool labeled;

  vertexlabel(T v, T p, double fl = 0) {
    vertex = v;
    parent = p;
    flow = fl;
    labeled = false;
  }

  friend ostream &operator<<(ostream &strm, const vertexlabel &obj) {
    strm << obj.vertex << " : " << obj.parent << " : " << obj.flow << " : "
         << obj.labeled;
    return strm;
  }
};

template <class T, class W> int findVertexPos(vector<vertexlabel<T, W>> V, T u);
template <class T, class W> int findEdgePos(vector<flowedge<T, W>> E, T u, T v);

template <class T, class W>
tuple<vector<T>, vector<T>, vector<flowedge<T, W>>, W>
FordFulkersonAlgorithm(WGraph<T, W> G, T source, T sink, W inf = 1000000000);

int main() {
  // Define the network by its edges.
  // We will assume that s is the source and t is the sink.
  // Example graph from the text.
  WGraph<char, int> G(true);
  G.addEdge('s', 'a', 2);
  G.addEdge('s', 'c', 4);
  G.addEdge('s', 'e', 1);
  G.addEdge('a', 'b', 5);
  G.addEdge('b', 't', 3);
  G.addEdge('c', 'a', 2);
  G.addEdge('c', 'f', 3);
  G.addEdge('d', 'b', 5);
  G.addEdge('d', 't', 2);
  G.addEdge('e', 'd', 2);
  G.addEdge('e', 'f', 3);
  G.addEdge('f', 't', 1);

  G.saveGraphFileGML("G");

  tuple<vector<char>, vector<char>, vector<flowedge<char, int>>, int>
      MaxFlowInfo = FordFulkersonAlgorithm(G, 's', 't');

  // Get and display results.
  vector<char> X = get<0>(MaxFlowInfo);
  vector<char> NotX = get<1>(MaxFlowInfo);
  vector<flowedge<char, int>> E = get<2>(MaxFlowInfo);
  int Max = get<3>(MaxFlowInfo);

  cout << " X: ";
  for (auto x : X)
    cout << x << " ";
  cout << endl;

  cout << "~X: ";
  for (auto x : NotX)
    cout << x << " ";
  cout << "\n\n";

  cout << "Final Edge Flow List" << endl;
  for (auto x : E)
    cout << x << endl;
  cout << endl;

  cout << "Maximum Flow = " << Max << endl;

  // Create and save the final flow graph.
  WGraph<char, int> FG(true);
  for (auto x : E)
    FG.addEdge(x.from, x.to, x.flow);

  FG.saveGraphFileGML("FG");

  return 0;
}

template <class T, class W>
tuple<vector<T>, vector<T>, vector<flowedge<T, W>>, W>
FordFulkersonAlgorithm(WGraph<T, W> G, T source, T sink, W inf) {
  tuple<vector<T>, vector<T>, vector<flowedge<T, W>>, W> RetInfo;

  // Create a vertex list of vertexlabel objects.
  vector<T> Vlist = G.getVertexList();
  vector<vertexlabel<T, W>> V;
  for (auto v : Vlist) {
    V.push_back(vertexlabel<T, W>(v, v));
  }

  // Create an edge list of flowedge objects.
  vector<flowedge<T, W>> E;
  vector<pair<T, pair<T, W>>> Gedges = G.getEdgeList();
  for (auto v : Gedges) {
    E.push_back(flowedge<T, W>(v.first, v.second.first, v.second.second, 0));
  }

  // Ford-Fulkerson Algorithm
  // deque of vertices to be used as a stack structure. Push source vertex.
  deque<T> labeled;
  labeled.push_back(source);

  // Set the source for processing
  int spos = findVertexPos(V, source);
  V[spos].parent = source;
  V[spos].flow = inf;
  V[spos].labeled = true;

  while (!labeled.empty()) {
    // Pop the next vertex to visit off the stack.
    T v = labeled.back();
    labeled.pop_back();
    bool pathfinished = false;

    // for all unlabeled vertices u adjacent to v.
    for (size_t i = 0; i < E.size() && !pathfinished; i++) {
      bool ulabeled = false;
      T u;
      int upos = -1;
      // Forward edge, from is v.
      if (E[i].from == v) {
        // Get u, edge to vertex.
        u = E[i].to;

        // If u is labeled, proceed to next edge.
        upos = findVertexPos(V, u);
        if (V[upos].labeled)
          continue;

        // So u is currently not labeled.
        int vpos = findVertexPos(V, v);

        // Calculate the slack of the vu edge.
        W slack = E[i].cap - E[i].flow;

        // If slack is positive, label u.
        if (slack > 0) {
          V[upos].parent = v;
          V[upos].flow = min(V[vpos].flow, slack);
          V[upos].labeled = true;
          ulabeled = true;
        }
        // Backward edge, v is the to vertex.
      } else if (E[i].to == v) {
        // Get u, edge from vertex.
        u = E[i].from;

        // If u is labeled, proceed to next edge.
        upos = findVertexPos(V, u);
        if (V[upos].labeled)
          continue;

        // So u is currently not labeled.
        int vpos = findVertexPos(V, v);

        // If the flow of the edge is positive, label u and update v.
        if (E[i].flow > 0) {
          V[upos].parent = v;
          V[upos].flow = min(V[vpos].flow, E[i].flow);
          V[upos].labeled = true;
          ulabeled = true;
        }
      }

      // If u was labeled and hence a change to the graph.
      if (ulabeled) {

        // If we finish a path from s to t. Augment Path stage.
        if (u == sink) {
          // Get path by following the parents back to s.
          upos = findVertexPos(V, u);
          W tflow = V[upos].flow;
          int uppos = findVertexPos(V, V[upos].parent);
          bool finished = false;

          while (!finished) {
            // Find the edge from the parent to the vertex in the path.
            int epos = findEdgePos(E, V[uppos].vertex, V[upos].vertex);
            // forward edge if edge is found and backward if not.
            if (epos >= 0) {
              E[epos].flow += tflow;
              // backward edge
            } else {
              epos = findEdgePos(E, V[upos].vertex, V[uppos].vertex);
              E[epos].flow -= tflow;
            }

            // If the parent is the source we are finished with the path.
            if (V[upos].parent == source)
              finished = true;
            else {
              // Otherwise move back one edge in the path.
              upos = findVertexPos(V, V[upos].parent);
              uppos = findVertexPos(V, V[upos].parent);
            }
          }

          // Reset the vertices and labeled stack.
          for (size_t i = 0; i < V.size(); i++) {
            V[i].labeled = false;
            V[i].flow = 0;
            V[i].parent = V[i].vertex;
          }

          labeled.clear();
          labeled.push_back(source);
          V[spos].parent = source;
          V[spos].flow = inf;
          V[spos].labeled = true;

          // exit the loop and find another path.
          pathfinished = true;
        } else {
          if (upos >= 0)
            labeled.push_back(u);
        }
      }
    }
  }

  T maxflow = 0;
  for (size_t i = 0; i < V.size(); i++)
    for (size_t j = 0; j < V.size(); j++) {
      if (V[i].labeled && !V[j].labeled) {
        int epos = findEdgePos(E, V[i].vertex, V[j].vertex);
        if (epos != -1)
          maxflow += E[epos].flow;
      }
    }

  vector<T> X;
  vector<T> NotX;
  for (size_t i = 0; i < V.size(); i++)
    if (V[i].labeled)
      X.push_back(V[i].vertex);
    else
      NotX.push_back(V[i].vertex);

  get<0>(RetInfo) = X;
  get<1>(RetInfo) = NotX;
  get<2>(RetInfo) = E;
  get<3>(RetInfo) = maxflow;

  return RetInfo;
}

// Finds the position of the desired vertex in a vertex list.
template <class T, class W>
int findVertexPos(vector<vertexlabel<T, W>> V, T u) {
  for (size_t j = 0; j < V.size(); j++)
    if (V[j].vertex == u)
      return j;

  return -1;
}

// Finds the position of the desired edge in an edge list.
template <class T, class W>
int findEdgePos(vector<flowedge<T, W>> E, T u, T v) {
  for (size_t j = 0; j < E.size(); j++)
    if (E[j].from == u && E[j].to == v)
      return j;

  return -1;
}
