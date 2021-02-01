#pragma once
#include <vector>
#include "SCS/Common.h"


/**
 * Implementation of a solution for the Shortest Common Supersequence's Length problem.
 *
 * Given two strands, this class finds the length of their shortest common supersequence.
 * It uses dynamic programming in order to provide a solution withing a time complexity of O(n^2).
 */
class SCS
{
public:
	explicit SCS(int n);
	~SCS() = default;
	int Calculate(const std::vector<Base>& strand1, const std::vector<Base>& strand2);

private:
	void Init(const std::vector<Base>& strand1, const std::vector<Base>& strand2);

	std::vector<std::vector<int>> solutionArray;
	std::vector<std::vector<int>> edgesArray;
	int size;
};