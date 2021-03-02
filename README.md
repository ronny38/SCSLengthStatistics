# Shortest Common Supersequence Length Analyzer
Analyzing statistics on the SCS length of pairs of arbitrary sequences: The minimum, maximum, average, the variance, and the distribution.

## What's In the Box
This repository provides code that allows you to simulate, analyze, measure and graphically present the distribution of the SCS length of binary vectors of various lengths.

The code that is written in CPP, under "SCS" directory, is highly optimized, such that the running time is reduced significantly, in comparison to the naive solution.
The code that is written in R provides tools to analyze and present the results from the simulation.

## Getting Started

The first step is to configure all required parameters in "SCS/Settings.h", as follows:

### Output Directory
```
#define OUTPUT_DIRECTORY "<Your Path Here>"
```

### The Length of the Strands

Each compilation of the code yields analysis of strands with a constant length.
```
#define N <Your Length Here>
```

### The Size of the Threadpool's Queue
This parameter sets the number of subtasks that the main analysis will be divided into.
Set optimized values to achieve shorter running time.

The number of jobs must be a power of 2, so an exponent should be entered at this field.
```
#define POWER_NUM_OF_JOBS <Log_2(Your Number of Jobs Here)>
```

### The Number of Threads

The number of threads that will work in the threadpool.
Set optimized values to achieve shorter running time.
```
#define NUM_OF_THREADS <Your Number of Threads Here>
```

### Analysis Mode
The analysis can run in two modes:
* **Randomized**: The code will randomly generate a large number of pairs, and the statistics will be as accurate as the number of pairs generated. Choose "true" to run in this mode.
* **Normal**: The code will go over each pair of strands of length N, and the statistics will be 100% accurate. Additional optimizations will be applied in this mode to reduce running time. Choose "false" to run in this mode.
```
#define RANDOMIZE <true or false>
```

### The Number of Pairs to Generate in Randomized Mode
**Important**: This parameter has any effect only when RANDOMIZE is set to true.

This parameter sets the number of pairs to generate at each job (subtask) in the queue.

Hence, when RANDOMIZE is true, POWER_NUM_OF_JOBS is 'J' and NUM_OF_RANDOMS_PER_JOB is 'R', the total amount of pairs the code will generate is 'J'x'R' (J times R).
```
#define NUM_OF_RANDOMS_PER_JOB <Your Choice Here>
```

## Analyzing the Code

There are two coding files: "SCS_statistics_binary.R" and "SCS_statistics_quaternary.R", the instructions are relevant for both. 
The first step is to configure the directory as follows:

### Git Directory
**Important**: Change backslashes to regular slashes.
```
git_dir = "<Your Path Here>"
```

After configuring the directory, it is time to run the code and start analyzing.

### Mean plot
To represent the mean values as a function of the strand's length, run the following command:
```
Mean_Plot()
```

### Variance plot
To represent the variance values as a function of the strand's length, run the following command:
```
Var_Plot()
```

### Distribution plot
Showing the data for specified strand length as a distribution histogram.
```
dist_for_n(<Strand Length>)
```

It is also possible to show the normal distribution function, that matches the SCS mean 
and variance of the specified strand length, by adding "TRUE".
For example:
```
dist_for_n(<Strand Length>, TRUE)
```

## Authors

* **Or Efrat** - or.efrat@campus.technion.ac.il
* **Ronny Barkan** - ronny.barkan@campus.technion.ac.il