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
    double benchtime, dps, DMIPS;
    unsigned long loops;
    
    pc.baud(9600);
    printf("\n\rDhrystone Benchmark Program C/1 12/01/84\r\n");
    timer.start();
    while(1) {
        loops = 0l;
        myled = 1;
        timer.reset();
        do {
            Proc0();
            loops += LOOPS;
            benchtime = timer.read();
        } while (benchtime <= 20.000);
        myled = 0;
        dps = (double)loops / benchtime;
        printf("Dhrystone time for %ld passes = %.3f sek\r\n", loops, benchtime);
        printf("This machine benchmarks at %.0f dhrystones/second\r\n", dps);
        DMIPS = dps/1757.0;
        pc.printf("This machine has %f DMIPS\r\n", DMIPS);
        pc.printf("This machine has %f DMIPS/Mhz\r\n", DMIPS/18.5);
        
        wait(1.0);
    }
}