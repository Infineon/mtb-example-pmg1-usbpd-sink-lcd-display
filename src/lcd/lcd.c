/******************************************************************************
* File Name: lcd.c
* Version 1.0
*
* Description:
*  This file provides the source code to the APIs for initializing
*  LCD, Send data/command to LCD
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cybsp.h"
#include "cy_pdl.h"
#include "cy_pdutils_sw_timer.h"
#include "cy_pdstack_common.h"
#include "lcd.h"

/******************************************************************************
 * Global variables declaration
 ******************************************************************************/
uint16_t volt = 0U, current = 0U;
uint8_t dataPtr = 0;
volatile bool contractFlag = false, lcdTimerFlag = false;
char lcdData[LCD_COLUMN_COUNT + 1];

byte_parse_t byteParse, byteParseArr[LCD_COLUMN_COUNT + 1];
extern uint8_t srcType;
extern lcd_write_state_t lcd_write_state;
extern lcd_print_state_t lcd_print_state;
extern cy_stc_pdutils_sw_timer_t gl_TimerCtx;
extern cy_stc_pdstack_context_t gl_PdStackPort0Ctx;

/*******************************************************************************
* Function Name: lcd_timer_cb
********************************************************************************
* Summary:
*   Toggles LCD EN (enable) pin for Read/Write
*
* Parameters:
*  id - Timer ID
*  callbackContext
*
* Return:
*  None
*
*******************************************************************************/
void lcd_timer_cb (
        cy_timer_id_t id,            /**< Timer ID for which callback is being generated. */
        void *callbackContext)       /**< Timer module Context. */
{

    /* Sets the Enable signal to low */
    Cy_GPIO_Clr(CYBSP_LCD_EN_PORT, CYBSP_LCD_EN_PIN);

    lcd_write_state = (lcdTimerFlag == false)?(LSB_WRITE):(DO_NOTHING);
}

/*******************************************************************************
* Function Name: lcd_periodic_timer_cb
********************************************************************************
* Summary:
*   - Sets the LCD Print State to CLEAR_DISPLAY
*   - Sets the LCD Write State to LCD_CMD
*
* Parameters:
*  id - Timer ID
*  callbackContext
*
* Return:
*  None
*
*******************************************************************************/
void lcd_periodic_timer_cb (
        cy_timer_id_t id,            /**< Timer ID for which callback is being generated. */
        void *callbackContext)       /**< Timer module Context. */
{
    lcd_print_state = CLEAR_DISPLAY;
    lcd_write_state = LCD_CMD;
}

/*******************************************************************************
* Function Name: lcd_clock
********************************************************************************
* Summary:
*   Toggles LCD EN (enable) pin for Read/Write
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void lcd_clock()
{
    /* Pulling enable signal to high */
    Cy_GPIO_Set(CYBSP_LCD_EN_PORT, CYBSP_LCD_EN_PIN);

    /* Delay (1ms) - Time to read/write in Data Registers */
    Cy_SysLib_Delay(LCD_CLOCK_DELAY);

    /* Pulling enable Signal to low */
    Cy_GPIO_Clr(CYBSP_LCD_EN_PORT, CYBSP_LCD_EN_PIN);
}

/*******************************************************************************
* Function Name: lcd_write_4_bits
********************************************************************************
* Summary:
*   Writes the received data to data lines (4-7)
*
* Parameters:
*  value 0 - GPIO value to be written in data line 4
*  value 1 - GPIO value to be written in data line 5
*  value 2 - GPIO value to be written in data line 6
*  value 3 - GPIO value to be written in data line 7
*
* Return:
*  None
*
*******************************************************************************/
void lcd_write_4_bits(uint8_t value0, uint8_t value1, uint8_t value2, uint8_t value3)
{
    Cy_GPIO_Write(CYBSP_LCD_DAT4_PORT, CYBSP_LCD_DAT4_PIN, value0);
    Cy_GPIO_Write(CYBSP_LCD_DAT5_PORT, CYBSP_LCD_DAT5_PIN, value1);
    Cy_GPIO_Write(CYBSP_LCD_DAT6_PORT, CYBSP_LCD_DAT6_PIN, value2);
    Cy_GPIO_Write(CYBSP_LCD_DAT7_PORT, CYBSP_LCD_DAT7_PIN, value3);
}

