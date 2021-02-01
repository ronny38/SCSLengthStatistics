#pragma once
#include <vector>
#include "SCS/Common.h"

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