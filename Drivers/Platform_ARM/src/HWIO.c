/*******************************************************************************
 * @file     HWIO.c
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
#include "HWIO.h"
#include "fan6295.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "../../FUSB_CORE/platform.h"

/*******************************************************************************
 * GPIO definition for interrupt pin
 ******************************************************************************/
#define INT_N_PORT      GPIOA
#define INT_N_PIN       GPIO_PIN_1

#define DEBUG_PIN       GPIO_PIN_0

/*******************************************************************************
 * GPIOs assigned to load switches
 ******************************************************************************/
#define VBUS_PORT       GPIOC
#define VBUS_5V_PIN     GPIO_PIN_3
#define VBUS_HV_PIN     GPIO_PIN_4

#define VBUS_DISC_PIN   GPIO_PIN_0

extern FSC_BOOL haveINTReady;

void InitializeGPIO( void )
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Outputs (VBUS Controls, etc.) on Port C */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* Configure IOs in output push-pull mode to drive VBUS outputs */
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Pin = VBUS_5V_PIN;
    HAL_GPIO_Init(VBUS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = VBUS_HV_PIN;
    HAL_GPIO_Init(VBUS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Pin = VBUS_DISC_PIN;
    HAL_GPIO_Init(VBUS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Pin = DEBUG_PIN;
    HAL_GPIO_Init(INT_N_PORT, &GPIO_InitStruct);

    /* Inputs (INT_N) on Port A */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* INT_N setup... */
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Pin = INT_N_PIN;
    HAL_GPIO_Init(INT_N_PORT, &GPIO_InitStruct);

    /* Enable and set EXTI line 0 Interrupt */
//    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 1, 0); Pankaj
//    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn); Pankaj
}


#ifdef FSC_HAVE_DP
FSC_BOOL platform_dp_enable_pins(FSC_BOOL enable, FSC_U32 config)
{
  return TRUE;
}

void platform_dp_status_update(FSC_U32 status)
{
}
#endif /* FSC_HAVE_DP */
