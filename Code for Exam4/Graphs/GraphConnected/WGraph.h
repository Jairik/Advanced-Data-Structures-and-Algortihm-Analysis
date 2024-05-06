#ifndef WGRAPH_H_
#define WGRAPH_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

// W represents the data type of the weight, assumed to be numeric.
template <class T, class W> class WGraph {
protected:
  vector<pair<T, vector<pair<T, W>>>> graph;
  bool directed;

public:
  WGraph(bool dir = false);
  virtual ~WGraph();

  bool isDirected() { return directed; }
  int numVertices();
  int size();
  void clear();
  void addVertex(T);
  void addVertices(vector<T>);
  void addEdge(T, T, W);
  void addEdge(T, pair<T, W>);
  void addEdge(pair<T, pair<T, W>>);
  void addEdges(T, vector<pair<T, W>>);
  void addEdges(vector<pair<T, pair<T, W>>>);

  void deleteEdge(T, T);
  void deleteEdge(pair<T, T>);
  void deleteEdges(T, vector<T>);
  void deleteEdges(vector<pair<T, T>>);
  void deleteVertex(T);

  vector<pair<T, W>> getAdjacentList(T);
  vector<T> getVertexList();
  vector<pair<T, pair<T, W>>> getEdgeList();
  int getVertexPos(T);
  int getEdgePos(T, T);

  void sortVertexList() { sort(graph.begin(), graph.end()); }

  void print();
  void saveGraphFileGML(string);
};

template <class T, class W> WGraph<T, W>::WGraph(bool dir) { directed = dir; }
template <class T, class W> WGraph<T, W>::~WGraph() {}
template <class T, class W> int WGraph<T, W>::numVertices() {
  return graph.size();
}
template <class T, class W> int WGraph<T, W>::size() { return graph.size(); }
template <class T, class W> void WGraph<T, W>::clear() { graph.clear(); }

template <class T, class W> void WGraph<T, W>::addVertex(T v) {
  bool found = false;
  for (auto vp : graph)
    if (vp.first == v)
      found = true;

  if (!found)
    graph.push_back({v, {}});
}

template <class T, class W> void WGraph<T, W>::addVertices(vector<T> vlist) {
  for (size_t i = 0; i < vlist.size(); i++)
    addVertex(vlist[i]);
}

template <class T, class W> int WGraph<T, W>::getVertexPos(T v) {
  for (size_t i = 0; i < graph.size(); i++)
    if (graph[i].first == v)
      return i;

  return -1;
}

template <class T, class W> int WGraph<T, W>::getEdgePos(T v, T vt) {
  int vpos = getVertexPos(v);
  if (vpos >= 0) {
    vector<pair<T, W>> adjlist = graph[vpos].second;
    for (size_t i = 0; i < adjlist.size(); i++)
      if (adjlist[i].first == vt)
        return i;
  }

  return -1;
}

template <class T, class W> void WGraph<T, W>::addEdge(T v, T vt, W w) {
  // Make sure the vertex is in the graph.
  addVertex(v);
  addVertex(vt);
  int pos = getVertexPos(v);

  if (getEdgePos(v, vt) == -1)
    graph[pos].second.push_back({vt, w});

  // If the graph is not directed add an edge vt - v.
  if (!directed) {
    pos = getVertexPos(vt);

    if (getEdgePos(vt, v) == -1)
      graph[pos].second.push_back({v, w});
  }
}

template <class T, class W> void WGraph<T, W>::addEdge(T v, pair<T, W> p) {
  addEdge(v, p.first, p.second);
}

template <class T, class W> void WGraph<T, W>::addEdge(pair<T, pair<T, W>> p) {
  addEdge(p.first, p.second);
}

template <class T, class W>
void WGraph<T, W>::addEdges(T v, vector<pair<T, W>> vt) {
  for (size_t i = 0; i < vt.size(); i++)
    addEdge(v, vt[i]);
}

template <class T, class W>
void WGraph<T, W>::addEdges(vector<pair<T, pair<T, W>>> elist) {
  for (size_t i = 0; i < elist.size(); i++)
    addEdge(elist[i].first, elist[i].second);
}

template <class T, class W> void WGraph<T, W>::deleteEdge(T v1, T v2) {
  int pos = getVertexPos(v1);
  int epos = -1;
  if (pos != -1) {
    epos = getEdgePos(v1, v2);
    if (epos != -1)
      graph[pos].second.erase(graph[pos].second.begin() + epos);
  }

  // If the graph is not directed remove edge v2 - v1.
  if (!directed) {
    pos = getVertexPos(v2);
    if (pos != -1) {
      epos = getEdgePos(v2, v1);
      if (epos != -1)
        graph[pos].second.erase(graph[pos].second.begin() + epos);
    }
  }
}

template <class T, class W> void WGraph<T, W>::deleteEdge(pair<T, T> p) {
  deleteEdge(p.first, p.second);
}

template <class T, class W> void WGraph<T, W>::deleteEdges(T v, vector<T> vt) {
  for (size_t i = 0; i < vt.size(); i++)
    deleteEdge(v, vt[i]);
}

template <class T, class W>
void WGraph<T, W>::deleteEdges(vector<pair<T, T>> ep) {
  for (size_t i = 0; i < ep.size(); i++)
    deleteEdge(ep[i].first, ep[i].second);
}

