#pragma once

#define BLACK false
#define RED true

template<class K, class T>
class TreeMap
{
private:
	struct Node {
		K key;
		T val;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		bool color = BLACK;
	};

	Node* nil = new Node;
	Node* root = nil;
	size_t size = 0;

	void leftTurn(Node* x) {
		Node* y = x->right;			// y is right subtree
		Node* p = x->parent;
		x->right = y->left;			// node x becames parent for left subtree of y
		if (y->left != nil) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x == root) {			// node x is root
			root = y;
		}
		else if (x == p->left) {	// node x is left child
			p->left = y;
		}
		else {						// node x is right child
			p->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightTurn(Node* y) {
		Node* x = y->left;			// x is left subtree
		Node* p = y->parent;
		y->left = x->right;			// node y becames parent for right subtree of x
		if (x->right != nil) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y == root) {			// node y is root
			root = x;
		}
		else if (y == p->right) {	// node y is right child
			p->right = x;
		}
		else {						// node y is left child
			p->left = x;
		}
		x->right = y;
		y->parent = x;
	}

	void move_node(Node* node, Node* newPosition) {
		if (newPosition->parent == nullptr) {					// newPosition is root
			root = node;
		}
		else if (newPosition->parent->left == newPosition) {	// newPosition is left child
			newPosition->parent->left = node;
		}
		else {													// newPosition is right child
			newPosition->parent->right = node;
		}
		node->parent = newPosition->parent;
	}

	Node* findNode(K key) {
		if (root == nil) {
			throw std::runtime_error("Map is empty");
		}
		Node* node = root;
		while (key != node->key) {
			if (key < node->key) {
				node = node->left;
			}
			else {
				node = node->right;
			}
			if (node == nil) { // no such key in the tree
				throw std::runtime_error("Key does not exists");
			}
		}
		return node;
	}

	void clearNode(Node* node) { // clear node 
		if (node == nil) {
			return;
		}
		clearNode(node->left);
		clearNode(node->right);
		delete node;
	}

	void listOfKeys(Node* node, K* elems) { // make list of keys 
		static int length = 0;
		if (node == nil) {
			return;
		}
		listOfKeys(node->left, elems);
		elems[length] = node->key;
		length++;
		listOfKeys(node->right, elems);
		if (length == size) {
			length = 0;
		}
	}

	void listOfValues(Node* node, T* elems) { // make list of values
		static int length = 0;
		if (node == nil) {
			return;
		}
		listOfValues(node->left, elems);
		elems[length] = node->val;
		length++;
		listOfValues(node->right, elems);
		if (length == size) {
			length = 0;
		}
	}

public:
	void insert(K key, T val) {
		Node* newNode = new Node;
		newNode->key = key;
		newNode->val = val;
		// insert
		if (root == nil) { // tree is empty
			root = newNode;
			root->color = BLACK;
			root->left = nil;
			root->right = nil;
			size++;
			return;
		}
		Node* node = root;
		while (true) {
			if (key == node->key) {
				throw std::runtime_error("Key already exists");
			}
			if (key > node->key) {
				if (node->right != nil) {
					node = node->right;
				}
				else {
					node->right = newNode;
					break;
				}
			}
			else {
				if (node->left != nil) {
					node = node->left;
				}
				else {
					node->left = newNode;
					break;
				}
			}
		}
		newNode->parent = node;
		newNode->left = nil;
		newNode->right = nil;
		newNode->color = RED;
		size++;

		// rebalancing tree
		Node* p = newNode->parent;	// parent
		Node* gp = p->parent;		// grand parent
		while (p->color == RED) {
			p = newNode->parent;
			gp = p->parent;
			if (p == gp->left) {
				if (gp->right->color == RED) {
					gp->left->color = BLACK;
					gp->right->color = BLACK;
					gp->color = RED;
					newNode = gp;
				}
				else {
					if (p->color == RED && newNode == p->right) {
						newNode = p;
						leftTurn(newNode);
					}
					if (p->color == RED) {
						p->color = BLACK;
						gp->color = RED;
						rightTurn(gp);
					}
				}
			}
			else {
				if (gp->left->color == RED) {
					gp->left->color = BLACK;
					gp->right->color = BLACK;
					gp->color = RED;
					newNode = gp;
				}
				else {
					if (p->color == RED && newNode == p->left) {
						newNode = p;
						rightTurn(newNode);
					}
					if (p->color == RED) {
						p->color = BLACK;
						gp->color = RED;
						leftTurn(gp);
					}
				}
			}
		}
		root->color = BLACK;
	}

	T find(K key) {
		return findNode(key)->val;
	}

	void remove(K key) {
		Node* nodeToDelete = findNode(key);

		Node* x;
		bool orig_color = nodeToDelete->color;
		if (nodeToDelete->left == nil) {
			x = nodeToDelete->right;
			move_node(x, nodeToDelete);
		}
		else if (nodeToDelete->right == nil) {
			x = nodeToDelete->left;
			move_node(x, nodeToDelete);
		}
		else {
			Node* y = nodeToDelete->right;
			while (y->left != nil) {
				y = y->left;
			}
			orig_color = y->color;
			x = y->right;
			if (y->parent == nodeToDelete) {
				x->parent = y;
			}
			else {
				move_node(x, y);
				y->right = nodeToDelete->right;
				y->right->parent = y;
			}
			move_node(y, nodeToDelete);
			y->left = nodeToDelete->left;
			y->left->parent = y;
			y->color = nodeToDelete->color;
		}
		delete nodeToDelete;
		size--;

		if (orig_color != BLACK) {
			return;
		}
		// rebalancing tree
		Node* w;
		while (x != root && x->color == BLACK) {
			if (x->parent->left == x) { // x is left child
				w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftTurn(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						rightTurn(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftTurn(x->parent);
					x = root;
				}
			}
			else { // x is right child
				w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightTurn(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftTurn(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightTurn(x->parent);
					x = root;
				}
			}
			x->color = BLACK;
		}
	}

	void clear() {
		clearNode(root);
		root = nil;
		size = 0;
	}

	size_t get_size() {
		return size;
	}

	K* getKeys() {
		K* keys = new K[size];
		listOfKeys(root, keys);
		return keys;
	}

	T* getValues() {
		T* values = new T[size];
		listOfValues(root, values);
		return values;
	}

	friend std::ostream& operator<<(std::ostream& stream, TreeMap& map) {
		K* keys = map.getKeys();
		T* values = map.getValues();
		stream << "{\n";
		for (int i = 0; i < map.get_size(); i++) {
			stream << "\t" << keys[i] << " -> " << values[i] << "\n";
		}
		stream << "}\n";
		return stream;
	}

	void print() {
		std::cout << *this;
	}

	~TreeMap() {
		clear();
	}
};