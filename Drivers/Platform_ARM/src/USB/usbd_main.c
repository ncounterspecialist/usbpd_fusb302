#include "usbd_main.h"

#include "usbd_hid.h"

USBD_HandleTypeDef USBD_Device;

/*******************************************************************************
 * Function:        InitializeUSB
 * Input:           None
 * Return:          None
 * Description:     Initializes all the timers that are used.
 ******************************************************************************/
void InitializeUSB( void )
{
    /* Init Device Library */
    USBD_Init(&USBD_Device, &HID_Desc, 0);

    /* Register the HID class */
    USBD_RegisterClass(&USBD_Device, &USBD_HID);

    /* Start Device Process */
    USBD_Start(&USBD_Device);
}
