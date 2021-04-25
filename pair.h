#pragma once
#include "stuff.h"

#ifndef PAIR_H
#define PAIR_H

class pair
{
public:

	pair()
	{
		nameV = 0;
		numV = 0;
	}

	pair(int name, int number)
	{
		nameV = name;
		numV = number;
	}

	pair(const pair &toCopy)
	{
		nameV = toCopy.nameV;
		numV = toCopy.numV;
	}

	int name()
	{
		return nameV;
	}

	int num()
	{
		return numV;
	}

	pair &operator=(const pair &right)
	{
		nameV = right.nameV;
		numV = right.numV;
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const pair &out)
	{
		os << out.nameV << " " << out.numV << " ";
		return os;
	}

private:
	int nameV;
	int numV;
};

#endif
