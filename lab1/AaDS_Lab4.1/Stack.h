#pragma once

using namespace std;

template<class T>
class Stack {
private:
	class Element_Stack {
	public:
		T data;
		Element_Stack* next;
	};

	Element_Stack* top;
	size_t size;

public:
	Stack() {
		top = nullptr;
		size = 0;
	}

	~Stack() = default;

	void push(T x);
	T pop();
	bool isEmpty();
	size_t getsize();
};

	template<class T>
	inline void Stack<T>::push(T x)
	{
		if (isEmpty()) {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = nullptr;
			top = Node;
		}
		else {
			Element_Stack* Node = new Element_Stack;
			Node->data = x;
			Node->next = top;
			top = Node;
		}
		size++;
	}

	template<class T>
	inline T Stack<T>::pop()
	{
		if (isEmpty())
			throw runtime_error("Stack is empty.");
		else {
			Element_Stack* temp = top;
			if (top->next == nullptr)
				top = nullptr;
			else
				top = temp->next;
			T result = temp->data;
			delete temp;
			size--;
			return result;
		}
	}

	template<class T>
	inline bool Stack<T>::isEmpty()
	{
		if (top == nullptr)
			return true;
		else
			return false;
	}

	template<class T>
	inline size_t Stack<T>::getsize()
	{
		return size;
	}