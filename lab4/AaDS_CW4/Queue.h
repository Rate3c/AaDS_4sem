#pragma once

template<class T>
class Queue
{
private:
	struct Elem {
		Elem* next = nullptr;
		Elem* prev = nullptr;
		T data = nullptr;
	};

	Elem* first = new Elem;
	Elem* last = first;


public:
	Queue(T data) {
		first->data = data;
	}

	~Queue() {
		clear();
	}

	void clear() {
		while (!empty()) {
			pop();
		}
	}

	// Push back new element
	void push(T data) {
		Elem* new_last = new Elem;
		new_last->data = data;
		if (first != nullptr) {
			new_last->prev = last;
			last->next = new_last;
		}
		else { // If queue was empty
			first = new_last;
		}
		last = new_last;
	}

	// Pop front element
	T pop() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		T data = first->data;
		if (first->next != nullptr) {
			first = first->next;
			delete first->prev;
			first->prev = nullptr;
		}
		else { // If queue becomes empty
			delete first, last;
			first = nullptr;
			last = nullptr;
		}
		return data;
	}

	bool empty() {
		return (first == nullptr);
	}
};