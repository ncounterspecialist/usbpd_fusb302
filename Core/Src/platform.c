#include "../../Drivers/FUSB_CORE/platform.h"

#include "HWIO.h"
#include "fan6295.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"


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
#ifndef I2C1_TIMEOUT_MAX
#define I2C1_TIMEOUT_MAX 0xFFFF
#endif


extern FSC_BOOL haveINTReady;
extern I2C_HandleTypeDef hi2c1;
/**
 * @brief Set or return the current vbus voltage level as implemented by
 *        the platform (i.e. supply control, gpio switches, etc.)
 *
 * @param port ID for multiple port controls
 * @param level enumeration
 * @param enable TRUE = ON
 * @param disableOthers Disable other sources in make-before-break fashion
 * @return None or state of vbus.
 */
void platform_set_vbus_lvl_enable(FSC_U8 port, VBUS_LVL level, FSC_BOOL enable,
                                  FSC_BOOL disableOthers)
{
    if (level == VBUS_LVL_5V)
    {
        /* Enable/Disable the 5V Source */
        HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN,
                           enable ? GPIO_PIN_SET : GPIO_PIN_RESET );

        if (disableOthers)
        {
          HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN, GPIO_PIN_RESET );
        }
    }
    else if (level == VBUS_LVL_HV)
    {
        /* Enable/Disable the HV Source */
        HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN,
                           enable ? GPIO_PIN_SET : GPIO_PIN_RESET );

        if (disableOthers)
        {
          HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN, GPIO_PIN_RESET );
        }
    }

    /* Turn off all levels, if requested */
    if ((level == VBUS_LVL_ALL) && (enable == FALSE))
    {
      HAL_GPIO_WritePin( VBUS_PORT, VBUS_5V_PIN, GPIO_PIN_RESET );
      HAL_GPIO_WritePin( VBUS_PORT, VBUS_HV_PIN, GPIO_PIN_RESET );
    }
}

/**
 * @brief Check if the VBUS voltage is enabled
 * @param level VBUS level to check
 * @return TRUE if enabled
 */
FSC_BOOL platform_get_vbus_lvl_enable(FSC_U8 port, VBUS_LVL level)
{
    GPIO_PinState state = GPIO_PIN_RESET;

    /* Additional VBUS levels can be added here as needed. */
    switch (level) {
    case VBUS_LVL_5V:
        /* Return the state of the 5V VBUS Source. */
        state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_5V_PIN );

        break;
    case VBUS_LVL_HV:
        /* Return the state of the HV VBUS Source. */
        state = HAL_GPIO_ReadPin( VBUS_PORT, VBUS_HV_PIN );

        break;
    default:
        /* Otherwise, return FALSE. */
        break;
    }

    return (state == GPIO_PIN_SET) ? TRUE : FALSE;
}

/**
 * @brief Set or return programmable supply (PPS) voltage and current limit.
 *
 * @param port ID for multiple port controls
 * @param mv Voltage in millivolts
 * @return None or Value in mv/ma.
 */
void platform_set_pps_voltage(FSC_U8 port, FSC_U32 mv)
{
#ifdef FSC_HAVE_PPS_SOURCE
  if (mv == 0)
  {
    FAN6295_SetEnable(FALSE);
    FAN6295_SetVoltage(250); /* Set to 5V - setting 0V causes POR */
  }
  else
  {
    FAN6295_SetVoltage(mv);
    FAN6295_SetEnable(TRUE);
  }
#endif /* FSC_HAVE_PPS_SOURCE */
}

/**
 * @brief The function gets the current VBUS level supplied by PPS supply
 *
 * If VBUS is not enabled by the PPS supply the return type is undefined.
 *
 * @param port ID for multiple port controls
 * @return VBUS level supplied by PPS in milivolt resolution
 */
FSC_U16 platform_get_pps_voltage(FSC_U8 port)
{
    return 0;
}

/**
 * @brief Set the maximum current that can be supplied by PPS source
 * @param port ID for multiple port controls
 * @param ma Current in milliamps
 * @return None
 */
void platform_set_pps_current(FSC_U8 port, FSC_U32 ma)
{
#ifdef FSC_HAVE_PPS_SOURCE
    FAN6295_SetILimit(ma);
#endif /* FSC_HAVE_PPS_SOURCE */
}

/**
 * @brief Get the maximum current that the PPS supply is configured to provide
 *
 * If the PPS supply is not currently supplying current the return value is
 * undefined.
 *
 * @param port ID for multiple port controls
 * @return Current in milliamps
 */
FSC_U16 platform_get_pps_current(FSC_U8 port)
{
    return 0;
}

