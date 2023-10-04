#pragma ONCE

class Node {
 private:
  int id_;
  int nivel_;
  float coste_;
  Node* padre_;

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
