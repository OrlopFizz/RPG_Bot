#include <iostream>
#include <vector>
#include <algorithm>
struct Node { //un nodo de un arbol debe contener un valor que contiene, y un listado de sus hijos. 
	std::string value;
	std::vector<Node*> children;
	Node* parent;
	int level;

	Node() {};
	Node(std::string pvalue) : value{ pvalue }, level{ 1 } {}; //un nodo sin padre es una raiz, es decir, tiene un nivel de 1.
	Node(std::string pvalue, int plevel) : value{ pvalue }, level{ plevel } {};

	void add_child(Node*& const pnode) {
		(*pnode).level = (*this).level + 1;
		(*this).children.push_back(pnode);
		(*pnode).parent = this;
	}

	void add_children(Node* pnodes[], int array_size) {
		for (int i = 0; i < array_size; ++i) {
			(*this).add_child(pnodes[i]);
		}
	}

	/*
	get tree of current node as root.
	it returns a string with every value in the tree represented:
	every element is organized in a different line ('\n')
	with different levels represented with differing tabs ('\n')
	every parent has the next representation of their children, meaning this is a depth-first alg.
	*/
	void get_tree(std::string& out) const {
		//get value of the current node, adding
		out.append(this->get_string());
		//out.append("\n");
		std::for_each(this->children.begin(), this->children.end(), [&out](Node* const child) {
			out.append("\n");
			child->get_tree(out);
			});
	}

	std::string get_string() const {
		std::string out{};
		int level = (this->level) - 1;
		for (int i = 0; i < level; ++i) {
			out.append("\t");
		}
		out.append(this->value);
		return out;
	};
};