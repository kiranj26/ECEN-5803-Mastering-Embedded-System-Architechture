/* ========================================================================== */
/*                                                                            */
/*   main.cpp                                                               */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */


#include "mbed.h"
#include "dhry.h"
 
DigitalOut myled(LED1);
Timer timer;
Serial pc(USBTX, USBRX);  //serial channel over HDK USB interface
 
int main() {
    double benchtime, dps;
    unsigned long loops;
    
    pc.baud(9600);
    printf("Dhrystone Benchmark Program C/1 12/01/84\r\n");
    timer.start();
    while(1) {
        loops = 0l;
        myled = 1;
        timer.reset();
        do {
            Proc0();
            loops += LOOPS;
            benchtime = timer.read();
        } while (benchtime <= 60.000);
        myled = 0;
        dps = (double)loops / benchtime;
        printf("Dhrystone time for %ld passes = %.3f sek\r\n", loops, benchtime);
        printf("This machine benchmarks at %.0f dhrystones/second\r\n", dps);
        
        wait(1.0);
    }
}