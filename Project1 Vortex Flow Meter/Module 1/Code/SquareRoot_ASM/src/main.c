/**
 * @file main.c
 * @brief Square Root Approximation using Integer Approach - Project 1 Module 1
 *
 * @author Viraj Patel, Kiran jojare
 * @see <a href="https://developer.arm.com/documentation/ddi0439/b/Programmers-Model/Instruction-set-summary/Cortex-M4-instructions?lang=en">ARM Cortex-M4 Instructions</a>
 * @see PDF obtained from professor "Approximate Square Root Bisection Method"
 */

// include standard header files
#include <string.h>
#include <assert.h> 

/**
 * @brief Compute the integer square root of a number using approximate bisection method.
 * @param
 *     int x - The input integer to take the square root.
 * @return The integer square root of the given number.
 */
__asm int my_sqrt_int(int x)
{
    PUSH {R4-R8, LR}       ; Save registers that will be used in the subroutine
    MOV R4, #0             ; Initialize a = 0
    LDR R5, =0x4000        ; Initialize b = 2^16
    MOV R6, #-1            ; Initialize c = -1
		MOV R8, #0             ; Initialize done = 0
loop_start
    MOV R7, R6             ; c_old <- c
    ADD R6, R4, R5         ; R6 = a + b
    ASR R6, R6, #1         ; c <- (a+b)/2
    MUL R3, R6, R6         ; R3 = c*c
    CMP R3, R0             ; Compare c*c with x
    BEQ done               ; If c*c == x, branch to done
    BLT update_a           ; If c*c < x, branch to update_a
    B update_b             ; Otherwise, branch to update_b

update_a
    MOV R4, R6             ; a <- c
    B loop_check					 ; jump to loop_check

update_b
    MOV R5, R6             ; b <- c
    B loop_check           ; jump to loop_check

loop_check
    CMP R6, R7             ; Compare c with c_old
    BEQ done               ; If c == c_old, branch to done
		CMP R8, #1             ; Compare done with 1
		BEQ done               ; If done == 1, branch to done
    B loop_start           ; Otherwise, loop back to start

done
    MOV R0, R6             ; Move result into R0 (return value)
    POP {R4-R8, LR}        ; Restore saved registers
    BX LR                  ; Return
}

/**
 * @brief Compute the square root of a number using approximate bisection method in Q16.16 number format
 * @param
 *     int x - The input integer to take the square root in Q16.16 number format.
 * @return The square root of the given number in Q16.16 format
 */
__asm int my_sqrt_fixed_point(int x)
{
    PUSH {r4-r7,lr}       ; Push r4-r7 and link register to stack

    CMP r0,#0x00          ; Compare num with 0
    BEQ done1             ; If num == 0, branch to end
    CMP r0,#0x10000       ; Compare num with 0x00010000
    BEQ done1             ; If num == 0x00010000, branch to end

    MOVS r3,#0x00         ; Initialize start to 0
    MOV r2,r0             ; Initialize end to num
    MOV r4,r0             ; Initialize ans to num
    MOVS r5,#0x00         ; Clear r5 register to use it later
    
loop
    B end                 ; Branch to end if start > end
loop1
    ADDS r1,r3,r2         ; mid = (start + end)
    LSRS r1,r1,#1         ; mid /= 2

    UMULL r7,r6,r1,r1     ; r6:r7 = mid * mid
    SUBS r7,r0,r7         ; Subtract result from num
    SBCS r6,r5,r6         ; Subtract with carry the result from 0
    BCC cond_less_equal   ; If unsigned lower or same, branch to cond_less_equal

    ADDS r3,r1,#1         ; start = mid + 1
    MOV r4,r1             ; ans = mid
    B loop

cond_less_equal
    SUBS r2,r1,#1         ; end = mid - 1
    
end
    CMP r3,r2             ; Compare start with end
    BLS loop1             ; If start <= end, branch to loop1
    
    LSLS r0,r4,#8         ; Return ans << 8
done1
    POP {r4-r7,pc}        ; Pop r4-r7 from stack and return
		BX LR                 ; Return
}

/**
 * @brief Application Entry Point.
 * @param void
 * @return nothing
 */
int main(void)
{
	volatile int r, j = 0;

	// Assert that my_sqrt_int returns the correct value for each test input
	r = my_sqrt_int(0);
	assert(r == 0); // assert that the square root of 0 is 0

	r = my_sqrt_int(25);
	assert(r == 5); // assert that the square root of 25 is 5

	r = my_sqrt_int(133);
	assert(r == 11); // assert that the square root of 133 is 11

	// Testing requested from lab exercise question
	// 3. Test your code with these inputs: 2, 4, 22, and 121. Record the results
	
	r = my_sqrt_int(2);
	assert(r == 1); // assert that the square root of 2 is 1 
	
	r = my_sqrt_int(4);
	assert(r == 2); // assert that the square root of 4 is 2
	
	r = my_sqrt_int(22);
	assert(r == 4); // assert that the square root of 22 is 4
	
	r = my_sqrt_int(121);
	assert(r == 11); // assert that the square root of 121 is 11
	
	// Iterate from 0 to 9999 and compute square root of 'i' using 'my_sqrt_int', then accumulate the results in 'j'.
	for (int i = 0; i < 10000; i++) { 
			r = my_sqrt_int(i); 
			j += r; 
	}
	// Assert that the accumulated result 'j' is 661650
	assert(j == 661650);
	
	// Testing requested from bonus lab exercise question
	// 1. Test your code with these inputs: 2.0, 4.0, 22.0, and 121.0. Record the results
	r = my_sqrt_fixed_point(0x00020000);    // 2.0 in Q16.16 format
	assert(r == 0x00016a00);    // assert that square root of 2.0 is 1.41 in Q16.16 format
	
	r = my_sqrt_fixed_point(0x00040000);    // 4.0 in Q16.16 format
	assert(r == 0x00020000);    // assert that square root of 4.0 is 2.0 in Q16.16 format
	
	r = my_sqrt_fixed_point(0x00160000);    // 22.0 in Q16.16 format
	assert(r == 0x0004b000);    // assert that square root of 22.0 is 4.68 in Q16.16 format
	
	r = my_sqrt_fixed_point(0x00790000);    // 121.0 in Q16.16 format
	assert(r == 0x000b0000);    // assert that square root of 121.0 is 11.0 in Q16.16 format
	
	// Code execution ends here
	while(1);
}
