#include <iostream>

#include "Graph.h"
#include "WGraph.h"

using namespace std;

void div(string s = "") {
  cout << "------------- " << s << " -------------" << endl;
}

void div2(string s = "") {
  cout << "============= " << s << " =============" << endl;
}

int main() {
  div2("Adding Edges");

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

  G.print();
  cout << endl;

  G.saveGraphFileGML("G");

  // Note edge duplicate, ignored by insert function.
  Graph<int> G2;
  G2.addEdge(1, 2);
  G2.addEdge(1, 3);
  G2.addEdge({1, 5});
  G2.addEdges(2, {3, 1, 6});
  G2.addEdges({{4, 3}, {6, 1}, {5, 2}, {4, 1}});

  G2.print();
  cout << endl;

  G2.saveGraphFileGML("G2");

  // Directed version.
  Graph<int> G3(true);
  G3.addEdge(1, 2);
  G3.addEdge(1, 3);
  G3.addEdge({1, 5});
  G3.addEdges(2, {3, 1, 6});
  G3.addEdges({{4, 3}, {6, 1}, {5, 2}, {4, 1}});

  G3.sortVertexList();
  G3.print();
  cout << endl;

  G3.saveGraphFileGML("G3");

  WGraph<int, int> G4;
  G4.addEdges(1, {{3, 2}, {5, 1}, {6, 5}});
  G4.addEdges(2, {{4, 1}, {1, 5}, {5, 2}});
  G4.addEdges(3, {{6, 2}});
  G4.addEdges(4, {{1, 2}});

  G4.print();
  cout << endl;
  G4.saveGraphFileGML("G4");

  WGraph<int, int> G5(true);
  G5.addEdges(1, {{3, 2}, {5, 1}, {6, 5}});
  G5.addEdges(2, {{4, 1}, {1, 5}, {5, 2}});
  G5.addEdges(3, {{6, 2}});
  G5.addEdges(4, {{1, 2}, {3, 7}, {2, 1}});
  G5.addEdges(5, {{2, 3}, {3, 6}});
  G5.addEdges(6, {{4, 4}});

  G5.print();
  cout << endl;
  G5.saveGraphFileGML("G5");

  div2("Deleting Edges Undirected Unweighted Graph");
  G2.sortVertexList();
  G2.print();
  cout << endl;

  div("Delete 1-5");
  G2.deleteEdge(1, 5);
  G2.print();
  cout << endl;

  div("Delete 2-6");
  G2.deleteEdge({2, 6});
  G2.print();
  cout << endl;

  div("Delete 1-2 and 5-2");
  G2.deleteEdges({{1, 2}, {5, 2}});
  G2.print();
  cout << endl;

  div("Delete vertex 3");
  G2.deleteVertex(3);
  G2.print();
  cout << endl;

  div2("Deleting Edges Directed Unweighted Graph");
  G3.addEdge(5, 1);
  G3.addEdges(3, {2, 1, 4});
  G3.addEdges(6, {2, 5, 3});

  G3.sortVertexList();
  G3.print();
  cout << endl;

  div("Delete 1-5");
  G3.deleteEdge(1, 5);
  G3.print();
  cout << endl;

  div("Delete 2-6");
  G3.deleteEdge({2, 6});
  G3.print();
  cout << endl;

  div("Delete 1-2 and 5-2");
  G3.deleteEdges({{1, 2}, {5, 2}});
  G3.print();
  cout << endl;

  div("Delete vertex 3");
  G3.deleteVertex(3);
  G3.print();
  cout << endl;

  div2("Deleting Edges Undirected Weighted Graph");
  G4.sortVertexList();
  G4.print();
  cout << endl;

  div("Delete 1-5");
  G4.deleteEdge(1, 5);
  G4.print();
  cout << endl;

  div("Delete 5-2");
  G4.deleteEdge(5, 2);
  G4.print();
  cout << endl;

  div("Delete Vertex 2");
  G4.deleteVertex(2);
  G4.print();
  cout << endl;

  div2("Deleting Edges Directed Weighted Graph");
  G5.sortVertexList();
  G5.print();
  cout << endl;

  div("Delete 1-5");
  G5.deleteEdge(1, 5);
  G5.print();
  cout << endl;

  div("Delete 5-2");
  G5.deleteEdge(5, 2);
  G5.print();
  cout << endl;

  div("Delete Vertex 2");
  G5.deleteVertex(2);
  G5.print();
  cout << endl;

  div2("CC and = Available from pair and vector deep copies.");

  G2.addEdge(1, 2);
  G2.addEdge(1, 3);
  G2.addEdge({1, 5});
  G2.addEdges(2, {3, 1, 6});
  G2.addEdges({{4, 3}, {6, 1}, {5, 2}, {4, 1}});
  G2.sortVertexList();

  Graph<int> G6(G2);
  G2.print();
  cout << endl;
  G6.print();
  cout << endl;

  G6.addEdge(6, 3);

  G2.print();
  cout << endl;
  G6.print();
  cout << endl;

  G3.addEdges(1, {2, 3, 5});
  G3.addEdges(2, {3, 1, 6});
  G3.addEdges(3, {5, 4, 2});
  G3.addEdges({{4, 3}, {6, 1}, {5, 2}, {4, 1}});
  G3.sortVertexList();

  G6 = G3;

  G3.print();
  cout << endl;
  G6.print();
  cout << endl;

  G3.deleteVertex(5);

  G3.print();
  cout << endl;
  G6.print();
  cout << endl;

  return 0;
}
