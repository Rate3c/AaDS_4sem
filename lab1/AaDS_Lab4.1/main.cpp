#include <iostream>
#include "RBTree.h"

using namespace std;

int main() {
	RedBlackTree<int, int> tree;

	tree.insert(27, 1);
	tree.insert(7, 2);
	tree.insert(47, 3);
	tree.insert(6, 4);
	tree.insert(16, 5);
	tree.insert(36, 6);
	tree.insert(56, 7);
	tree.insert(10, 8);
	tree.insert(26, 9);
	tree.insert(15, 10);

	cout << "Red-Black Tree:\n";
	tree.printTree();

	cout << "\nList of keys: ";
	Element_List<int>* temp = tree.getKeys()->head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;

	cout << "\nList of values: ";
	temp = tree.getValues()->head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;

	cout << "\n Tree after removing keys: 27, 15:\n";
	tree.remove(27);
	tree.remove(15);
	tree.printTree();

	tree.clear();
}