/*******************************************************************************
* Function Name: lcd_write
********************************************************************************
* Summary:
*   - Sends the higher nibble bits to data lines (4-7)
*   - Sends the lower nibble Bits to data lines (4-7)
*
* Parameters:
*  data - Sends the data to LCD
*
* Return:
*  None
*
*******************************************************************************/
void lcd_write(uint8_t data)
{
    byteParse.byte = data;

    /* Writing MSB nibble to data lines (4-7) */
    lcd_write_4_bits(byteParse.bit4, byteParse.bit5, byteParse.bit6, byteParse.bit7);

    lcd_clock();

    /* Writing LSB nibble to data lines(4-7) */
    lcd_write_4_bits(byteParse.bit0, byteParse.bit1, byteParse.bit2, byteParse.bit3);

    lcd_clock();
}

/*******************************************************************************
* Function Name: lcd_cmd
********************************************************************************
* Summary:
*   - Sets RS signal to low
*   - Sends cmd to data lines
*
* Parameters:
*  cmd - Sends the command to LCD
*
* Return:
*  None
*
*******************************************************************************/
void lcd_cmd(uint8_t cmd)
{
    /* Sets RS signal to low */
    Cy_GPIO_Clr(CYBSP_LCD_RS_PORT, CYBSP_LCD_RS_PIN);

    /* Send command */
    lcd_write(cmd);
}

/*******************************************************************************
* Function Name: lcd_data
********************************************************************************
* Summary:
*   - Sets RS signal to high
*   - Sends data to data lines
*
* Parameters:
*  data - Sends the data to LCD
*
* Return:
*  None
*
*******************************************************************************/
void lcd_data(uint8_t data)
{
    /* Sets RS signal to high */
    Cy_GPIO_Set(CYBSP_LCD_RS_PORT, CYBSP_LCD_RS_PIN);

    /* Send data */
    lcd_write(data);
}

/*******************************************************************************
* Function Name: lcd_init
********************************************************************************
* Summary:
*   - Sends the init sequence
*   - Sets to 4-bit mode
*   - Function set (Number of lines, Font)
*   - Clear display
*   - Entry set (Shift)
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void lcd_init()
{
    /* Write 0x02 (Setting to 4-bit mode) */
    lcd_cmd(FOUR_BIT_INIT_CMD);

    /* Function set */
    lcd_cmd(FUN_SET_CMD);
    Cy_SysLib_DelayUs(40);

    /* Display on, Cursor off */
    lcd_cmd(DISP_ON_CURS_OFF_CMD);
    Cy_SysLib_DelayUs(40);

    /* Clear the display */
    lcd_cmd(CLEAR_DIS_CMD);
    Cy_SysLib_Delay(2);

    /* Entry mode set */
    lcd_cmd(ENTRY_SET_CMD);
    Cy_SysLib_DelayUs(40);
}

/*******************************************************************************
* Function Name: NumToString
********************************************************************************
* Summary:
*   - Converts Integer to String
*
* Parameters:
*  n - Integer
*  buffer - String to store the converted value
*
* Return:
*  None
*
*******************************************************************************/
void NumToString(int n, char *buffer)
{
    uint8_t i = 0, j =0;
    char temp[10];

    while(n!=0)
    {
        temp[i++] = n%10 + '0';
        n = n/10;
    }
    for(; j<i ; j++)
    {
        buffer[j] = temp[i -j -1];
    }
    buffer[i] = '\0';
}

