#pragma once

#include <iostream>
using namespace std;

template<class T>
class Element_List {
public:
	T data;
	Element_List* prev;
	Element_List* next;

	Element_List() {
		this->data = 0;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

template<class T>
class List {
public:
	Element_List<T>* head;
	Element_List<T>* tail;

	List() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	bool isEmpty();
	void pushback(T data);
	void pushfront(T data);
	void popback();
	void popfront();
	void clear();
};

template<class T>
inline bool List<T>::isEmpty()
{
	if (head == nullptr && tail == nullptr)
		return true;
	else if (head != nullptr && tail != nullptr)
		return false;
	else
		throw logic_error("Error");
}

template<class T>
inline void List<T>::pushback(T data)
{
	if (isEmpty()) {
		Element_List<T>* Node = new Element_List<T>();
		Node->data = data;
		head = Node;
		tail = Node;
	}
	else {
		Element_List<T>* Node = new Element_List<T>();
		Node->data = data;
		tail->next = Node;
		Node->prev = tail;
		tail = Node;
	}
}

template<class T>
inline void List<T>::pushfront(T data)
{
	if (isEmpty()) {
		Element_List<T>* Node = new Element_List<T>();
		Node->data = data;
		head = Node;
		tail = Node;
	}
	else {
		Element_List<T>* Node = new Element_List<T>();
		Node->data = data;
		head->prev = Node;
		Node->next = head;
		head = Node;
	}
}

template<class T>
inline void List<T>::popback()
{
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		if (tail->prev != nullptr) {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		else {
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
	}
}

template<class T>
inline void List<T>::popfront()
{
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		if (head->next != nullptr) {
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
	}
}

template<class T>
inline void List<T>::clear()
{
	Element_List<T>* Node = head;
	while (Node != nullptr) {
		Node = Node->next;
		delete head;
		head = Node;
	}
}
