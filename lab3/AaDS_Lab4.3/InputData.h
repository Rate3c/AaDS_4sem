#pragma once

#include<fstream>
#include"List.h"
#include<string>

void InputInFile(List<string>* data, ifstream& file) {
	while (!file.eof()) {
		string s1;
		getline(file, s1);
		data->push_back(s1);
	}
}