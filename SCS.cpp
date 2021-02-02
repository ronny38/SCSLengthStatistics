#include "SCS.h"
#include <algorithm>

using namespace std;

SCS::SCS(int n) : size(n)
{
	solutionArray.resize(size+1);
	for (auto i = 0; i <= size; ++i)
	{
		solutionArray[i].resize(size+1, 0);
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

    for (int i = 0; i <= size; i++){
        solutionArray[i][0] = i;
        solutionArray[0][i] = i;
    }

    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (strand1[i - 1] == strand2[j - 1])
                solutionArray[i][j] = solutionArray[i - 1][j - 1] + 1;
            else
                solutionArray[i][j] = min(solutionArray[i - 1][j] + 1,
                                          solutionArray[i][j - 1] + 1);
        }
    }

    return solutionArray[size][size];
}
