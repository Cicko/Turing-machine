#include "Node.hpp"


// Constructors
Node::Node() {
  symbol = '$';
  right = NULL;
  left = NULL;
}

Node::Node(char simb) {
  symbol = simb;
  right = NULL;
  left = NULL;
}

Node::~Node(){
	symbol = '$';
}


// Setters
void Node::SetSymbol(char simb){
	symbol = simb;
}
void Node::SetRight(Node* der){
	right = der;
}
void Node::SetLeft(Node* izq){
  left = izq;
}


// Getters
char Node::GetSymbol() const {
  return symbol;
}
Node* Node::GetRight(){
	if(right == NULL){
		right = new Node ();
	}
	return right;
}
Node* Node::GetLeft(){
	if(left == NULL)
		left = new Node ();
	return left;
}
