
#include <iostream>
#include <chrono>
#include "dhry.h"

int main() {
    using namespace std::chrono;

    high_resolution_clock::time_point start_time, end_time;
    double benchtime, dps, DMIPS;
    unsigned long loops;

    std::cout << "Dhrystone Benchmark Program C/1 12/01/84" << std::endl;

    // Run the benchmark once
    loops = 0l;
    start_time = high_resolution_clock::now();

   do {
        Proc0();
        loops += LOOPS;
        end_time = high_resolution_clock::now();
        benchtime = duration_cast<duration<double>>(end_time - start_time).count();
        std::cout << "Benchtime: " << benchtime << std::endl;
   } while (benchtime <= 20.000);

    // Calculate and print benchmark results
    dps = static_cast<double>(loops) / benchtime;
    std::cout << "Dhrystone time for " << loops << " passes = " << benchtime << " seconds" << std::endl;
    std::cout << "This machine benchmarks at " << dps << " dhrystones/second" << std::endl;

    DMIPS = dps/1757.0;
    std::cout << "This machine has " << DMIPS << " DMIPS" << std::endl;
    std::cout << "This machine has " << DMIPS/18.5 << "DMIPS/Mhz" << std::endl;

    return 0;
}


