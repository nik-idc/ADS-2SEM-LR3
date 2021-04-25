#pragma once

#ifndef ADJVERTS_H
#define ADJVERTS_H

#include "pair.h"

class graphNode
{
public:

	graphNode()
	{
		adjVertsV = list<pair>();
		vertexV = 0;
	}

	graphNode(list<pair> newVerts, int newV)
	{
		adjVertsV = newVerts;
		vertexV = newV;
	}

	graphNode(const graphNode &toCopy)
	{
		adjVertsV = toCopy.adjVertsV;
		vertexV = toCopy.vertexV;
	}

	list<pair>& adjVerts()
	{
		return adjVertsV;
	}

	int vertex()
	{
		return vertexV;
	}

	void setVertex(int newV)
	{
		vertexV = newV;
	}

	graphNode &operator=(const graphNode &right)
	{
		adjVertsV = right.adjVertsV;
		vertexV = right.vertexV;
		return *this;
	}

	bool isAdjTo(int name)
	{
		if (!adjVertsV.isEmpty())
		{
			iterator<pair> *it = adjVertsV.createIterator(0);
			pair temp;
			while (it->hasNext())
			{
				temp = it->next();
				if (temp.name() == name)
					return true;
			}
			return false;
		}
		else
			return false;
	}

private:
	list<pair> adjVertsV;
	int vertexV;
};

#endif