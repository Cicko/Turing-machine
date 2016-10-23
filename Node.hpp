/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 21-October-2016
* @description: This class represent a node in the turing tape, containing a symbol and adjacent neighbors
*
**/

#define INITIA_STATE 0

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
  const Node* getRight ();
  const Node* getLeft ();
}
