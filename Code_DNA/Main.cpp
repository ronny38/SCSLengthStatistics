#include <vector>
#include <thread>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "ThreadPool.h"
#include "SCS.h"
#include "Settings.h"

using namespace std;

int main()
{
	auto start = chrono::high_resolution_clock::now();

	string fileName = OUTPUT_DIRECTORY + string("\\DNA_N=") + to_string(N);
	vector<vector<uint64_t>> hists;
	ThreadPool tp(NUM_OF_THREADS, NUM_OF_JOBS, RANDOMIZE);

	auto hist = tp.Join();

	ofstream file(fileName + ".csv", ofstream::out | ofstream::trunc);
	file << "SCS Length,Count" << endl;
	for (auto i = 0; i <= N; ++i)
	{
		file << to_string(i + N) << "," << to_string((*hist)[i]) << endl;
	}
	file.close();

	auto stop = chrono::high_resolution_clock::now();

	cout << "Finished executing in:" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " milliseconds = ";
	cout << chrono::duration_cast<chrono::seconds>(stop - start).count() << " seconds = ";
	cout << chrono::duration_cast<chrono::minutes>(stop - start).count() << " minutes = ";
	cout << chrono::duration_cast<chrono::hours>(stop - start).count() << " hours" << endl;
}