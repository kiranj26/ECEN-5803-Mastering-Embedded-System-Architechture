/*----------------------------------------------------------------------------
 * Name:    Time.c
 * Purpose: Time Functions for 100Hz Clock Tick
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                     /* STM32F10x definitions           */

long timeval = 0;


/*----------------------------------------------------------------------------
  TIM1 Update Interrupt executes each 10ms @ 72 MHz CPU Clock
 *----------------------------------------------------------------------------*/
void TIM1_UP_IRQHandler (void) {

  if (TIM1->SR & (TIM_SR_UIF)) {                  /* UIF set?                 */

    timeval++;

    TIM1->SR &= ~(TIM_SR_UIF);                    /* clear UIF flag           */
  }
}


/*----------------------------------------------------------------------------
  Setup the TIM1 Interrupt
 *----------------------------------------------------------------------------*/
void TIM_Init (void)  {

  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;             /* enable clock for TIM1    */

  TIM1->PSC   = ( 7200 - 1);                      /* set prescaler   = 10KHz  */
  TIM1->ARR   = (  100 - 1);                      /* set auto-reload = 10 ms  */
  TIM1->RCR   =  0;;                              /* set repetition counter   */

  TIM1->DIER = TIM_DIER_UIE;                      /* Update Interrupt enable  */
  NVIC_EnableIRQ(TIM1_UP_IRQn);                   /* TIM1   Interrupt enable  */

  TIM1->CR1  |= TIM_CR1_CEN;                      /* timer enable             */
}
