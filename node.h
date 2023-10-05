#pragma ONCE

class Node {
 private:
  int id_;      // Ientificador 
  int nivel_;   // Profundidad en árbol
  float coste_; // Coste acumulado
  Node* padre_; // Puntero al padre

 public:
  Node();
  Node(int id, int nivel, float coste, Node* padre);

  void set_id(int id);
  void set_coste(float coste);

  int get_id();
  int get_nivel();
  float get_coste();
  Node* get_padre();

};
