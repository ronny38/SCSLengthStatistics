#pragma once
#include <vector>

enum Base {A, C, G, T};
const int NO_EDGE = -1;


static bool IncrementIndex(std::vector<Base>& vec, int index)
{
	if (index < 0)
	{
		return false;
	}

	if (vec[index] != T)
	{
		switch (vec[index])
		{
		case A:
			vec[index] = C;
			break;
		case C:
			vec[index] = G;
			break;
		default:
			vec[index] = T;
			break;
		}
		return true;
	}
	else
	{
		vec[index] = A;
		return IncrementIndex(vec, index - 1);
	}
}

bool Increment(std::vector<Base>& vec)
{
	return IncrementIndex(vec, vec.size() - 1);
}
