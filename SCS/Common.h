#ifndef COMMON_H
#define COMMON_H
#include <vector>

enum Base {A, C, G, T};
const int NO_EDGE = -1;

static void IncrementIndex(Base& val)
{
	switch (val)
	{
	case A:
		val = C;
		break;
	case C:
		val = G;
		break;
	default:
		val = T;
		break;
	}
}

static bool IncrementInnerS1(std::vector<Base>& vec, int index, bool isAC)
{
	if (index <= 2 && (isAC && vec[index] == C || !isAC && vec[index] == T))
	{
		return false;
	}

	if (vec[index] != T)
	{
		IncrementIndex(vec[index]);
		return true;
	}
	else
	{
		vec[index] = A;
		return IncrementInnerS1(vec, index - 1, isAC);
	}
}

static bool IncrementS1(std::vector<Base>& vec, bool isAC)
{
	return IncrementInnerS1(vec, vec.size() - 1, isAC);
}




static bool IncrementInnerS2(std::vector<Base>& vec, int index)
{
	if (index < 0)
	{
		return false;
	}

	if (vec[index] != T)
	{
		IncrementIndex(vec[index]);
		return true;
	}
	else
	{
		vec[index] = A;
		return IncrementInnerS2(vec, index - 1);
	}
}

static bool IncrementS2(std::vector<Base>& vec)
{
	return IncrementInnerS2(vec, vec.size() - 1);
}

#endif