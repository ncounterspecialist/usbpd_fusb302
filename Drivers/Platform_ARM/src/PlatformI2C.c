/*******************************************************************************
 * @file     PlatformI2C.c
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
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"

#include "PlatformI2C.h"

#ifndef I2C1_TIMEOUT_MAX
#define I2C1_TIMEOUT_MAX 0xFFFF
#endif

/*******************************************************************************
 * i2c device object
 ******************************************************************************/
I2C_HandleTypeDef I2cHandle;

void InitializeI2C(void)
{
    /* Initialize the I2C GPIO Pins */
    GPIO_InitTypeDef  GPIO_InitStruct;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();

    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF1_I2C2; Pankaj

    GPIO_InitStruct.Pin       = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /** Initialize the I2C Peripheral!
     * On the STM32F072B_DISCO Board we are going to use:
     * I2C Unit 2
     * SCL: Port B Pin 10
     * SDA: Port B Pin 11
     * Timing:
     * From STM32Cube: 0x10805D88 for 100kHz @ 48MHz
     *                (Rise time = 100 ns, Fall time = 100 ns)
     * From STM32Cube: 0x0090194B for 400kHz @ 48MHz
     *                (Rise time = 100 ns, Fall time = 100 ns)
     * From STM32Cube: 0x00700818 for 1Mhz @ 48MHz
     *                (Rise time = 100 ns, Fall time = 100 ns)
     */
    I2cHandle.Instance             = I2C2;

    I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
//    I2cHandle.Init.Timing          = 0x00700818; Pankaj
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.OwnAddress1     = 0;
    I2cHandle.Init.OwnAddress2     = 0;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&I2cHandle);
}
