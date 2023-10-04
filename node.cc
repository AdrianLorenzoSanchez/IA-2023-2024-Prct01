#include <iostream>
#include "node.h"

// Constructor por defecto
Node::Node() {
  id_ = 0;
  nivel_= 0;
  coste_ = 0;
  padre_ = NULL;
}

// Constructor parametrizado
Node::Node(int id, int nivel, float coste, Node* padre) {
  id_ = id;
  nivel_ = nivel;
  coste_ = coste;
  padre_ = padre;
}

// setters
void Node::set_id(int id) {
  id_ = id;
}
void Node::set_coste(float coste) {
  coste_ = coste;
}

// getters
int Node::get_id() {
  return id_;
}
int Node::get_nivel() {
  return nivel_;
}
float Node::get_coste() {
  return coste_;
}
Node* Node::get_padre() {
  return padre_;
}