#define _GNU_SOURCE 

#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <pthread.h>
#include "dhry.h"

int main() {
    clock_t start_time, end_time;
    double benchtime, dps, DMIPS;
    unsigned long loops;

    printf("Dhrystone Benchmark Program C/1 12/01/84\n");
    
    // Change Core From 0-3
    int core = 0;
    // Set affinity to core N
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    printf("Running On Core: %d\n", sched_getcpu());

    // Run the benchmark once
    loops = 0l;
    start_time = clock();

    do {
        Proc0();
        loops += LOOPS;
        end_time = clock();
        benchtime = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        //printf("Benchtime: %lf\n", benchtime);
    } while (benchtime <= 20.000);

    // Calculate and print benchmark results
    dps = (double)loops / benchtime;
    printf("Dhrystone time for %lu passes = %lf seconds\n", loops, benchtime);
    printf("This machine benchmarks at %lf dhrystones/second\n", dps);

    DMIPS = dps / 1757.0;
    printf("This machine has %lf DMIPS\n", DMIPS);
    printf("This machine has %lf DMIPS/MHz\n", DMIPS / 18.5);

    return 0;
}
