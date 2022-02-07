/*******************************************************************************
 * @file     Timing.h
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
#ifndef TIMING_H
#define TIMING_H

#include "FSCTypes.h"

/**
 * @brief Initializes the tick timer.
 *
 * Tick timer is a running clock at 1us, though the frequency
 * can be adjusted.
 *
 * @param None
 * @return None
 */
void InitializeTickTimer(void);

/**
 * @brief Enable/Disables the tick timer.
 * @param enable TRUE = enable, FALSE = disable
 * @return None
 */
void EnableTickTimer(FSC_BOOL enable);

/**
 * @brief Using the match interrupt feature, set up an interrupt
 * in X microseconds.
 * @param microseconds time in microsecond resolution
 * @return None
 */
void SetTimeInterrupt(FSC_U32 microseconds);

/**
 * @brief Disable the timer interrupt.
 * @return None
 */
void ClearTimeInterrupt(void);

/*
 * @brief Time-stamp timer that is currently implemented as linked
 * 1 second and 0.1ms counters.
 * @param None
 * @return None
 */
void InitializeTSTimer(void);

/*
 * @brief The log timestamp is returned as - Upper 16: Seconds, Lower 16: 0.1ms.
 * @param None
 * @return None
 */
FSC_U32 platform_get_log_time(void);

#endif /* TIMING_H */
