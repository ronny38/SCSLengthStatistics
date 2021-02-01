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


/*
  
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
