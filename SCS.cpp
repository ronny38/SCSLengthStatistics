#include "SCS.h"
#include <algorithm>

using namespace std;

SCS::SCS(int n) : size(n)
{
	solutionArray.resize(size);
	edgesArray.resize(size);
	for (auto i = 0; i < size; ++i)
	{
		solutionArray[i].resize(size, 0);
		edgesArray[i].resize(size, NO_EDGE);
	}
}

/**
 * Calculates the Shortest Common Supersequence's Length.
 *
 * @param strand1, strand2 - The DNA strands.
 * @return the length of the shortest common supersequence.
 */
int SCS::Calculate(const vector<Base>& strand1, const vector<Base>& strand2)
{
	Init(strand1, strand2);

	// Base case
	for (auto i = 0; i < size; ++i)
	{
		if (edgesArray[0][i] != NO_EDGE)
			solutionArray[0][i] = 1;
		else
			solutionArray[0][i] = 0;
	}

	for (auto i = 1; i < size; ++i)
	{
		for (auto j = 0; j < size; ++j)
		{
			auto lastEdgeIndex = edgesArray[i][j];
			auto maxBeforeThisIndex = solutionArray[i - 1][j];
			if (lastEdgeIndex == NO_EDGE)
			{
				solutionArray[i][j] = maxBeforeThisIndex;
			}
			else
			{
				auto maxlastEdgeIndex = (lastEdgeIndex == 0 ? 0 : solutionArray[i - 1][lastEdgeIndex - 1]);
				solutionArray[i][j] = max(maxBeforeThisIndex, 1 + maxlastEdgeIndex);
			}
		}
	}

	return (2*size - solutionArray[size - 1][size - 1]);
}



/**
 * Initializes an inner data structure.
 * 
 * This is a 2D array, where entry [i][j] holds the index of the highest k
 * such that k isn't larger than j, and there is an edge between entry i in strand1 and entry k in strand2.
 * If there's no such edge, it holds -1.
 * 
 * We define an edge between entry i and entry j in two strands, if both cells contain the same DNA base.
 *
 * @param strand1, strand2 - The DNA strands.
 */
void SCS::Init(const vector<Base>& strand1, const vector<Base>& strand2)
{
	for (auto i = 0; i < size; ++i)
	{
		edgesArray[i].assign(size, NO_EDGE);
		for (auto j = 0; j < size; ++j)
		{
			if (j == 0)
			{
				if (strand1[i] == strand2[j])
					edgesArray[i][j] = j;
			}
			else
			{
				edgesArray[i][j] = (strand1[i] == strand2[j] ? j : edgesArray[i][j - 1]);
			}
		}
	}
}