/*******************************************************************************
* Function Name: lcd_write_nonblock
********************************************************************************
* Summary:
*   - Sends the data/command to LCD
*   - Uses Non-Blocking Delay
*
* Parameters:
*  data - Sends the data to LCD
*
* Return:
*  bool - true/false
*
*******************************************************************************/
bool lcd_write_nonblock(uint8_t data)
{
    /* Variable initializations */
    bool write_function_status = false;

    byteParse.byte = data;

    switch(lcd_write_state)
    {
        /* Clears the RS Pin */
        case LCD_CMD:
            /* Sets RS signal to high */
            Cy_GPIO_Clr(CYBSP_LCD_RS_PORT, CYBSP_LCD_RS_PIN);

            lcd_write_state = MSB_WRITE;
            break;

        /* Sets the RS Pin */
        case LCD_DATA:
            /* Sets RS signal to high */
            Cy_GPIO_Set(CYBSP_LCD_RS_PORT, CYBSP_LCD_RS_PIN);

            lcd_write_state = MSB_WRITE;
            break;

        /* Sends the MSB nibble data */
        case MSB_WRITE:
            /* Writing MSB nibble to data lines (4-7) */
            lcd_write_4_bits(byteParse.bit4, byteParse.bit5, byteParse.bit6, byteParse.bit7);

            /* Sets the Enable signal to High */
            Cy_GPIO_Set(CYBSP_LCD_EN_PORT, CYBSP_LCD_EN_PIN);

            lcdTimerFlag = false;
            lcd_write_state = LCD_CLOCK;
            break;

        /* Starts the timer to toggle the enable signal */
        case LCD_CLOCK:
            if (!Cy_PdUtils_SwTimer_IsRunning(&gl_TimerCtx, (cy_timer_id_t)LCD_TIMER_ID))
            {
                /* Start a software timer for LCD */
                Cy_PdUtils_SwTimer_Start (&gl_TimerCtx, (void *)&gl_PdStackPort0Ctx, (cy_timer_id_t)LCD_TIMER_ID,
                        LCD_CLOCK_DELAY, lcd_timer_cb);
            }
            break;

        /* Sends the LSB nibble data */
        case LSB_WRITE:
            /* Writing LSB nibble to data lines(4-7) */
            lcd_write_4_bits(byteParse.bit0, byteParse.bit1, byteParse.bit2, byteParse.bit3);

            /* Sets the Enable signal to High */
            Cy_GPIO_Set(CYBSP_LCD_EN_PORT, CYBSP_LCD_EN_PIN);

            lcdTimerFlag = true;
            lcd_write_state = LCD_CLOCK;
            break;

        /* Do Nothing */
        case DO_NOTHING:
            write_function_status = true;
            break;
    }
    return write_function_status;
}

/*******************************************************************************
* Function Name: lcd_print_nonblock
********************************************************************************
* Summary:
*   - Sends the data byte by byte
*
* Parameters:
*  data - Prints the string in LCD
*
* Return:
*  bool - True/false
*
*******************************************************************************/
bool lcd_print_nonblock(char *data)
{
    /* Variable initialization */
    uint8_t len = 0U;
    bool write_status = false, print_status = false;

    /* Getting the length of the string */
    len = strlen(data);

    /* Sends the data byte by byte depending on length of the string */
    if (dataPtr < len)
    {
        /* Sending data */
        write_status = lcd_write_nonblock((uint8_t)(*(data+dataPtr)));

        if (write_status == true)
        {
            dataPtr++;
            lcd_write_state = LCD_DATA;
        }
    }
    else
    {
        dataPtr = 0;
        print_status = true;
    }
    return print_status;
}

