#include "../SCS.h"
#include "Common.h"
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
	SCS s(4);

	vector<Base> s1 = { A, C, G, T };
	vector<Base> s2 = { A, C, G, T };

	assert(s.Calculate(s1, s2) == 4);

	s1 = { A, C, T, G };
	assert(s.Calculate(s1, s2) == 5);

	s1 = { A, T, C, G };
	assert(s.Calculate(s1, s2) == 5);

	s1 = { A, T, G, C };
	assert(s.Calculate(s1, s2) == 6);

	s1 = { A, A, A, A };
	assert(s.Calculate(s1, s2) == 7);

	s2 = { T, T, G, C };
	assert(s.Calculate(s1, s2) == 8);
}
