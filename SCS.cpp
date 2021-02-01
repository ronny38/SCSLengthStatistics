#include "SCS.h"

SCS::SCS(int n) : size(n)
{
	solutionArray.resize(size);
	edgesArray.resize(size);
	for (auto i = 0; i < size; ++i)
	{
		solutionArray[i].resize(size, 0);
		edgesArray[i].resize(size, -1);
	}
}

int SCS::Calculate(const std::vector<Base>& strand1, const std::vector<Base>& strand2)
{
	

}


/**
 * Initializes an inner data structure.
 * 
 * This is a 2D array, where cell [i][j] holds the index of the highest k
 * such that k isn't larger than j, and there is an edge between cell i in strand1 and cell k in strand2.
 * If there's no such edge, it holds -1.
 * 
 * We define an edge between cell i and cell j in two strands, if both cells contain the same DNA base.
 *
 * @param strand1, strand2 - The DNA strands.
 */
void SCS::Init(const std::vector<Base>& strand1, const std::vector<Base>& strand2)
{
	for (auto i = 0; i < size; ++i)
	{
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