/**
 * @brief Enable/Disable VBus discharge path
 *
 * @param port ID for multiple port controls
 * @param enable TRUE = discharge path ON.
 * @return None
 */
void platform_set_vbus_discharge(FSC_U8 port, FSC_BOOL enable)
{
    /**
     *  Enable/Disable the discharge path
     * @todo - Implement as needed on platforms that support this feature.
     */
    HAL_GPIO_WritePin( VBUS_PORT, VBUS_DISC_PIN,
                       (enable == TRUE) ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/**
 * @brief Enable/Disable VConn path
 *
 * Optional for platforms with separate VConn switch
 *
 * @param port ID for multiple port controls
 * @param enable TRUE = VConn path ON.
 * @return None
 */
void platform_set_vconn(FSC_U8 port, FSC_BOOL enable);

/**
 * @brief The current state of the device interrupt pin
 *
 * @param port ID for multiple port controls
 * @return TRUE if interrupt condition present.  Note: pin is active low.
 */
FSC_BOOL platform_get_device_irq_state(FSC_U8 port)
{
    /**
     * Return the state of the device interrupt signal.
     * Port A, GPIO_PIN_1 -- ACTIVE LOW!
     */
#ifdef FSC_POLLING_MODE
    return TRUE;
#else
    return HAL_GPIO_ReadPin(INT_N_PORT, INT_N_PIN) ? FALSE : TRUE;
#endif /* FSC_POLLING MODE */
}

/**
 * @brief Write a char buffer to the I2C peripheral.
 *
 * Assumes a single I2C bus.  If multiple buses are used, map based on
 * I2C address in the platform code.
 *
 * @param SlaveAddress - Slave device bus address
 * @param RegAddrLength - Register Address Byte Length
 * @param DataLength - Length of data to transmit
 * @param PacketSize - Maximum size of each transmitted packet
 * @param IncSize - Number of bytes to send before incrementing addr
 * @param RegisterAddress - Internal register address
 * @param Data - Buffer of char data to transmit
 * @return TRUE - success, FALSE otherwise
 */
FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    HAL_StatusTypeDef result = HAL_OK;

    result = HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, RegisterAddress,
                               RegAddrLength, Data, DataLength,
                               I2C1_TIMEOUT_MAX);

    return ((result == HAL_OK) ? TRUE : FALSE);
}


/**
 * @brief Read char data from the I2C peripheral.
 *
 * Assumes a single I2C bus.  If multiple buses are used, map based on
 * I2C address in the platform code.
 *
 * @param SlaveAddress - Slave device bus address
 * @param RegAddrLength - Register Address Byte Length
 * @param DataLength - Length of data to attempt to read
 * @param PacketSize - Maximum size of each received packet
 * @param IncSize - Number of bytes to recv before incrementing addr
 * @param RegisterAddress - Internal register address
 * @param Data - Buffer for received char data
 * @return TRUE - success, FALSE otherwise
 */
FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data)
{
    HAL_StatusTypeDef result = HAL_OK;

    result = HAL_I2C_Mem_Read(&hi2c1, SlaveAddress, RegisterAddress,
                              RegAddrLength, Data, DataLength,
                              I2C1_TIMEOUT_MAX);

    return ((result == HAL_OK) ? TRUE : FALSE);
}

/**
 * @brief Perform a blocking delay.
 *
 * @param delayCount - Number of 10us delays to wait
 * @return None
 */
void platform_delay_10us(FSC_U32 tenMicroSecondCounter)
{
    platform_delay(tenMicroSecondCounter * 10);
}

/**
 * @brief Perform a blocking delay.
 *
 * @param delayCount - Number of us delays to wait
 * @return None
 */
void platform_delay(FSC_U32 microseconds)
{
    FSC_U32 currentTime = TIM2->CNT;
//    HAL_Delay(1);

    /* Use the free running clock */
    while ((FSC_U32)((FSC_U32)TIM2->CNT - currentTime) < microseconds);
}

/**
 * @brief Return a system timestamp for use with core timers.
 *
 * @param None
 * @return System time value in units of (milliseconds / TICK_SCALE_TO_MS)
 */
FSC_U32 platform_get_system_time(void)
{
  return TIM2->CNT;
}


/**
 * @brief Return a system timestamp for use with logging functions
 *
 * @param None
 * @return Packed timestamp - format: Upper 16: seconds, Lower 16: 0.1ms.
 */
FSC_U32 platform_get_log_time(void)
{
    /* This packs seconds and tenths of milliseconds into one 32-bit value. */
    return ((FSC_U32) (TIM3->CNT) << 16) + (FSC_U32) (TIM1->CNT);
}

