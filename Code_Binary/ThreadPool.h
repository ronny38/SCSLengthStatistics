#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex>
#include <queue>
#include <thread>
#include <tuple>
#include <vector>
#include <memory>
#include <chrono>

#include "SCS.h"
#include "Settings.h"


class ThreadPool
{
public:
	ThreadPool(unsigned int numOfThreads, unsigned int numOfJobsPower, bool randomize);
	~ThreadPool();
	inline bool Randomize() const
	{
		return m_randomize;
	}

	std::shared_ptr<std::vector<uint64_t>> Join();

	friend void ThreadFunc(ThreadPool* t, int threadNum, std::vector<uint64_t>* hist);

private:
	std::vector<std::thread> m_workers;
	std::vector<std::vector<uint64_t>> m_hists;
	const unsigned int m_numOfThreads;
	const bool m_randomize;
	std::mutex m_mutex;
	std::queue<std::tuple<uint64_t, uint64_t>> m_jobs;
	unsigned int m_jobsCounter;
	unsigned int m_numOfJobs;
	std::vector<unsigned int[N + 1][N + 1]> m_solutionArrays;
};


#endif // !THREADPOOL_H