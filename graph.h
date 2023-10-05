#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include "node.h"

#pragma ONCE

using namespace std;

auto cmp = [](Node* left, Node* right) { return left->get_coste() > right->get_coste() ;}; 


class Graph {
 private:
  string fichero_;                // fichero de entrada
  int nodos_;                     // numero de nodos
  int aristas_;                   // numero de aristas 
  vector<Node*> inspeccionados_;  // vector nodos inspeccionados
  vector<Node*> generados_;       // vector nodos generados 
  vector<vector<float>> costes_;  // matriz para almacenar costes aristas

 public:
  Graph(string fichero);
  void algoritmo();
  Node* bfs(int ini, int final);
  Node* dfs(int ini, int final);
  void sucesores_bfs(Node* padre, priority_queue<Node*, std::vector<Node*>, decltype(cmp)>& frontera);
  void sucesores_dfs(Node* padre, stack<Node*>& frontera);
  bool visitado(Node* nodo, int i);
  void imprimir_resultado(Node* nodo, int origen);
  
};