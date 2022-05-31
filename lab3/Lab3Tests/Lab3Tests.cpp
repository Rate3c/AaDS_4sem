#include "pch.h"
#include "CppUnitTest.h"
#include "../AaDS_Lab4.3/DijkstrasAlgorithm.h"
#include "../AaDS_Lab4.3/InputData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

ifstream input("D:\\VisualStudio\\My Projects\\AsDS\\AaDS_Lab4.3\\airport.txt");
List<string>* flights = new List<string>();

namespace Lab3Tests
{
	TEST_CLASS(Lab3Tests)
	{
	public:
		
		TEST_METHOD(TestAvailablePath)
		{
			string city_Start = "Madrid";
			string city_End = "Washington";
			InputInFile(flights, input);
			AdjList* adj = new AdjList(flights);
			string cur = "Cheapest route:\nMadrid ->Washington \nThe cheapest route for the price:400\n";
			Assert::AreEqual(adj->DijkstrasAlgorithm(city_Start, city_End), cur);
		}
		TEST_METHOD(TestUnavailablePath)
		{
			string city_Start = "NYC";
			string city_End = "Oslo";
			InputInFile(flights, input);
			AdjList* adj = new AdjList(flights);
			string cur = "This route can't be built";
			Assert::AreEqual(adj->DijkstrasAlgorithm(city_Start, city_End), cur);
		}
		TEST_METHOD(TestPathExeption)
		{
			try {
				string city_Start = "LA";
				string city_End = "LA";
				InputInFile(flights, input);
				AdjList* adj = new AdjList(flights);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "End city can't be equal to start city");
			}
		}
		TEST_METHOD(TestePath)
		{
			string city_Start = "Sydney";
			string city_End = "Rio";
			InputInFile(flights, input);
			AdjList* adj = new AdjList(flights);
			string cur = "Cheapest route:\nSydney ->LA ->Rio \nThe cheapest route for the price:4400\n";
			Assert::AreEqual(adj->DijkstrasAlgorithm(city_Start, city_End), cur);
		}
	};
}
