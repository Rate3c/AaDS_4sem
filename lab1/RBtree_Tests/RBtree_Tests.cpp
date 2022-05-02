#include "pch.h"
#include "CppUnitTest.h"
#include "../AaDS_Lab4.1/RBTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBtreeTests
{
	TEST_CLASS(RBtreeTests)
	{
	public:
		TEST_METHOD(Test_insert) {

			RedBlackTree<int, int> tree1;
			tree1.insert(29, 7);
			Assert::IsTrue(tree1.root->key == 29);
			Assert::IsTrue(tree1.root->value == 7);

			RedBlackTree<int, int> tree2;
			tree2.insert(33, 1);
			tree2.insert(13, 2);
			tree2.insert(53, 3);
			tree2.insert(11, 4);

			Element_List<Element_RBtree<int, int>*>* temp = tree2.allNodesToList()->head;
			Assert::IsTrue(temp->data->key == 33);
			Assert::IsTrue(temp->data->value == 1);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 13);
			Assert::IsTrue(temp->data->value == 2);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 11);
			Assert::IsTrue(temp->data->value == 4);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 53);
			Assert::IsTrue(temp->data->value == 3);

			bool exceptionThrown = false;

			//Insert the same key
			try {
				tree2.insert(33, 5);
			}
			catch (logic_error) {
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown);
		}

		TEST_METHOD(Test_remove) {

			//When tree is empty
			RedBlackTree<int, int> tree1;

			try {
				tree1.remove(7);
			}
			catch (logic_error error) {
				Assert::AreEqual("Tree is empty.", error.what());
			}

			RedBlackTree<int, int> tree2;
			tree2.insert(33, 1);
			tree2.insert(13, 2);
			tree2.insert(53, 3);
			tree2.insert(11, 4);
			tree2.insert(21, 5);
			tree2.remove(21);

			Element_List<Element_RBtree<int, int>*>* temp = tree2.allNodesToList()->head;
			Assert::IsTrue(temp->data->key == 33);
			Assert::IsTrue(temp->data->value == 1);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 13);
			Assert::IsTrue(temp->data->value == 2);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 11);
			Assert::IsTrue(temp->data->value == 4);
			temp = temp->next;
			Assert::IsTrue(temp->data->key == 53);
			Assert::IsTrue(temp->data->value == 3);

			//Remove nonexisting key
			try {
				tree2.remove(64);
			}
			catch (invalid_argument error) {
				Assert::AreEqual("Key doen't exist in the tree.", error.what());
			}
		}

		TEST_METHOD(test_find) {

			//When tree is empty
			RedBlackTree<int, int> tree1;
			try {
				tree1.find(4);
			}
			catch (logic_error error) {
				Assert::AreEqual("Tree is empty.", error.what());
			}

			RedBlackTree<int, int> tree2;
			tree2.insert(33, 1);
			tree2.insert(13, 2);
			tree2.insert(53, 3);
			tree2.insert(11, 4);

			Assert::IsTrue(tree2.find(53)->key == 53);
			Assert::IsTrue(tree2.find(53)->value == 3);

			//Key to find does not exist
			try {
				tree2.find(64);
			}
			catch (invalid_argument error) {
				Assert::AreEqual("Key doen't exist in the tree.", error.what());
			}
		}

		TEST_METHOD(Test_getkeys) {
			RedBlackTree<int, int> tree;
			tree.insert(33, 1);
			tree.insert(13, 2);
			tree.insert(53, 3);
			tree.insert(11, 4);

			Element_List<int>* temp = tree.getKeys()->head;
			Assert::IsTrue(temp->data == 33);
			temp = temp->next;
			Assert::IsTrue(temp->data == 13);
			temp = temp->next;
			Assert::IsTrue(temp->data == 11);
			temp = temp->next;
			Assert::IsTrue(temp->data == 53);
		}

		TEST_METHOD(Test_getvalues) {
			RedBlackTree<int, int> tree;
			tree.insert(33, 1);
			tree.insert(13, 2);
			tree.insert(53, 3);
			tree.insert(11, 4);

			Element_List<int>* temp = tree.getValues()->head;
			Assert::IsTrue(temp->data == 1);
			temp = temp->next;
			Assert::IsTrue(temp->data == 2);
			temp = temp->next;
			Assert::IsTrue(temp->data == 4);
			temp = temp->next;
			Assert::IsTrue(temp->data== 3);
		}

		TEST_METHOD(Test_clear) {
			RedBlackTree<int, int> tree;

			//Tree is empty
			try {
				tree.clear();
			}
			catch (logic_error error) {
				Assert::AreEqual("The tree is already empty.", error.what());
			}

			tree.insert(33, 1);
			tree.insert(13, 2);
			tree.insert(53, 3);
			tree.insert(11, 4);
			tree.clear();
			Assert::IsTrue(tree.root == tree.nil);
		}
	};
}
