#include <iostream>
#include <fstream>
#include <string>
#include "FlowNetwork.h"

using namespace std;

int main()
{
    cout << "Name of the file: ";
    string filename;
    cin >> filename;
    cout << endl;

    ifstream file(filename + ".txt");
    FlowNetwork* network = new FlowNetwork();
    char from, to;
    int cap;

    while (file >> from >> to >> cap) {
        network->add_arc(from, to, cap);
    }

    cout << "Maximum flow: " << network->maximize_flow() << endl;
}