#include "dijkstra.h"

int main()
{
	try
	{
		std::ifstream graphData; // For reading the graph

		graphData.open("graph.txt", std::ios_base::in | std::ios_base::binary);

		size_t vertsCount = 0, from, to;
		int result = 0;

		stack<std::string> occurList;
		graphNode *graph = buildAdjList(graphData, occurList, vertsCount); // Building the adjacency array

		// Entering 'from' and 'to' indeces
		std::cout << "Please enter the indexes of 'from' and 'to' vertices (vertices are sorted in order of occurence):\n";

		std::cout << "From:\n";
		std::cin >> from;
		if (from < 0 || from >= vertsCount)
			throw std::invalid_argument("Incorrect 'from' index!");

		std::cout << "To:\n";
		std::cin >> to;
		if (to < 0 || to >= vertsCount)
			throw std::invalid_argument("Incorrect 'to' index!");

		// If no edges are coming out of the 'from' vertex then there is no point in going further
		if (graph[from].adjVerts().isEmpty())
			std::cout << "'From' vertex does not have edges coming out of it\n";
		else
		{
			dijkstra(graph, vertsCount, from, to, result);

			// Display result
			if (result != INT_MAX)
				std::cout << "Shortest distance from " << occurList[from] << " to " << occurList[to] << " is " << result << " \n";
			else
				std::cout << "No path from " << occurList[from] << " to " << occurList[to] << "\n";
		}

		delete[] graph;

		graphData.close();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}