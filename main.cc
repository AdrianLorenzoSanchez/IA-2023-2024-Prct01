#include <iostream>
#include "graph.h"

using namespace std;

int main() {

  string fichero; // fichero entrada
  bool salir = false;

  while (!salir) {
    cout << "Especifica fichero de entrada [0 salir]: "; cin >> fichero;
    if (fichero == "0") 
      salir = true;
    else {
      Graph grafo(fichero);
      grafo.algoritmo();
    }
  }

}