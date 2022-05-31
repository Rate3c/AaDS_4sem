#pragma once
#define RED true
#define BLACK false

#include"List.h"
#include<string>

using namespace std;
template<typename T, typename V>
class TreeMap {
public:
	class Node
	{
	public:
		Node(bool color = RED, T key = T(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, V value = V()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		T key;
		V value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};

	~TreeMap() {
		if (this->Top != NULL)
			this->clear();
		Top = NULL;
		delete Leaf;
		Leaf = NULL;
	}

	TreeMap(Node* Top = NULL, Node* Leaf = new Node(0)) :Top(Top), Leaf(Leaf) {}

	void insert(T key, V value) {
		if (this->Top != NULL) {
			Node* node = NULL;
			Node* parent = NULL;
			for (node = this->Top; node != Leaf; )// Search leaf for new element 
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					throw std::out_of_range("key is repeated");
			}
			node = new Node(RED, key, Leaf, Leaf, Leaf, value);
			node->parent = parent;
			if (parent != Leaf) {
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			RebalanceTree(node);
		}
		else {
			this->Top = new Node(BLACK, key, Leaf, Leaf, Leaf, value);
		}
	}

	List<T>* getKeys() {
		List<T>* list = new List<T>();
		this->ListKeyOrValue(1, list);
		return list;
	}

	List<V>* getValues() {
		List<V>* list = new List<V>();
		this->ListKeyOrValue(2, list);
		return list;
	}

	V find(T key) {
		Node* node = Top;
		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node->value;
		else
			throw std::out_of_range("Key is missing");
	}

	void clear() {
		this->clear(this->Top);
		this->Top = NULL;
	}

	bool checkForAvailability(T key) { //check if there is such key in the tree
		Node* node = Top;
		while (node != nullptr && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != nullptr)
			return true;
		else
			return false;
	}

	void deleteKey(T key) {
		Node* needed = Top;
		while (needed->key != key) {
			if (needed->key < key)
				needed = needed->right;
			else
				needed = needed->left;
		}
		deleteNode(needed);
	}

private:
	Node* Top;
	Node* Leaf;
	Node* get_node(T key) {
		Node* node = Top;

		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node;
	}

	void deleteNode(Node* current) {
		Node* fixed, * changed;


		// delete node current from tree  
		if (!current || current == Leaf) return;

		if (current->left == Leaf || current->right == Leaf) {
			// changed has a Leaf node as a child
			changed = current;
		}
		else {
			// find tree successor with a Leaf node as a child
			changed = current->right;
			while (changed->left != Leaf) changed = changed->left;
		}

		// fixed is changed's only child
		if (changed->left != Leaf)
			fixed = changed->left;
		else
			fixed = changed->right;

		// remove changed from the parent chain
		fixed->parent = changed->parent;
		if (changed->parent)
			if (changed == changed->parent->left)
				changed->parent->left = fixed;
			else
				changed->parent->right = fixed;
		else
			Top = fixed;

		if (changed != current) {
			current->key = changed->key;
			current->value = changed->value;
		}

		if (changed->color == BLACK)
			RebalanceTree(fixed);
	}

	void clear(Node* tree) {
		if (tree != Leaf) {
			clear(tree->left);
			clear(tree->right);
			delete tree;
		}
	}

	void ListKeyOrValue(int mode, List<T>* list) {
		if (this->Top != Leaf)
			this->KeyOrValue(Top, list, mode);
		else
			throw std::out_of_range("Tree empty!");
	}

	void KeyOrValue(Node* tree, List<T>* list, int mode) {

		if (tree != Leaf) {
			KeyOrValue(tree->left, list, mode);
			if (mode == 1)
				list->push_back(tree->key);
			else
				list->push_back(tree->value);
			KeyOrValue(tree->right, list, mode);
		}
	}

	Node* grandparent(Node* cur) {
		if ((cur != Leaf) && (cur->parent != Leaf))
			return cur->parent->parent;
		else
			return Leaf;
	}

	Node* uncle(Node* cur) {
		Node* cur1 = grandparent(cur); //assisting node
		if (cur1 == Leaf)
			return Leaf; // No grandparent means no uncle
		if (cur->parent == cur1->left)
			return cur1->right;
		else
			return cur1->left;
	}

	Node* find_key(T key) {
		Node* node = this->Top;
		while (node != Leaf && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != Leaf)
			return node;
		else
			throw std::out_of_range("Key is missing");
	}

	//rebalance tree
	void RebalanceTree(Node* node) {
		Node* uncle;
		while (node != this->Top && node->parent->color == RED)
		{
			if (node->parent == this->grandparent(node)->left)
			{
				uncle = this->uncle(node);
				if (uncle->color == RED) {
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						this->leftTurn(node);
					}
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->rightTurn(this->grandparent(node));
				}
			}
			else {
				uncle = this->uncle(node);
				if (uncle->color == RED) {
					node->parent->color = BLACK;
					uncle->color = BLACK;
					this->grandparent(node)->color = RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						this->rightTurn(node);
					}
					node->parent->color = BLACK;
					this->grandparent(node)->color = RED;
					this->leftTurn(this->grandparent(node));
				}
			}
		}
		this->Top->color = BLACK;
	}

	void leftTurn(Node* node) {
		Node* right = node->right;
		// Create node->right link
		node->right = right->left;
		if (right->left != Leaf)
			right->left->parent = node;
		// Create right->parent link
		if (right != Leaf)
			right->parent = node->parent;
		if (node->parent != Leaf) {
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->Top = right;
		}
		right->left = node;
		if (node != Leaf)
			node->parent = right;
	}

	void rightTurn(Node* node) {
		Node* left = node->left;
		// Create node->left link
		node->left = left->right;
		if (left->right != Leaf)
			left->right->parent = node;
		// Create left->parent link
		if (left != Leaf)
			left->parent = node->parent;
		if (node->parent != Leaf) {
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else {
			this->Top = left;
		}
		left->right = node;
		if (node != Leaf)
			node->parent = left;
	}
};