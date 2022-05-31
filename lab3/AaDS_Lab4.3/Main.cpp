#include<iostream>
#include"DijkstrasAlgorithm.h"
#include <fstream>
#include"InputData.h"

using namespace std;

int main() {
	try {
		ifstream input("airport.txt");
		int* path = NULL;
		int* d = NULL;
		List<string>* flights = new List<string>();
		string city_Start;
		string city_End;
		InputInFile(flights, input);

		cout << "Flights: " << endl;
		for (int i = 0; i < flights->get_size(); i++)
			cout << flights->at(i) << endl;
		cout << endl;

		cout << "Enter the start point" << endl;
		getline(cin, city_Start);

		cout << "Enter the finish point" << endl;
		getline(cin, city_End);

		AdjList* adj = new AdjList(flights);
		cout << adj->DijkstrasAlgorithm(city_Start, city_End);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}
}