/*******************************************************************************
 * @file     PlatformI2C.h
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
#ifndef  PLATFORMI2C_H
#define  PLATFORMI2C_H

#include "FSCTypes.h"

/**
 * @brief:     Initialize and (optionally) enable the I2C peripheral.
 * @param None
 * @return None
 ******************************************************************************/
void InitializeI2C(void);

/**
 * @brief Description Write a char buffer to the I2C peripheral.
 * @param SlaveAddress - Slave device bus address
 * @param RegAddrLength - Register Address Byte Length
 * @param DataLength - Length of data to transmit
 * @param PacketSize - Maximum size of each transmitted packet
 * @param IncSize - Number of bytes to send before incrementing addr
 * @param RegisterAddress - Internal register address
 * @param Data - Buffer of char data to transmit
 * @return TRUE - success, FALSE failure
 */
FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

/**
 * @brief Read char data from the I2C peripheral.
 * @param SlaveAddress - Slave device bus address
 * @param RegAddrLength - Register Address Byte Length
 * @param DataLength - Length of data to attempt to read
 * @param PacketSize - Maximum size of each received packet
 * @param IncSize - Number of bytes to recv before incrementing addr
 * @param RegisterAddress - Internal register address
 * @param Data - Buffer for received char data
 * @param Error state.
 */
FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

#endif /* PLATFORMI2C_H */

