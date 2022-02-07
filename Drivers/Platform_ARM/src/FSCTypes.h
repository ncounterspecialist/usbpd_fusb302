/*******************************************************************************
 * @file     FSCTypes.h
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
#ifndef FSCTYPES_H
#define FSCTYPES_H

/* Define compiler macros */
#if defined ( __GNUC__ )
  #define __ASM            __asm
  #define __INLINE         inline
  #define __STATIC_INLINE  static inline
  #define __PACKED         __attribute__((packed))
  #define __ALIGNED(n)     __attribute__((aligned(n)))
#else
  #define __ASM
  #define __INLINE
  #define __STATIC_INLINE
  #define __PACKED
  #define __ALIGNED(n)
#endif

 /* Define Boolean types */
typedef enum _BOOL
{
    FALSE = 0,
    TRUE
} FSC_BOOL;

/* Signed types */
typedef signed char         FSC_S8;
typedef signed short int    FSC_S16;
typedef signed long int     FSC_S32;

/* Unsigned types */
typedef unsigned char       FSC_U8;
typedef unsigned short int  FSC_U16;
typedef unsigned long int   FSC_U32;

#endif /* FSCTYPES_H */

