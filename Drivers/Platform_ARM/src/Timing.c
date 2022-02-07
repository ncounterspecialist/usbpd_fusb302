/*******************************************************************************
 * @file     Timing.c
 * @author   USB PD Firmware Team
 *
 * Copyright 2018 ON Semiconductor. All rights reserved.
 *
 * This software and/or documentation is licensed by ON Semiconductor under
 * limited terms and conditions. The terms and conditions pertaining to the
 * software and/or documentation are available at
 * http://www.onsemi.com/site/pdf/ONSEMI_T&C.pdf
 * ("ON Semiconductor Standard Terms and Conditions of Sale, Section 8 Software").
 *
 * DO NOT USE THIS SOFTWARE AND/OR DOCUMENTATION UNLESS YOU HAVE CAREFULLY
 * READ AND YOU AGREE TO THE LIMITED TERMS AND CONDITIONS. BY USING THIS
 * SOFTWARE AND/OR DOCUMENTATION, YOU AGREE TO THE LIMITED TERMS AND CONDITIONS.
 ******************************************************************************/
#include "Timing.h"
#include "stm32f1xx_hal.h"

#include "../../FUSB_CORE/core.h"

void InitializeTickTimer(void)
{
    /* Disable */
    TIM2->CR1 = 0x00000000;

    /*SystemCoreClock is 48MHz. Prescaler - 48 gives 1us resolution */
    TIM2->PSC = 48;

    /*
     * Start the count at the end.  Certain registers (PSC,ARR,...) are
     * "shadowed" and only get updated on a rollover or other event.
     */
    TIM2->CNT = 0xFFFFFFFF;

    /*
     * Period/Reload - a long period give a free-running time-stamp-mode timer
     */
    TIM2->ARR = 0xFFFFFFFF;

    /* Enable! */
    EnableTickTimer(TRUE);

    /* Enable and set TIM2 Interrupt */
    TIM2->SR = 0;
    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void EnableTickTimer(FSC_BOOL enable)
{
    if (enable)
    {
        TIM2->CR1 |= TIM_CR1_CEN;
    }
    else
    {
        TIM2->CR1 &= ~TIM_CR1_CEN;
    }
}


void SetTimeInterrupt(FSC_U32 microseconds)
{
  /* Set the offset for the next interrupt request */
  TIM2->CCR1 = TIM2->CNT + microseconds;

  /* Clear the previous and enable the next CC1 Interrupt */
  TIM2->SR = 0;
  TIM2->DIER |= TIM_DIER_CC1IE;
}

void ClearTimeInterrupt(void)
{
    /* Disable the interrupt enable bit */
    TIM2->DIER &= ~TIM_DIER_CC1IE;
}


void InitializeTSTimer(void)
{
    /* Use Timer1 to count at 0.1ms resolution up to one second. */
    /* Use Timer3, triggered by Timer16, to count seconds. */

    /* SystemCoreClock is 48MHz. */
    TIM1->PSC = 4800; /* A prescaler of 4800 gives 0.1ms res */
    TIM1->ARR = 10000; /* A period of 10000 gives 1sec intervals */
    TIM1->CR2 |= TIM_CR2_MMS_1; /* MMS = 0b010 generates TRGO */

    /* Start the count at the end.  Certain registers (PSC,ARR,...) are */
    /* "shadowed" and only get updated on a rollover or other event. */
    TIM1->CNT = 0xFFFFFFFF;

    /* Set Timer3 up as a slave to Timer1.  Timer3 will count in seconds. */
    TIM3->SMCR |= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;
    TIM3->CNT = 0;

    /* Enable both. */
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void EnableTSTimer(FSC_BOOL enable)
{
    if (enable)
    {
        TIM1->CR1 |= TIM_CR1_CEN;
        TIM3->CR1 |= TIM_CR1_CEN;
    }
    else
    {
        TIM1->CR1 &= ~TIM_CR1_CEN;
        TIM3->CR1 &= ~TIM_CR1_CEN;
    }
}
