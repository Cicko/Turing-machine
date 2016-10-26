/**
*
* @author: Rudolf Cicko
* @subject: Complejidad computacional (computational complexity), Universidad de La Laguna
* @date: 21-October-2016
* @description: This class represent a node in the turing tape, containing a symbol and adjacent neighbors
*
**/
#include <cstdlib>
#include <string>

using namespace std;


class Node {
  string symbol;  // with string we can make complex symbols like: a1, a2, a3....
  string white;   // white symbol.
  Node* right;
  Node* left;
public:
  Node(string white);
  Node(string white, string symbol);
  ~Node();
  void SetSymbol(string symbol);
  void SetWhite(string white);
  void SetRight(Node* right);
  void SetLeft(Node* left);
  string GetSymbol();
  string GetWhite();
  Node* GetRight ();
  Node* GetLeft ();
};
