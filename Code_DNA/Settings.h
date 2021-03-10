#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

/*
* The directory to which output the results.
*/
#define OUTPUT_DIRECTORY "C:\\Hi"


/*
* The length of the strands.
*/
#define N 10


/*
* The number of jobs that the threadpool's jobs queue will hold.
* The more jobs there are, the more the task is divided into smaller subtasks.
*/
#define NUM_OF_JOBS (1 << 2)


/*
* The number of threads that will work in the threadpool.
*/
#define NUM_OF_THREADS 8


/*
* false = The code will go over each pair of strands of length N, and the statistics will be 100% accurate.
* true = The code will generate a big number of pairs randomly, and the statistics will be as accurate as the number of pairs generated.
*/
#define RANDOMIZE true


/*
* This parameter has any effect only when RANDOMIZE is set to true.
* This parameter sets the number of pairs to generate for each job (subtask) in the queue.
* Hence, when RANDOMIZE is true, POWER_NUM_OF_JOBS is 'J' and NUM_OF_RANDOMS_PER_JOB is 'R', the total amount of pairs the code will generate is 'J'x'R' (J times R).
*/
#define NUM_OF_RANDOMS_PER_JOB (1 << 20)


#endif // !SETTINGS_H