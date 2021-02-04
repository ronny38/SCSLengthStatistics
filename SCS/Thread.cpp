#include <vector>
#include "../SCS.h"
#include <thread>
#include <string>
#include <fstream>

#include <iostream>

using namespace std;

void Func(int n, vector<uint64_t>* hist, Base firstBase, bool isAC)
{
	SCS scs(n);
	vector<Base> s1, s2;
	s1.resize(n, A);
	s1[1] = firstBase;
	s1[2] = (isAC ? A : G);
	hist->resize(n + 1, 0);

	do
	{
		s2 = s1;
		do
		{
			(*hist)[scs.Calculate(s1, s2) - n]++;
		} while (IncrementS2(s2));
	} while (IncrementS1(s1, isAC));

}

int main()
{
	int n = 8;
	vector<thread> workers;
	bool isAC = true;
	Base secondBase = A;
	string fileName = "C:\\Users\\oref1\\Technion\\Sem5\\SCS\\temp\\tempN=" + to_string(n);
	int fileNumber = 0;
	vector<vector<uint64_t>> hists;
	hists.resize(8);

	for (auto i = 0; i < 4; ++i)
	{
		for (auto j = 0; j < 2; ++j)
		{
			workers.push_back(thread(Func, n, &(hists[fileNumber]), secondBase, isAC));
			isAC = !isAC;
			fileNumber++;
		}
		IncrementIndex(secondBase);
	}

	for (auto& t : workers)
	{
		t.join();
	}


	ofstream file(fileName + ".csv", ofstream::app | ofstream::out);
	file << "SCS Length,Count" << endl;

	for (auto i = 0; i <= n; ++i)
	{
		uint64_t sum = 0;
		for (auto j = 0; j < 8; ++j)
		{
			sum += hists[j][i];
		}
		file << to_string(i + n) << "," << to_string(sum) << endl;
	}
	file.close();

}
