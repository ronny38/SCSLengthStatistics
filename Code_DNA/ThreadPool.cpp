#include <iostream>
#include <string>

#include "ThreadPool.h"
#include "Strand.h"

using namespace std;

static void doJob(uint64_t start, uint64_t end, unsigned int solutionArray[N + 1][N + 1], vector<uint64_t>* hist);
static void doRandomizedJob(unsigned int solutionArray[N + 1][N + 1], vector<uint64_t>* hist);

/*
* ThreadFunc:
* The function that is set for each thread in the threadpool.
* The thread takes jobs from the queue, calculates the results and adds them to its histogram, until the queue empties.
*
* @param t - a pointer to the Threadpool object (which contains the jobs queue and additional parameters).
* @param threadNum - the index of the thread out of NUM_OF_THREADS.
* @param hist - a pointer to the histogram that this specific thread should add its results to.
*/
void ThreadFunc(ThreadPool* t, int threadNum, vector<uint64_t>* hist)
{
	// Initialize the histogram to (N+1) cells that contain 0.
	hist->resize(N + 1, 0);

	t->m_mutex.lock();
	while (!t->m_jobs.empty())
	{
		// Take the next job in the queue.
		// A job is a tuple object that contains the starting value and the ending value of the subtask.
		auto& job = t->m_jobs.front();
		t->m_jobs.pop();
		t->m_mutex.unlock();

		auto start = chrono::high_resolution_clock::now();

		if (!t->Randomize())
		{
			doJob(get<0>(job)/*Starting value*/, get<1>(job)/*Ending value*/, t->m_solutionArrays[threadNum], hist);
		}
		else
		{
			doRandomizedJob(t->m_solutionArrays[threadNum], hist);
		}

		// Present the progress out of all jobs.
		t->m_mutex.lock();
		cout << "Finished " << to_string(++t->m_jobsCounter) << " jobs";
		cout << " out of " << to_string(t->m_numOfJobs) << endl;
		auto stop = chrono::high_resolution_clock::now();
		cout << "last job took " << chrono::duration_cast<chrono::minutes>(stop - start).count() << " minutes" << endl << endl;
	}
	t->m_mutex.unlock();
}

ThreadPool::ThreadPool(unsigned int numOfThreads, unsigned int numOfJobs, bool randomize) :
	m_hists(numOfThreads),
	m_numOfThreads(numOfThreads),
	m_jobsCounter(0),
	m_numOfJobs(numOfJobs),
	m_solutionArrays(numOfThreads),
	m_randomize(randomize)
{
	// Initialize all threads' matrices
	for (auto i = 0; i < m_numOfThreads; ++i)
	{
		for (auto j = 0; j <= N; ++j) {
			m_solutionArrays[i][j][0] = j;
			m_solutionArrays[i][0][j] = j;
		}
	}

	// Divide the task into smaller subtasks.
	// For each job in the queue, calculate the starting strand and the ending strand (which are represented by integer values).
	uint64_t offset;
	if (numOfJobs >= Strand::FirstStrandMaxValue())
	{
		offset = 1;
	}
	else
	{
		offset = Strand::FirstStrandMaxValue() / m_numOfJobs;
	}

	uint64_t base = 0;
	while (base + offset < Strand::FirstStrandMaxValue())
	{
		m_jobs.push(make_tuple(base, base + offset));
		base += offset;
	}
	m_jobs.push(make_tuple(base, Strand::FirstStrandMaxValue()));

	// Add the threads to the thread pool.
	for (auto i = 0; i < m_numOfThreads; ++i)
	{
		m_workers.push_back(thread(ThreadFunc, this, i, &m_hists[i]));
	}
}

ThreadPool::~ThreadPool()
{
	Join();
}

shared_ptr<vector<uint64_t>> ThreadPool::Join()
{
	for (auto& t : m_workers)
	{
		t.join();
	}

	// Summarize the results from all the threads into one main histogram.
	vector<uint64_t> hist(N + 1, 0);

	for (auto i = 0; i <= N; ++i)
	{
		uint64_t sum = 0;
		for (auto j = 0; j < m_numOfThreads; ++j)
		{
			sum += m_hists[j][i];
		}
		hist[i] = sum;
	}
	m_workers.clear();

	return make_shared<vector<uint64_t>>(hist);
}

/*
* doJob:
* The main function that is called by the threads to calculate SCS results in a given range, when RANDOMIZED is set to false.
*
* @param start, @param end - the starting\ending values to calculate the SCS problem for every pair of strands within this range.
* @param solutionArray - a pointer to the inner matrix that is used to solve the SCS problem. The matrix is reused for time-optimization purposes.
* @param hist - a pointer to the histogram that this specific thread should add its results to.
*
* This function has been optimized to save running time. For more details please kindly check the documentation of SCS<N>::PairsToAdd.
*/
void doJob(uint64_t start, uint64_t end, unsigned int solutionArray[N + 1][N + 1], vector<uint64_t>* hist)
{
	for (auto s1 = start; s1 < end; ++s1)
	{
		Strand prevS2;
		for (auto s2 = s1; s2 < Strand::MaxValue(); ++s2)
		{
			auto res = SCS::PairsToAdd(s1, s2);
			// If res == 0 then there's no point at calculating the SCS problem for these two strands,
			// that is because these two current strands have already been taken into our calculations before.
			if (res != 0)
			{
				(*hist)[SCS::Calculate(Strand(s1), Strand(s2), solutionArray, prevS2) - N] += res;
				prevS2 = Strand(s2);
			}
		}
	}
}


/*
* doRandomizedJob:
* The main function that is called by the threads to calculate SCS results for randomly generated strands, when RANDOMIZED is set to true.
*
* @param solutionArray - a pointer to the inner matrix that is used to solve the SCS problem. The matrix is reused for time-optimization purposes.
* @param hist - a pointer to the histogram that this specific thread should add its results to.
*/
void doRandomizedJob(unsigned int solutionArray[N + 1][N + 1], vector<uint64_t>* hist)
{
	for (auto i = 0; i < NUM_OF_RANDOMS_PER_JOB; ++i)
	{
		auto s1 = SCS::GenerateStrand();
		auto s2 = SCS::GenerateStrand();
		(*hist)[SCS::Calculate(s1, s2, solutionArray, Strand()) - N]++;
	}
}