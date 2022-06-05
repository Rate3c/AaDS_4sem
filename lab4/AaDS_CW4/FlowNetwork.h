#pragma once
#include "TreeMap.h"
#include "Queue.h"

class FlowNetwork
{
private:
	struct Arc {
		const int init_capacity;		// initial capacity
		int capacity;					// residual capacity
		int flow = 0;
		Arc(int cap) : init_capacity(cap) {
			capacity = cap;
		}
	};

	struct Node {
		TreeMap<Node*, Arc*>* arcs = new TreeMap<Node*, Arc*>();
		Node* mark = nullptr;			// for breadth first search
	};

	Node* source = new Node;
	Node* sink = new Node;
	TreeMap<char, Node*>* nodes = new TreeMap<char, Node*>();

	void reset_marks() {
		Node** node_arr = nodes->getValues();
		for (int i = 0; i < nodes->get_size(); i++) {
			node_arr[i]->mark = nullptr;
		}
	}

public:
	FlowNetwork() {
		nodes->insert('S', source);
		nodes->insert('T', sink);
	}

	void add_arc(char from, char to, int capacity) {
		Node* node;
		try {
			node = nodes->find(from);
		}
		catch (std::runtime_error e) {
			node = new Node;
			nodes->insert(from, node);
		}
		Node* target;
		try {
			target = nodes->find(to);
		}
		catch (std::runtime_error e) {
			target = new Node;
			nodes->insert(to, target);
		}
		node->arcs->insert(target, new Arc(capacity));
		target->arcs->insert(node, new Arc(0));
	}

	int maximize_flow() {
		int flow = 0;

		while (true) {
			// breadth first search
			reset_marks();
			Queue<Node*>* queue = new Queue<Node*>(source);
			while (!queue->empty()) {
				Node* u = queue->pop();
				Node** v = u->arcs->getKeys();
				for (int i = 0; i < u->arcs->get_size(); i++) {
					if (u->arcs->find(v[i])->capacity <= 0) continue; // skip if arc's capacity is zero
					if (v[i]->mark != nullptr) continue;
					v[i]->mark = u;				// save previous node
					if (v[i] == sink) {			// the best path
						queue->clear();
						break;
					}
					queue->push(v[i]);
				}
			}

			if (sink->mark == nullptr) break;	// path not found

			// find minimum capacity
			int min_cap = INT32_MAX;
			Node* curr = sink;
			while (curr != source) {
				Node* prev = curr->mark;
				int cap = prev->arcs->find(curr)->capacity;
				if (cap < min_cap) {
					min_cap = cap;
				}
				curr = curr->mark;
			}

			// modify the network
			curr = sink;
			while (curr != source) {
				Node* prev = curr->mark;
				Arc* arc = prev->arcs->find(curr);
				arc->flow += min_cap;
				arc->capacity -= min_cap;
				Arc* reverse_arc = curr->arcs->find(prev);
				reverse_arc->flow -= min_cap;
				reverse_arc->capacity += min_cap;
				curr = curr->mark;
			}

			flow += min_cap;
		}

		return flow;
	}
};
