#include "pch.h"
#include "CppUnitTest.h"
#include "..\AaDS_CW4\FlowNetwork.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CW4tests
{
	TEST_CLASS(cw4unittest)
	{
	public:

		TEST_METHOD(TestMaxFlow1)
		{
			FlowNetwork* network = new FlowNetwork();
			network->add_arc('S', 'O', 3);
			network->add_arc('S', 'P', 3);
			network->add_arc('O', 'Q', 3);
			network->add_arc('O', 'P', 2);
			network->add_arc('P', 'R', 2);
			network->add_arc('Q', 'R', 4);
			network->add_arc('Q', 'T', 2);
			network->add_arc('R', 'T', 3);
			Assert::AreEqual(5, network->maximize_flow());
		}

		TEST_METHOD(TestMaxFlow2)
		{
			FlowNetwork* network = new FlowNetwork();
			network->add_arc('S', 'B', 5);
			network->add_arc('S', 'D', 7);
			network->add_arc('S', 'C', 6);
			network->add_arc('B', 'E', 1);
			network->add_arc('D', 'E', 2);
			network->add_arc('D', 'C', 9);
			network->add_arc('C', 'T', 1);
			network->add_arc('E', 'T', 8);
			Assert::AreEqual(4, network->maximize_flow());
		}

		TEST_METHOD(TestMaxFlow3)
		{
			FlowNetwork* network = new FlowNetwork();
			network->add_arc('S', 'D', 3);
			network->add_arc('D', 'F', 4);
			network->add_arc('E', 'B', 1);
			network->add_arc('E', 'T', 1);
			network->add_arc('S', 'B', 3);
			network->add_arc('D', 'E', 2);
			network->add_arc('F', 'T', 2);
			network->add_arc('C', 'S', 3);
			network->add_arc('C', 'D', 1);
			network->add_arc('B', 'C', 4);
			network->add_arc('C', 'E', 2);
			Assert::AreEqual(3, network->maximize_flow());
		}
	};
}
