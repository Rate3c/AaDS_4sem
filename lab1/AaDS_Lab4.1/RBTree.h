#pragma once

#include<iostream>
#include "List.h"
#include "Stack.h"

using namespace std;

enum class RBColor {
	RED,
	BLACK
};

template<class T1, class T2>
class Element_RBtree {
public:
	RBColor color;
	T1 key;
	T2 value;
	Element_RBtree* parent;
	Element_RBtree* left;
	Element_RBtree* right;

	Element_RBtree() {
		this->color = RBColor::RED;
		this->key = 0;
		this->value = 0;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}
};

template<class T1, class T2>
class RedBlackTree {
public:
	Element_RBtree<T1, T2>* root;
	Element_RBtree<T1, T2>* nil;

	RedBlackTree() {
		nil = new Element_RBtree<T1, T2>();
		nil->color = RBColor::BLACK;
		root = nil;
		root->left = nil;
		root->right = nil;
	}

	void leftTurn(Element_RBtree<T1, T2>* xNode);
	void rightTurn(Element_RBtree<T1, T2>* yNode);

	void insert(T1 key, T2 value);
	void rebalancingTreeAfterInsertion(Element_RBtree<T1, T2>* Node);
	Element_RBtree<T1, T2>* find(T1 key);
	void remove(T1 key);
	void rebalancingTreeAfterRemove(Element_RBtree<T1, T2>* Node);
	List<Element_RBtree<T1, T2>*>* allNodesToList();
	void printTree();
	List<T1>* getKeys();
	List<T2>* getValues();
	void clear();
};

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::leftTurn(Element_RBtree<T1, T2>* xNode)
{
	Element_RBtree<T1, T2>* yNode = xNode->right;
	Element_RBtree<T1, T2>* bNode = yNode->left;
	xNode->right = bNode;
	if (bNode != nil)
		bNode->parent = xNode;
	Element_RBtree<T1, T2>* pNode = xNode->parent;
	yNode->parent = pNode;
	if (pNode == nullptr)
		root = yNode;
	else {
		if (pNode->left == xNode)
			pNode->left = yNode;
		else if (pNode->right == xNode)
			pNode->right = yNode;
	}
	yNode->left = xNode;
	xNode->parent = yNode;
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::rightTurn(Element_RBtree<T1, T2>* yNode)
{
	Element_RBtree<T1, T2>* xNode = yNode->left;
	Element_RBtree<T1, T2>* bNode = xNode->right;
	yNode->left = bNode;
	if (bNode != nil)
		bNode->parent = yNode;
	Element_RBtree<T1, T2>* pNode = yNode->parent;
	xNode->parent = pNode;
	if (pNode == nullptr)
		root = xNode;
	else {
		if (pNode->left == yNode)
			pNode->left = xNode;
		else if (pNode->right == yNode)
			pNode->right = xNode;
	}
	xNode->right = yNode;
	yNode->parent = xNode;
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::insert(T1 key, T2 value)
{
	if (root == nil) {
		Element_RBtree<T1, T2>* Node = new Element_RBtree<T1, T2>;
		Node->key = key;
		Node->value = value;
		Node->color = RBColor::BLACK;
		Node->left = nil;
		Node->right = nil;
		root = Node;
	}
	else {
		Element_RBtree<T1, T2>* Node = root;
		while (Node->left != nil || Node->right != nil) {
			if (key == Node->key)
				throw logic_error("This key is exist.");
			else if (key < Node->key) {
				if (Node->left != nil)
					Node = Node->left;
				else break;
			}
			else {
				if (Node->right != nil)
					Node = Node->right;
				else break;
			}
		}
		Element_RBtree<T1, T2>* newNode = new Element_RBtree<T1, T2>;
		newNode->key = key;
		newNode->value = value;
		newNode->left = nil;
		newNode->right = nil;
		newNode->parent = Node;
		if (newNode->key > Node->key)
			Node->right = newNode;
		else
			Node->left = newNode;
		newNode->color = RBColor::RED;
		rebalancingTreeAfterInsertion(newNode);
	}
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::rebalancingTreeAfterInsertion(Element_RBtree<T1, T2>* Node)
{
	while (Node->parent->color == RBColor::RED) {
		Element_RBtree<T1, T2>* Parent = Node->parent;
		Element_RBtree<T1, T2>* grandParent = Parent->parent;
		if (grandParent->left == Parent) {
			if (grandParent->right->color == RBColor::RED) {
				grandParent->left->color = RBColor::BLACK;
				grandParent->right->color = RBColor::BLACK;
				grandParent->color = RBColor::RED;
				Node = grandParent;
			}
			else {
				if (Parent->right == Node) {
					Node = Parent;
					leftTurn(Node);
					Parent = Node->parent;
					grandParent = Parent->parent;
				}
				Parent->color = RBColor::BLACK;
				grandParent->color = RBColor::RED;
				rightTurn(grandParent);
			}
		}
		else if (grandParent->right == Parent) {
			if (grandParent->left->color == RBColor::RED) {
				grandParent->left->color = RBColor::BLACK;
				grandParent->right->color = RBColor::BLACK;
				grandParent->color = RBColor::RED;
				Node = grandParent;
			}
			else {
				if (Parent->left == Node) {
					Node = Parent;
					rightTurn(Node);
					Parent = Node->parent;
					grandParent = Parent->parent;
				}
				Parent->color = RBColor::BLACK;
				grandParent->color = RBColor::RED;
				leftTurn(grandParent);
			}
		}
		if (Node == root)
			break;
	}
	root->color = RBColor::BLACK;
}

template<class T1, class T2>
inline Element_RBtree<T1, T2>* RedBlackTree<T1, T2>::find(T1 key)
{
	if (root == nil) {
		throw logic_error("Tree is empty.");
	}
	else {
		Element_RBtree<T1, T2>* Node = root;
		bool check = 0;
		while (Node != nil) {
			if (key == Node->key) {
				check = 1;
				break;
			}
			else if (key < Node->key)
				Node = Node->left;
			else
				Node = Node->right;
		}
		if (check == 0)
			throw invalid_argument("Key doen't exist in the tree.");
		else
			return Node;
	}
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::remove(T1 key)
{
	if (root == nil)
		throw logic_error("Tree is empty.");
	else {
		Element_RBtree<T1, T2>* Node = find(key);
		Element_RBtree<T1, T2>* xNode;
		RBColor originalColor = Node->color;
		if (Node->left == nil) {
			delete Node->left;
			xNode = Node->right;
			if (Node->parent->left == Node) {
				Node->parent->left = xNode;
			}
			else if (Node->parent->right == Node) {
				Node->parent->right = xNode;
			}
			xNode->parent = Node->parent;
		}
		else if (Node->right == nil) {
			delete Node->right;
			xNode = Node->left;
			if (Node->parent->left == Node) {
				Node->parent->left = xNode;
			}
			else if (Node->parent->right == Node) {
				Node->parent->right = xNode;
			}
			xNode->parent = Node->parent;
		}
		else {
			Element_RBtree<T1, T2>* yNode = Node->right;
			while (yNode->left != nil) {
				yNode = yNode->left;
			}
			if (yNode == Node->right) {
				originalColor = Node->color;
			}
			else {
				originalColor = yNode->color;
			}
			xNode = yNode->right;
			if (yNode->parent == Node) {
				xNode->parent = yNode;
				yNode->left = Node->left;
				yNode->right = xNode;
			}
			else {
				if (yNode->parent->right == yNode) {
					yNode->parent->right = xNode;
				}
				else if (yNode->parent->left == yNode) {
					yNode->parent->left = xNode;
				}
				yNode->left = Node->left;
				yNode->right = Node->right;
			}
			if (Node->parent->right == Node) {
				Node->parent->right = yNode;
			}
			else if (Node->parent->left == Node) {
				Node->parent->left = yNode;
			}
			yNode->parent = Node->parent;
			yNode->color = originalColor;
		}
		if (originalColor == RBColor::BLACK) {
			rebalancingTreeAfterRemove(xNode);
		}
		delete Node;
	}
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::rebalancingTreeAfterRemove(Element_RBtree<T1, T2>* Node)
{
	Element_RBtree<T1, T2>* wNode;
	while (Node != root && Node->color != RBColor::BLACK) {
		if (Node->parent->left = Node) {
			wNode = Node->parent->right;
			if (wNode->color == RBColor::RED) {
				wNode->color = RBColor::BLACK;
				Node->parent->color = RBColor::RED;
				leftTurn(Node->parent);
				wNode = Node->parent->right;
			}
			else if (wNode->left->color == RBColor::BLACK && wNode->right->color == RBColor::BLACK) {
				wNode->color = RBColor::RED;
				Node = Node->parent;
			}
			else if (wNode->right->color == RBColor::BLACK) {
				wNode->left->color = RBColor::BLACK;
				wNode->color = RBColor::RED;
				rightTurn(wNode);
				wNode = Node->parent->right;
			}
			else {
				wNode->color = Node->parent->color;
				Node->parent->color = RBColor::BLACK;
				wNode->right->color = RBColor::BLACK;
				leftTurn(Node->parent);
				Node = root;
			}
		}
		else if (Node->parent->right = Node) {
			wNode = Node->parent->left;
			if (wNode->color == RBColor::RED) {
				wNode->color = RBColor::BLACK;
				Node->parent->color = RBColor::RED;
				rightTurn(Node->parent);
				wNode = Node->parent->left;
			}
			else if (wNode->left->color == RBColor::BLACK && wNode->right->color == RBColor::BLACK) {
				wNode->color = RBColor::RED;
				Node = Node->parent;
			}
			else if (wNode->left->color == RBColor::BLACK) {
				wNode->right->color = RBColor::BLACK;
				wNode->color = RBColor::RED;
				leftTurn(wNode);
				wNode = Node->parent->left;
			}
			else {
				wNode->color = Node->parent->color;
				Node->parent->color = RBColor::BLACK;
				wNode->left->color = RBColor::BLACK;
				rightTurn(Node->parent);
				Node = root;
			}
		}
		Node->color = RBColor::BLACK;
	}
}

template<class T1, class T2>
inline List<Element_RBtree<T1, T2>*>* RedBlackTree<T1, T2>::allNodesToList()
{
	List<Element_RBtree<T1, T2>*>* list = new List<Element_RBtree<T1, T2>*>;
	Stack<Element_RBtree<T1, T2>*>* stack = new Stack<Element_RBtree<T1, T2>*>;
	Element_RBtree<T1, T2>* temp = root;
	while (temp != nil) {
		list->pushback(temp);
		if (temp->right != nil)
			stack->push(temp->right);
		if (temp->left != nil)
			temp = temp->left;
		else {
			if (!stack->isEmpty())
				temp = stack->pop();
			else
				temp = nil;
		}
	}
	return list;
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::printTree()
{
	if (root == nil)
		cout << "Tree is empty.";
	else {
		List<Element_RBtree<T1, T2>*>* listNode = allNodesToList();
		while (listNode->head != nullptr) {
			cout << "(Key: " << listNode->head->data->key << ", Value: " << listNode->head->data->value << ")\n";
			listNode->popfront();
		}
	}
}

template<class T1, class T2>
inline List<T1>* RedBlackTree<T1, T2>::getKeys()
{
	List<T1>* listKey = new List<T1>;
	List<Element_RBtree<T1, T2>*>* listNode = allNodesToList();
	Element_List<Element_RBtree<T1, T2>*>* temp = listNode->head;
	while (temp != nullptr) {
		listKey->pushback(temp->data->key);
		temp = temp->next;
	}
	return listKey;
}

template<class T1, class T2>
inline List<T2>* RedBlackTree<T1, T2>::getValues()
{
	List<T2>* listValue = new List<T2>;
	List<Element_RBtree<T1, T2>*>* listNode = allNodesToList();
	Element_List<Element_RBtree<T1, T2>*>* temp = listNode->head;
	while (temp != nullptr) {
		listValue->pushback(temp->data->value);
		temp = temp->next;
	}
	return listValue;
}

template<class T1, class T2>
inline void RedBlackTree<T1, T2>::clear()
{
	if (root == nil)
		throw logic_error("The tree is already empty.");
	else {
		Element_RBtree<T1, T2>* current = root;
		Stack<Element_RBtree<T1, T2>*>* stack = new Stack<Element_RBtree<T1, T2>*>;
		while (current != nil) {
			if (current->right != nil)
				stack->push(current->right);
			if (current->left != nil) {
				Element_RBtree<T1, T2>* temp = current->left;
				delete current;
				current = temp;
			}
			else if (!stack->isEmpty()) {
				delete current;
				current = stack->pop();
			}
			else {
				delete current;
				current = nil;
			}
		}
		root = current;
	}
}
