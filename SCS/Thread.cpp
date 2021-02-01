#include <vector>
#include "../SCS.h"
#include <thread>
#include <string>
#include <fstream>

#include <iostream>

using namespace std;

char getBase(int num)
{
	if (num == 0) return 'A';
	if (num == 1) return 'C';
	if (num == 2) return 'G';
	return 'T';
}

string getStrand(const vector<Base>& vec)
{
	string res;
	for (auto& b : vec) res += getBase(b);
	return res;
}

void Func(int n, Base firstBase, bool isAC, const string& fileName)
{
	SCS scs(n);
	vector<Base> s1, s2;
	s1.resize(n, A);
	s1[1] = firstBase;
	s1[2] = (isAC ? A : G);

	ofstream file(fileName + ".csv", ofstream::app | ofstream::out);
	file << "n,SCS Length" << endl;
	do
	{
		s2 = s1;
		do
		{
			file << n << "," << scs.Calculate(s1, s2) << endl;
		} while (IncrementS2(s2));
	} while (IncrementS1(s1, isAC));

	file.close();
}


int main()
{
	vector<thread> workers;
	bool isAC = true;
	Base secondBase = A;
	string fileName = "C:\\Hi\\temp";
	int fileNumber = 0;

	for (auto i = 0; i < 4; ++i)
	{
		for (auto j = 0; j < 2; ++j)
		{
			workers.push_back(thread(Func, 4, secondBase, isAC, fileName + to_string(fileNumber)));
			isAC = !isAC;
			fileNumber++;
		}
		IncrementIndex(secondBase);
	}

	for (auto& t : workers)
	{
		t.join();
	}
}
