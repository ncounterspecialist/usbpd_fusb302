/*******************************************************************************
 * @file     HWIO.h
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
#ifndef _HWIO_H_
#define _HWIO_H_

#include "FSCTypes.h"

/**
 * @brief Initialize the GPIO pins including, if enabled, debug LEDs
 *        and INT_N IRQ settings.
 * @param None
 * @return None
 */
void InitializeGPIO( void );

/**
 * @brief Enable or disable the INT_N IRQ handler. This will wake up the PD
 *        core from sleep.
 * @param enable TRUE=enable, FALSE=disable
 * @return None
 */
void EnableExtIRQ(FSC_BOOL enable);

#endif /* _HWIO_H_ */
