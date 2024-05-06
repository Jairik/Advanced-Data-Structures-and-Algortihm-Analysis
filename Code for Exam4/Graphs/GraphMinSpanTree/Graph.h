#ifndef GRAPH_H_
#define GRAPH_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

template <class T> class Graph {
protected:
  vector<pair<T, vector<T>>> graph;
  bool directed;

  int getVertexPos(T);
  int getEdgePos(T, T);

public:
  Graph(bool dir = false);
  virtual ~Graph();

  bool isDirected() { return directed; }
  int numVertices();
  int size();
  void clear();
  void addVertex(T);
  void addVertices(vector<T>);
  void addEdge(T, T);
  void addEdge(pair<T, T>);
  void addEdges(T, vector<T>);
  void addEdges(vector<pair<T, T>>);

  void deleteEdge(T, T);
  void deleteEdge(pair<T, T>);
  void deleteEdges(T, vector<T>);
  void deleteEdges(vector<pair<T, T>>);
  void deleteVertex(T);

  vector<T> getAdjacentList(T);
  vector<T> getVertexList();
  vector<pair<T, T>> getEdgeList();

  void sortVertexList() { sort(graph.begin(), graph.end()); }

  void print();
  void saveGraphFileGML(string);
};

template <class T> Graph<T>::Graph(bool dir) { directed = dir; }
template <class T> Graph<T>::~Graph() {}
template <class T> int Graph<T>::numVertices() { return graph.size(); }
template <class T> int Graph<T>::size() { return graph.size(); }
template <class T> void Graph<T>::clear() { graph.clear(); }

template <class T> void Graph<T>::addVertex(T v) {
  bool found = false;
  for (auto vp : graph)
    if (vp.first == v)
      found = true;

  if (!found)
    graph.push_back({v, {}});
}

template <class T> void Graph<T>::addVertices(vector<T> vlist) {
  for (size_t i = 0; i < vlist.size(); i++)
    addVertex(vlist[i]);
}

template <class T> int Graph<T>::getVertexPos(T v) {
  for (size_t i = 0; i < graph.size(); i++)
    if (graph[i].first == v)
      return i;

  return -1;
}

template <class T> int Graph<T>::getEdgePos(T v, T vt) {
  int vpos = getVertexPos(v);
  if (vpos >= 0) {
    vector<T> adjlist = graph[vpos].second;
    for (size_t i = 0; i < adjlist.size(); i++)
      if (adjlist[i] == vt)
        return i;
  }

  return -1;
}

template <class T> void Graph<T>::addEdge(T v, T vt) {
  // Make sure the vertex is in the graph.
  addVertex(v);
  addVertex(vt);
  int pos = getVertexPos(v);

  if (getEdgePos(v, vt) == -1)
    graph[pos].second.push_back(vt);

  // If the graph is not directed add an edge vt - v.
  if (!directed) {
    pos = getVertexPos(vt);

    if (getEdgePos(vt, v) == -1)
      graph[pos].second.push_back(v);
  }
}

template <class T> void Graph<T>::addEdge(pair<T, T> e) {
  addEdge(e.first, e.second);
}

template <class T> void Graph<T>::addEdges(T v, vector<T> vt) {
  for (size_t i = 0; i < vt.size(); i++)
    addEdge(v, vt[i]);
}

template <class T> void Graph<T>::addEdges(vector<pair<T, T>> elist) {
  for (size_t i = 0; i < elist.size(); i++)
    addEdge(elist[i].first, elist[i].second);
}

template <class T> void Graph<T>::deleteEdge(T v1, T v2) {
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

template <class T> void Graph<T>::deleteEdge(pair<T, T> p) {
  deleteEdge(p.first, p.second);
}

template <class T> void Graph<T>::deleteEdges(T v, vector<T> vt) {
  for (size_t i = 0; i < vt.size(); i++)
    deleteEdge(v, vt[i]);
}

template <class T> void Graph<T>::deleteEdges(vector<pair<T, T>> ep) {
  for (size_t i = 0; i < ep.size(); i++)
    deleteEdge(ep[i].first, ep[i].second);
}

template <class T> void Graph<T>::deleteVertex(T v) {
  int pos = getVertexPos(v);
  if (pos == -1)
    return;

  // Remove vertex from graph.
  graph.erase(graph.begin() + pos);

  // Remove all edges that go to v.  By our graph construction
  // we restrict to a single edge between any two vertices.
  for (size_t i = 0; i < graph.size(); i++) {
    size_t vpos = find(graph[i].second.begin(), graph[i].second.end(), v) -
                  graph[i].second.begin();
    if (vpos < graph[i].second.size())
      graph[i].second.erase(graph[i].second.begin() + vpos);
  }
}

template <class T> vector<T> Graph<T>::getAdjacentList(T v) {
  int pos = getVertexPos(v);
  if (pos != -1)
    return graph[pos].second;

  vector<T> empty;
  return empty;
}

template <class T> vector<pair<T, T>> Graph<T>::getEdgeList() {
  vector<pair<T, T>> elist;
  for (size_t i = 0; i < graph.size(); i++) {
    T v1 = graph[i].first;
    vector<T> Adj = graph[i].second;
    for (size_t j = 0; j < Adj.size(); j++) {
      T v2 = Adj[j];
      elist.push_back({v1, v2});
    }
  }
  return elist;
}

template <class T> vector<T> Graph<T>::getVertexList() {
  vector<T> lst;
  for (size_t i = 0; i < graph.size(); i++)
    lst.push_back(graph[i].first);

  return lst;
}

template <class T> void Graph<T>::print() {
  for (auto vp : graph) {
    cout << vp.first << ": ";
    for (auto v : vp.second) {
      cout << v << " ";
    }
    cout << endl;
  }
}

template <class T> void Graph<T>::saveGraphFileGML(string filename) {
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

  vector<pair<T, T>> elist = getEdgeList();

  // Undirected graph remove duplicate edges.
  vector<pair<T, T>> redelist;
  if (!directed) {
    for (size_t i = 0; i < elist.size(); i++) {
      bool found = false;
      T v1 = elist[i].first;
      T v2 = elist[i].second;
      for (size_t j = 0; j < redelist.size(); j++) {
        if ((redelist[j].first == v1 && redelist[j].second == v2) ||
            (redelist[j].first == v2 && redelist[j].second == v1))
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
    fs += "\t\ttarget " + to_string(getVertexPos(elist[i].second)) + "\n";
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

#endif /* GRAPH_H_ */
