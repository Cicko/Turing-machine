#include "Node.hpp"



Node::Node(string aWhite) {
  white = aWhite;
  symbol = white;
  right = NULL;
  left = NULL;
}

Node::Node(string aWhite, string aSymbol) {
  white = aWhite;
  symbol = aSymbol;
  right = NULL;
  left = NULL;
}

Node::~Node(){
}


// Setters
void Node::SetSymbol(string simb){
  cout << "Symbol: " << simb << endl;
	symbol = simb;
}
void Node::SetWhite(string aWhite) {
  white = aWhite;
}
void Node::SetRight(Node* der){
	right = der;
}
void Node::SetLeft(Node* izq){
  left = izq;
}


// Getters
string Node::GetSymbol() {
  return symbol;
}
string Node::GetWhite() {
  return white;
}

Node* Node::GetRight(){
	if(right == NULL){
		right = new Node (white);
	}
	return right;
}
Node* Node::GetLeft(){
	if(left == NULL)
		left = new Node (white);
	return left;
}
