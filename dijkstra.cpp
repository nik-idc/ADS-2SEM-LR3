#include "dijkstra.h"

void findAllPaths(graphNode *graph, size_t vertsCount, bool *visited, list<int> &paths, int &curDist, size_t from, size_t to)
{
	if (from != to)
	{
		bool *visitedCopy = new bool[vertsCount]; // Copy of currently visited nodes for recursion

		for (size_t i = 0; i < vertsCount; i++) // Filling the array
			visitedCopy[i] = visited[i];

		// Iterating through the current node's adjacent vertices
		iterator<pair> *it = graph[from].adjVerts().createIterator(0);
		pair temp;
		while (it->hasNext())
		{
			temp = it->next();
			if (!visitedCopy[temp.name()]) // If current node has not yet been visited, visit it and calculate the path to it
			{
				curDist += temp.num();
				visitedCopy[temp.name()] = true;
				findAllPaths(graph, vertsCount, visitedCopy, paths, curDist, temp.name(), to);
				curDist -= temp.num();
				visitedCopy[temp.name()] = false;
			}
		}

		delete[] visitedCopy;
	}
	else // If reached needed node, push result to the list
		paths.pushBack(curDist);
	
}

graphNode *buildAdjList(std::ifstream &graphData, stack<std::string> &occurList, size_t &vertsCount)
{
	std::string curLine; // Current line in the source file
	list<graphNode> adjList; // Adjancy list in the form of a list

	while (!graphData.eof()) // Loop to read the line and update the list
	{
		std::getline(graphData, curLine);
		if (curLine == "")
			throw std::invalid_argument("Empty string in the file!");
		if (curLine[curLine.size() - 1] == '\r')
			curLine.pop_back();
		std::string first = "", second = "", straight = "", back = "";
		std::string *curEl = &first;
		size_t i = 0, j = 0;

		for (; i < curLine.size(); i++) // Analyze the current line
		{
			if (first == "")
				curEl = &first;
			else if (second == "")
				curEl = &second;
			else if (straight == "")
				curEl = &straight;
			else
				curEl = &back;

			while (curLine[i] != ' ' && i < curLine.size())
			{
				curEl->push_back(curLine[i]);
				i++;
			}
		}

		i = occurList.find(first); // Find index of the first element in the file
		j = occurList.find(second); // Find index of the second element in the file

		if (i == -1) // If element has just occured, push it to the stack
		{
			occurList.push(first);
			i = occurList.size() - 1;
		}
		if (j == -1) // If element has just occured, push it to the stack
		{
			occurList.push(second);
			j = occurList.size() - 1;
		}

		while (occurList.size() > adjList.size()) // Increase the size of the list if needed
		{
			adjList.pushBack(graphNode(list<pair>(), -1));
		}

		if (adjList[i].vertex() == -1) // Add new element to the list
			adjList[i].setVertex(i);

		if (straight != "N/A") // If the edge from first to second exists
			adjList[i].adjVerts().pushBack(pair(j, std::stoi(straight)));

		if (adjList[j].vertex() == -1) // Add new element to the list
			adjList[j].setVertex(j);

		if (back != "N/A") // If the edge from second to first exists
			adjList[j].adjVerts().pushBack(pair(i, std::stoi(back)));
	}

	// Writing all info in the array below
	vertsCount = adjList.size();
	graphNode *graph = new graphNode[vertsCount];

	for (size_t i = 0; i < vertsCount; i++)
	{
		graph[i] = adjList[i];
	}
	return graph;
}

int minDistIndex(int *dist, bool *visited, size_t s)
{
	int min = INT_MAX;
	size_t index = 0;
	for (size_t i = 0; i < s; i++)
	{
		if (dist[i] < min && visited[i] == false)
		{
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(graphNode *graph, size_t vertsCount, size_t from, size_t to, int &result)
{
	int *dist = new int[vertsCount]; // Distances array
	bool *visited = new bool[vertsCount]; // Visited/not visited array

	// Initialising arrays
	for (size_t i = 0; i < vertsCount; i++)
		dist[i] = INT_MAX;
	dist[from] = 0;

	for (size_t i = 0; i < vertsCount; i++)
		visited[i] = false;

	for (size_t i = 0; i < vertsCount - 1; i++) // Main loop
	{
		int cur = minDistIndex(dist, visited, vertsCount), curD = dist[cur];
		visited[cur] = true;
		iterator<pair> *it = graph[cur].adjVerts().createIterator(0);
		pair temp;
		while (it->hasNext())
		{
			temp = it->next();
			if (visited[temp.name()] == false && dist[cur] != INT_MAX && curD + temp.num() < dist[temp.name()])
			{
				dist[temp.name()] = curD + temp.num();
			}
		}
	}

	result = dist[to];

	delete[] dist;
	delete[] visited;
}