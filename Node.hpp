/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 21-October-2016
* @description: This class represent a node in the turing tape, containing a symbol and adjacent neighbors
*
**/
#include <cstdlib>

#define INITIA_STATE 0
#define WHITE '$'

class Node {
  char symbol;
  Node* right;
  Node* left;
public:
  Node();
  Node(char symbol);
  ~Node();
  void SetSymbol(char symbol);
  void SetRight(Node* right);
  void SetLeft(Node* left);
  const char GetSymbol();
  Node* GetRight ();
  Node* GetLeft ();
};