/*******************************************************************************
* Function Name: lcd_update_data
********************************************************************************
* Summary:
*   - Gets the Type of Source used to power the kit
*   - Gets the Current and Voltage details if PD contract happens
*   - Stores the details in 2D array
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void lcd_update_data(void)
{
    uint8_t length = 0U;

    /* Initializing the arrays to zero */
    memset (lcdData, 0, sizeof(lcdData));

    switch (srcType)
    {
        /* PD Power Source */
        case PD_POWER_SOURCE:
            strcpy((char *)&byteParseArr,"PD Power Source");

            /* After PD Contract is done */
            if(gl_PdStackPort0Ctx.dpmConfig.contractExist == 1u)
            {
                contractFlag = true;

                cy_stc_pdstack_dpm_status_t dpm_stat = gl_PdStackPort0Ctx.dpmStat;

                /* PD contract voltage & current */
                volt = dpm_stat.contract.maxVolt;
                current = (dpm_stat.contract.curPwr) * 10;

                /* Print voltage in mV */
                NumToString((int)volt, lcdData);
                strcat(lcdData, "mV ");

                length = strlen(lcdData);

                /* Print current in mA */
                NumToString((int)current, &lcdData[length]);
                strcat(lcdData, "mA");
            }
            else
            {
                contractFlag = false;
                strcpy(lcdData, "USB-C disconnect");
            }
            break;

        /* DCP source */
        case DCP_SOURCE:
            strcpy((char *)&byteParseArr, "DCP source");
            break;

        /* CDP source */
        case CDP_SOURCE:
            strcpy((char *)&byteParseArr, "CDP source");
            break;

        /* SDP source */
        case SDP_SOURCE:
            strcpy((char *)&byteParseArr, "SDP source");
            break;

        /* Type-C disconnect */
        case TYPE_C_DISCONNECT:
            strcpy((char *)&byteParseArr, "USB-C disconnect");
            break;
    }
}

/*******************************************************************************
* Function Name: lcd_update_details
********************************************************************************
* Summary:
*   - Displays the Type of source and PD details if PD contract happens in LCD
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void lcd_update_display(void)
{
    /* Print Source type and PD contract details state machine */
    switch (lcd_print_state)
    {
        /* Sets the cursor to the First row of LCD */
        case FIRST_ROW:
            if (lcd_write_nonblock(FIRST_ROW_POS))
            {
                lcd_print_state = PRINT_SOURCE;
                lcd_write_state = LCD_DATA;
            }
            break;

        /* Prints the Type of source connected in LCD */
        case PRINT_SOURCE:
            /* Prints type of source connected */
            if (lcd_print_nonblock((char *)&byteParseArr))
            {
                if (contractFlag == true)
                {
                    lcd_print_state = SECOND_ROW;
                    lcd_write_state = LCD_CMD;
                }
                else
                {
                    lcd_print_state = PERIODIC_TIMER;
                }
            }
            break;

        /* Sets the cursor to the Second row of LCD */
        case SECOND_ROW:
            if (lcd_write_nonblock(SECOND_ROW_POS))
            {
                lcd_print_state = PRINT_PDO;
                lcd_write_state = LCD_DATA;
            }
            break;

        /* Prints the PDO details in the second row */
        case PRINT_PDO:
            if (lcd_print_nonblock(lcdData))
            {
                lcd_print_state = PERIODIC_TIMER;
            }
            break;

        /* Clears the LCD display */
        case CLEAR_DISPLAY:
            if (lcd_write_nonblock(CLEAR_DIS_CMD))
            {
                lcd_print_state = FIRST_ROW;
                lcd_write_state = LCD_CMD;
            }
            break;

        /* Starts the timer for every 3 seconds */
        case PERIODIC_TIMER:
            if (!Cy_PdUtils_SwTimer_IsRunning(&gl_TimerCtx, (cy_timer_id_t)LCD_PERIODIC_TIMER_ID))
            {
                /* Start a software timer for LCD */
                Cy_PdUtils_SwTimer_Start (&gl_TimerCtx, (void *)&gl_PdStackPort0Ctx, (cy_timer_id_t)LCD_PERIODIC_TIMER_ID,
                        PERIODIC_DELAY, lcd_periodic_timer_cb);
            }
            break;
    }
}

/*******************************************************************************
* Function Name: lcd_print_pd_details
********************************************************************************
* Summary:
*   - Gets the Type of Source used to power the kit
*   - Gets the Current and Voltage details if PD contract happens
*   - Stores the details in 2D array
*   - Displays the Type of source and PD details if PD contract happens in LCD
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void lcd_print_pd_details()
{
    /* Gets the type of source and PD details */
    lcd_update_data();

    /* Displays the data in LCD */
    lcd_update_display();
}

/* [] END OF FILE */
