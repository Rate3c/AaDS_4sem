#pragma once
#include<string>
#include "List.h"
#include "TreeMap.h"

class AdjList {
	class Vertex {
	public:
		Vertex(int index_City = 0, double price = 0) :index_City(index_City), price(price) {}
		int index_City;
		double price;
	};

private:
	List<Vertex>* graph;
	TreeMap<string, int>* nameToIndex;
	TreeMap<int, string>* indexToName;
	int size;
	const int INF = INT_MAX;

public:
	AdjList(List<string>* data) {
		graph = new List<Vertex>();
		indexToName = new TreeMap<int, string>();
		nameToIndex = new TreeMap<string, int>();
		int N = data->get_size();
		int indexCity = 0;

		for (int i = 0; i < N; i++) {
			string CurString = data->at(i);
			int cur = CurString.find(';');
			int cur1 = CurString.find(';', cur + 1);
			string cityName1 = CurString.substr(0, cur);					//get the first city
			string cityName2 = CurString.substr(cur + 1, cur1 - cur - 1);	//get the second city
			cityName2.erase(0, 1);											//deleting the space

			if (!nameToIndex->checkForAvailability(cityName1)) {
				nameToIndex->insert(cityName1, indexCity);
				indexToName->insert(indexCity, cityName1);
				indexCity++;
			}
			if (!nameToIndex->checkForAvailability(cityName2)) {
				nameToIndex->insert(cityName2, indexCity);
				indexToName->insert(indexCity, cityName2);
				indexCity++;
			}
		}

		size = indexCity;
		graph = new List<Vertex>[size];
		//fill in the list of prices(adjacencies)
		for (int i = 0; i < N; i++) {
			int price_1_to_2 = INF;
			int price_2_to_1 = INF;
			string CurString = data->at(i);
	
			int cur = CurString.find(';');					//first entry 
			int cur1 = CurString.find(';', cur + 1);		//second entry
			int cur2 = CurString.find(';', cur1 + 1);		//third entry 
			int cur3 = CurString.find(';', cur2 + 1);		//fourth entry
			string cityName1 = CurString.substr(0, cur);					// get the first city
			string cityName2 = CurString.substr(cur + 1, cur1 - cur - 1);	//get the second city
			cityName2.erase(0, 1);	// delete the space

			if (CurString.substr(cur1 + 2, cur2 - 2 - cur1) != "N/A") {
				price_1_to_2 = stof(CurString.substr(cur1 + 2, cur2 - 2 - cur1));
			}

			if (CurString.substr(cur2 + 2, cur3 - 1) != "N/A") {
				price_2_to_1 = stoi(CurString.substr(cur2 + 2, cur3 - 2 - cur2));
			}

			if (price_1_to_2 != INF) {
				Vertex v1(nameToIndex->find(cityName2), price_1_to_2);
				graph[nameToIndex->find(cityName1)].push_back(v1);
			}

			if (price_2_to_1 != INF) {
				Vertex v2(nameToIndex->find(cityName1), price_2_to_1);
				graph[nameToIndex->find(cityName2)].push_back(v2);
			}
		}
	}

	string DijkstrasAlgorithm(string city_Start, string city_End) {
		if (city_Start != city_End) {
			string answer;

			while (!nameToIndex->checkForAvailability(city_Start)) {
				cout << "The departure city is missing, enter it again" << endl;
				cin >> city_Start;
			}
			while (!nameToIndex->checkForAvailability(city_End)) {
				cout << "The arrival city is missing, enter it again" << endl;
				cin >> city_End;
			}

			int indexCity = 0;
			int index_start_vertex = nameToIndex->find(city_Start); //find the index of the city of departure
			bool* visited = new bool[size];
			int* distance = new int[size];  //distances from the starting vertex
			for (int i = 0; i < size; i++) {
				distance[i] = INF;
				visited[i] = false;
			}
			distance[index_start_vertex] = 0;
			int* path = new int[size];

			for (int i = 0; i < size; ++i) {
				int vertex = -1;
				for (int j = 0; j < size; ++j)
					if (!visited[j] && (vertex == -1 || distance[j] < distance[vertex]))
						vertex = j;
				if (distance[vertex] == INF)
					break;
				visited[vertex] = true;
				for (size_t j = 0; j < graph[vertex].get_size(); ++j) {
					int to = graph[vertex].at(j).index_City,
						len = graph[vertex].at(j).price;
					if (distance[vertex] + len < distance[to]) {
						distance[to] = distance[vertex] + len;
						path[to] = vertex;
					}
				}
			}

			int startIndex = nameToIndex->find(city_Start);
			int endIndex = nameToIndex->find(city_End);  //search for the arrival city index

			if (distance[endIndex] != INF) {
				List<int>* path_cur = new List<int>();
				for (int v = endIndex; v != startIndex; v = path[v])
					path_cur->push_back(v);
				path_cur->push_back(startIndex);
				path_cur->reverse();
				answer += "Cheapest route:\n";
				string cur;
				for (int i = 0; i < path_cur->get_size(); i++) {
					cur += "->";
					cur += indexToName->find(path_cur->at(i)) + ' ';
				}
				cur.erase(0, 2);
				answer += cur + "\nThe cheapest route for the price:" + to_string(distance[endIndex]) + '\n';
			}
			else {
				answer = "This route can't be built";
			}
			return answer;
		}
		else throw exception("Arrival city can't be equal to depatured city");
	}
};