#pragma once
#include <string>
#include "Counter.h"

typedef TreeMap<char, std::string> Dictionary;
typedef TreeMap<std::string, char> RDictionary; // reverse dictionary

class Coder
{
public:
	struct EncodedString
	{
		std::string str = "";
		std::string nospaces = ""; // without spaces
		RDictionary* dictionary = new RDictionary();
	};

private:
	Coder();

	static Counter* countCharacters(std::string raw) {
		Counter* counter = new Counter();
		for (int i = 0; i < raw.size(); i++) {
			char c = raw[i];
			try {
				counter->find(c)[0]++; // if increment for current character already exists
			}
			catch (std::exception e) {
				counter->insert(c, new int{ 1 });
			}
		}
		return counter;
	}

	static void encodingTree(Counter* counter, int len, std::string bits, Dictionary* dict) {
		if (counter->get_size() == 1) {
			dict->insert(counter->getKeys()[0], bits);
			return;
		}

		Counter::Sorted* sorted = counter->getSorted();
		Counter* left = new Counter();
		Counter* right = new Counter();
		int sum = 0;
		for (int i = sorted->size - 1; i >= 0; i--) {
			int key = sorted->keys[i];
			int* val = sorted->values[i];
			if (sum + *val <= len / 2) {
				left->insert(key, val);
				sum += *val;
			}
			else {
				right->insert(key, val);
			}
		}
		encodingTree(left, sum, bits + "0", dict); // go left subtree
		encodingTree(right, len - sum, bits + "1", dict); // go right subtree
	}

	static Dictionary* make_dictionary(Counter* counter, int len) {
		Dictionary* dict = new Dictionary();
		encodingTree(counter, len, "", dict);
		return dict;
	}

public:
	static EncodedString* encode(std::string raw, Counter::Sorted** pass_sorted = nullptr) {
		Counter* counter = countCharacters(raw);
		if (pass_sorted != nullptr) { // can pass the frequency table if needed
			*pass_sorted = counter->getSorted();
		}

		Dictionary* dict = make_dictionary(counter, raw.size());
		EncodedString* encoded = new EncodedString;
		for (int i = 0; i < raw.size(); i++) {
			std::string code = dict->find(raw[i]);
			encoded->str.append(code).append(" ");
			encoded->nospaces.append(code); // without space
		}

		char* keys = dict->getKeys();
		std::string* values = dict->getValues();
		for (int i = 0; i < dict->get_size(); i++) {  // reverse the dictionary
			encoded->dictionary->insert(values[i], keys[i]);
		}
		return encoded;
	}

	static std::string decode(std::string encoded, RDictionary* dict) {
		if (encoded[encoded.size() - 1] != ' ') {
			encoded.append(" "); // make sure that string ends with a space
		}
		std::string decoded = "";
		size_t pos;
		while ((pos = encoded.find(' ')) != encoded.npos) {
			try {
				decoded += dict->find(encoded.substr(0, pos));
			}
			catch (std::runtime_error e) {
			}
			encoded.erase(0, pos + 1);
		}
		return decoded;
	}
};