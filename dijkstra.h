#pragma once

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graphNode.h"

// Function to find all paths from the 'from' node to the 'to' node
void findAllPaths(graphNode *graph, size_t vertsCount, bool *visited, list<int> &paths, int &curDist, size_t from, size_t to);

// Function to build an adjacency list
graphNode *buildAdjList(std::ifstream &graphData, stack<std::string> &occurList, size_t &vertsCount);

// Find minimum element in the distances array
int minDistIndex(int *dist, bool *visited, size_t s);

// Function to find the shortest path using the Dijkstra algorithm
void dijkstra(graphNode *graph, size_t vertsCount, size_t from, size_t to, int &result);

#endif