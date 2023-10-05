#include <fstream>
#include "graph.h"

using namespace std;

Graph::Graph(string fichero) {
  fichero_ = fichero;
  aristas_ = 0;

  ifstream fin;
  fin.open("ejemplos/"+fichero_);
  fin >> nodos_;

  // Crea la matriz de costes con tantas filas y columnas como el numero de nodos leído en el fichero
  costes_.resize(nodos_);
  for (int i = 0; i < costes_.size(); i++) 
    costes_[i].resize(nodos_);

  // Asignamos los costes de cada posible arista
  float coste;
  for (int i = 0; i < nodos_-1; i++) {
    for (int j = i+1; j < nodos_; j++) {
      fin >> coste;
      costes_[i][j] = coste; 
      costes_[j][i] = coste; 
      if (coste > 0) 
        aristas_++;
    }  
  }
  fin.close();
}

void Graph::algoritmo() {

  int origen, destino;
  bool salir = false;
  Node* nodo_final;
  char opcion;

  while (!salir) {
    
    cout << "Elija el tipo de búsqueda a realizar[b(bfs)/d(dfs)]: "; cin >> opcion;
    cout << "Elija el nodo origen y destino [1-" << nodos_ << "]: "; cin >> origen >> destino;
    
    if (opcion == 'b')
      nodo_final = bfs(origen-1, destino-1);
    else 
      nodo_final = dfs(origen-1, destino-1);


    // Si el coste del nodo devuelto por el algoritmo es -1 no encontró solución
    if (nodo_final->get_coste() == -1) 
      cout << "No existe un camino." << endl;
    else {
      imprimir_resultado(nodo_final, origen);
      generados_.clear();
      inspeccionados_.clear();
    }
    cout << "¿Nuevo fichero de entrada?[Y/N]:"; cin >> opcion;
    if (opcion == 'Y')
      salir = true;

    }

}


Node* Graph::bfs(int ini, int final) {

  // Declaramos una cola para ir metiendo los nodos hoja
  queue<Node*> frontera;

  // Generamos nodo raiz y lo metemos en la cola
  Node* raiz = new Node(ini, 0, 0, NULL);
  frontera.push(raiz);

  generados_.push_back(raiz);

  Node* actual = new Node();
  
  // Mientras la forntera no este vacía
  while (!frontera.empty()) {
    actual = frontera.front();
    frontera.pop();

    inspeccionados_.push_back(actual);

    // Prueba de meta
    if (actual->get_id() == final)
      return actual;

    sucesores_bfs(actual, frontera);
  }

  // Si no encuentra camino devuelve ultimo nodo inspeccionado con coste -1
  actual->set_coste(-1);
  return actual;

}

void Graph::sucesores_bfs(Node* padre, queue<Node*>& frontera) {

  // Recorre en la matriz de costes la fila del nodo padre
  // Si encuentra un sucesor comprueba que no se haya repetido en el camino que está explorando y lo mete en la cola
  for (int i = 0; i < costes_[padre->get_id()].size(); i++) {
      if (costes_[padre->get_id()][i] > 0 && !visitado(padre, i)) {
        Node* nodo = new Node(i, padre->get_nivel()+1, costes_[padre->get_id()][i]+padre->get_coste(), padre);
        frontera.push(nodo);

        generados_.push_back(nodo); // Añadimos los hijos al vector generados
    }
  }

}

Node* Graph::dfs(int ini, int final) {
  // Declaramos una pila para ir metiendo los nodos hoja
  stack<Node*> frontera;

  // Generamos nodo raiz y lo metemos en la cola
  Node* raiz = new Node(ini, 0, 0, NULL);
  frontera.push(raiz);

  generados_.push_back(raiz);

  Node* actual = new Node();
  
  // Mientras la forntera no este vacía
  while (!frontera.empty()) {
    actual = frontera.top();
    frontera.pop();

    inspeccionados_.push_back(actual);

    // Prueba de meta
    if (actual->get_id() == final)
      return actual;

    sucesores_dfs(actual, frontera);
  }

  // Si no encuentra camino devuelve ultimo nodo inspeccionado con coste -1
  actual->set_coste(-1);
  return actual;

}

void Graph::sucesores_dfs(Node* padre, stack<Node*>& frontera) {
  // Recorre en la matriz de costes la fila del nodo padre
  // Si encuentra un sucesor comprueba que no se haya repetido en el camino que está explorando y lo mete en la cola
  for (int i = 0; i < costes_[padre->get_id()].size(); i++) {
      if (costes_[padre->get_id()][i] > 0 && !visitado(padre, i)) {
        Node* nodo = new Node(i, padre->get_nivel()+1, costes_[padre->get_id()][i]+padre->get_coste(), padre);
        frontera.push(nodo);

        generados_.push_back(nodo); // Añadimos los hijos al vector generados
    }
  }
}

// Comprueba si un posible nodo a generar ha sido generado previamente en la rama
bool Graph::visitado(Node* nodo, int i) {

  // Si es el nodo raíz no se ha repetido en el camino
  if (nodo->get_padre() == NULL)
    return false;

  // Comprueba los demás nodos del camino
  while(nodo->get_padre() != NULL) {
    if(nodo->get_id() == i) 
      return true;
    nodo = nodo->get_padre();
  }
  // Comprueba el nodo raíz
  if (nodo->get_id() == i) 
    return true;

  return false;
}

void Graph::imprimir_resultado(Node* nodo, int origen) {
  ofstream fout("salida.csv", ios::app);
  float coste_camino = nodo->get_coste();
  fout << fichero_ << ";" << nodos_ << ";" << aristas_ << ";" << origen << ";" << nodo->get_id()+1 << ";";

  // Creo un vector para poder imprimir el camino de izquierda a derecha
  vector<Node*> imprimir;
  while (nodo->get_padre() != NULL) {
    imprimir.push_back(nodo);
    nodo = nodo->get_padre();
  }
  imprimir.push_back(nodo);

  // Imprimimos el vector empezando por el final para que salga en orden 
  for (int i = imprimir.size()-1; i > 0; i--)
    fout << imprimir[i]->get_id()+1 << "->";

  fout << imprimir[0]->get_id()+1 << ";" << coste_camino << ";" ;//<< generados_.size() << ";" << inspeccionados_.size() << endl;

  // Imprimimos vector generados
  for (int i = 0; i < generados_.size(); i++) 
    fout << generados_[i]->get_id()+1 << "[" << generados_[i]->get_nivel() << "] ";

  fout << ", ";

  // Imprimimos vector generados
  for (int i = 0; i < inspeccionados_.size(); i++) 
    fout << inspeccionados_[i]->get_id()+1 << "[" << inspeccionados_[i]->get_nivel() << "] ";
  fout << endl;

}
