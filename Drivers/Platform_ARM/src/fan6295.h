/*******************************************************************************
 * @file     fan6295.h
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
#ifndef FAN6295_H
#define FAN6295_H

#include "FSCTypes.h"

/**
 * @brief Initialize the FAN6295 power adapter controller
 * @param None
 * @return None
 */
void FAN6295_Initialize(void);

/*
 * @brief Turn the 6295 board VBUS load switch on or off.
 * @note  Not a RMW - disables all other CONTROL0 bits
 * @param enable TRUE = Turn on switch, FALSE = Turn off switch
 * @return None
 */
void FAN6295_SetEnable(FSC_BOOL enable);

/*
 * @brief Set the VREF value to produce the desired output.
 * @param value_20mv Requested voltage in mv (0mv - 20000mv) 20mv LSB
 * @return None
 */
void FAN6295_SetVoltage(FSC_U32 value_20mv);

/*
 * @brief Set the IREF value to produce the desired current limit.
 * @param ilim_ma Requested current limit - 1mA LSB
 * @return None
 */
void FAN6295_SetILimit(FSC_U32 ilim_ma);

#endif /* FAN6295_H_ */

