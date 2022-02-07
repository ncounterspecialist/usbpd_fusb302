/*******************************************************************************
 * @file     fan6295.c
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
#include "fan6295.h"
#include "FSCTypes.h"

#include "../../FUSB_CORE/fusb30X.h"

#define FAN6295_ADDR  0x62                  /* I2C address of the device */

/*******************************************************************************
 * Define register addresses
 ******************************************************************************/
#define REG_CONTROL0  0x01
#define REG_CONTROL1  0x02
#define REG_VREF_MSB  0x04
#define REG_VREF_LSB  0x05
#define REG_IREF_MSB  0x06
#define REG_IREF_LSB  0x07
#define REG_INTERRUPT 0x11

#define VREF_STEP     0x01                 /* 0-20.46V @ 20mV step */

void FAN6295_Initialize(void)
{
  FSC_U8 data[2] = {0x00, 0x00};

  DeviceWrite(FAN6295_ADDR, REG_CONTROL0, 2, data);
}

void FAN6295_SetEnable(FSC_BOOL enable)
{
  FSC_U8 data = enable ? 0x01 : 0x00;

  DeviceWrite(FAN6295_ADDR, REG_CONTROL0, 1, &data);
}

void FAN6295_SetVoltage(FSC_U32 value_20mv)
{
  FSC_U8 data[2];

  /* Shift into register format */
  data[0] = value_20mv >> 2;
  data[1] = (value_20mv << 6) | VREF_STEP;

  DeviceWrite(FAN6295_ADDR, REG_VREF_MSB, 2, data);
}

void FAN6295_SetILimit(FSC_U32 ilim_ma)
{
  /* NOTE - constants applicable to specific dev board */
  FSC_U32 irefmax = 1534;   /* mv */
  FSC_U32 rcs = 5;          /* mOhm */
  FSC_U32 avccr = 60;       /* Gain */

  FSC_U32 iref = (ilim_ma * 1023 * rcs * avccr) / (irefmax * 1000);

  FSC_U8 data[2];
  data[0] = iref >> 2;      /* Upper 8 */
  data[1] = iref << 6;      /* Lower 2 */

  DeviceWrite(FAN6295_ADDR, REG_IREF_MSB, 2, data);
}