template <class T, class W> void WGraph<T, W>::deleteVertex(T v) {
  int pos = getVertexPos(v);
  if (pos == -1)
    return;

  // Remove vertex from graph.
  graph.erase(graph.begin() + pos);

  // Remove all edges that go to v.  By our graph construction
  // we restrict to a single edge between any two vertices.
  for (size_t i = 0; i < graph.size(); i++) {
    int vpos = -1;
    for (size_t j = 0; j < graph[i].second.size(); j++)
      if (graph[i].second[j].first == v)
        vpos = j;
    if (vpos != -1)
      graph[i].second.erase(graph[i].second.begin() + vpos);
  }
}

template <class T, class W>
vector<pair<T, W>> WGraph<T, W>::getAdjacentList(T v) {
  int pos = getVertexPos(v);
  if (pos != -1)
    return graph[pos].second;

  vector<pair<T, W>> empty;
  return empty;
}

template <class T, class W>
vector<pair<T, pair<T, W>>> WGraph<T, W>::getEdgeList() {
  vector<pair<T, pair<T, W>>> elist;
  for (size_t i = 0; i < graph.size(); i++) {
    T v1 = graph[i].first;
    vector<pair<T, W>> Adj = graph[i].second;
    for (size_t j = 0; j < Adj.size(); j++) {
      pair<T, W> v2 = Adj[j];
      elist.push_back({v1, v2});
    }
  }
  return elist;
}

template <class T, class W> vector<T> WGraph<T, W>::getVertexList() {
  vector<T> lst;
  for (size_t i = 0; i < graph.size(); i++)
    lst.push_back(graph[i].first);

  return lst;
}

template <class T, class W> void WGraph<T, W>::print() {
  for (auto vp : graph) {
    cout << vp.first << ": ";
    for (auto v : vp.second) {
      cout << "(" << v.first << ", " << v.second << ") ";
    }
    cout << endl;
  }
}

template <class T, class W>
void WGraph<T, W>::saveGraphFileGML(string filename) {
  stringstream ss;
  ss.str("");
  ofstream outputFile;
  outputFile.open(filename + ".gml");
  string fs = "Creator \"Don Spickler\"\n"
              "Version \"1.0\"\n"
              "graph\n"
              "[\n"
              "\thierarchic 1\n"
              "\tlabel	\"\"\n"
              "\tdirected 1\n";

  int cols = sqrt(graph.size());
  int colcount = 0;
  int xpos = 0;
  int ypos = 0;
  for (size_t i = 0; i < graph.size(); i++) {
    ss.str("");
    fs += "\tnode\n";
    fs += "\t[\n";
    fs += "\t\tid " + to_string(i) + "\n";
    ss << graph[i].first;
    fs += "\t\tlabel \"" + ss.str() + "\"\n";
    fs += "\t\tgraphics\n";
    fs += "\t\t[\n";
    fs += "\t\t\tx " + to_string(xpos) + "\n";
    fs += "\t\t\ty " + to_string(ypos) + "\n";
    fs += "\t\t\tw 80\n";
    fs += "\t\t\th 40\n";
    xpos += 100;
    colcount++;
    if (colcount >= cols) {
      colcount = 0;
      xpos = 0;
      ypos += 100;
    }
    fs += "\t\t\tcustomconfiguration \"com.yworks.flowchart.start2\"\n";
    fs += "\t\t\tfill \"#E8EEF7\"\n";
    fs += "\t\t\tfill2 \"#B7C9E3\"\n";
    fs += "\t\t\toutline \"#000000\"\n";
    fs += "\t\t]\n";
    fs += "\t\tLabelGraphics\n";
    fs += "\t\t[\n";
    fs += "\t\t\ttext \"" + ss.str() + "\"\n";
    fs += "\t\t\tfontSize 12\n";
    fs += "\t\t\tfontName \"Dialog\"\n";
    fs += "\t\t\tmodel \"null\"\n";
    fs += "\t\t]\n";
    fs += "\t]\n";
  }

  vector<pair<T, pair<T, W>>> elist = getEdgeList();

  // Undirected graph remove duplicate edges.
  vector<pair<T, pair<T, W>>> redelist;
  if (!directed) {
    for (size_t i = 0; i < elist.size(); i++) {
      bool found = false;
      T v1 = elist[i].first;
      pair<T, W> v2 = elist[i].second;
      for (size_t j = 0; j < redelist.size(); j++) {
        if ((redelist[j].first == v1 && redelist[j].second.first == v2.first) ||
            (redelist[j].first == v2.first && redelist[j].second.first == v1))
          found = true;
      }
      if (!found)
        redelist.push_back({v1, v2});
    }
    elist = redelist;
  }

  for (size_t i = 0; i < elist.size(); i++) {
    fs += "\tedge\n";
    fs += "\t[\n";
    fs += "\t\tsource " + to_string(getVertexPos(elist[i].first)) + "\n";
    fs += "\t\ttarget " + to_string(getVertexPos(elist[i].second.first)) + "\n";
    fs += "\t\tlabel \"" + to_string(elist[i].second.second) + "\"\n";
    fs += "\t\tgraphics\n";
    fs += "\t\t[\n";
    fs += "\t\t\tfill \"#000000\"\n";

    if (directed)
      fs += "\t\t\ttargetArrow \"standard\"\n";

    fs += "\t\t]\n";
    fs += "\t]\n";
  }

  fs += "]\n";

  outputFile << fs;
  outputFile.close();
}

#endif /* WGRAPH_H_ */
