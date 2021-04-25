#include "pch.h"
#include "CppUnitTest.h"
#include "..\dijkstra.h"
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LR3UT
{
	TEST_CLASS(LR3UT)
	{
	public:
		
		TEST_METHOD(TestDijkstra)
		{
			srand(time(NULL));

			std::ifstream graphData; // For reading the graph

			graphData.open("../graph.txt", std::ios_base::in | std::ios_base::binary);

			size_t vertsCount = 0, from = 0 , to = 0;
			int result = 0;

			graphNode *graph = buildAdjList(graphData, vertsCount); // Building the adjacency array

			from = rand() % vertsCount;

			do			
				to = rand() % vertsCount;
			while (from == to);

			// If no edges are coming out of the 'from' vertex then there is no point in going further
			if (graph[from].adjVerts().isEmpty())
				std::cout << "'From' vertex does not have edges coming out of it\n";
			else
			{
				dijkstra(graph, vertsCount, from, to, result); // Finding the shortest path

				if (result != INT_MAX) // If there is a path
				{
					list<int> paths; // List of all paths
					int dist = 0; // Distance variable
					bool *visited = new bool[vertsCount]; // Visited array

					for (size_t i = 0; i < vertsCount; i++) // Filling up visited array
						visited[i] = false;
					visited[from] = true; // Setting starting node as visited

					findAllPaths(graph, vertsCount, visited, paths, dist, from, to); // Finding all paths

					// Iterating through the list to check if there are paths shorter than the one found by dijkstra function
					iterator<int> *it = paths.createIterator(0);
					int temp = 0;
					while (it->hasNext())
					{
						temp = it->next();
						Assert::IsTrue(result <= temp);
					}
				}
			}
			delete[] graph;

			graphData.close();	
		}
	};
}
