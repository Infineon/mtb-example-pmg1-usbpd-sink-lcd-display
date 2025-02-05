/*******************************************************************************
* File Name: lcd.h
* Version 1.0
*
* Description:
*  This file contains the structure declaration and function prototypes used in
*  the lcd source code.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2023-2025, Cypress Semiconductor Corporation (an Infineon company) or
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
#ifndef SRC_LCD_LCD_H_
#define SRC_LCD_LCD_H_

/*******************************************************************************
 * Include header files
 ******************************************************************************/

/*******************************************************************************
 * Macro declarations
 ******************************************************************************/
/* Delay for LCD enable pin */
#define LCD_CLOCK_DELAY         (1U)

/* Delay for LCD periodic print */
#define PERIODIC_DELAY          (1000U)

/* LCD command - First row, first column */
#define FIRST_ROW_POS           (0x00U)

/* LCD command - Clears display */
#define CLEAR_DIS_CMD           (0x01U)

/* LCD command - Four bit */
#define FOUR_BIT_INIT_CMD       (0x02U)

/* LCD command - Entry set */
#define ENTRY_SET_CMD           (0x06U)

/* LCD command - Display on, cursor off */
#define DISP_ON_CURS_OFF_CMD    (0x0CU)

/* LCD command - Function set */
#define FUN_SET_CMD             (0x2CU)

/* LCD command - Second row */
#define SECOND_ROW_POS          (0xC0U)

/* Size of Byte */
#define BYTE_SIZE               (8U)

/* LCD timer */
#define LCD_TIMER_ID            (CY_PDUTILS_TIMER_USER_START_ID + 2)

/* LCD Periodic timer */
#define LCD_PERIODIC_TIMER_ID   (CY_PDUTILS_TIMER_USER_START_ID + 3)

/* Number of columns in LCD */
#define LCD_COLUMN_COUNT        (16)

/******************************************************************************
 * Structure/Enum type declaration
 ******************************************************************************/
typedef enum
{
    PD_POWER_SOURCE = 1,
    DCP_SOURCE,
    CDP_SOURCE,
    SDP_SOURCE,
    TYPE_C_DISCONNECT
}power_source_t;

typedef enum
{
    LCD_DATA = 0,
    LCD_CMD,
    MSB_WRITE,
    LCD_CLOCK,
    LSB_WRITE,
    DO_NOTHING
}lcd_write_state_t;

typedef enum
{
    LCD_START = 0,
    LCD_INIT,
    FIRST_ROW,
    PRINT_SOURCE,
    SECOND_ROW,
    PRINT_PDO,
    CLEAR_DISPLAY,
    PERIODIC_TIMER
}lcd_print_state_t;

typedef union
{
    uint8_t byte;
    struct
    {
        uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    };
}byte_parse_t;

/******************************************************************************
 * Global function declaration
 ******************************************************************************/
void lcd_timer_cb (cy_timer_id_t id, void *callbackContext);
void lcd_periodic_timer_cb (cy_timer_id_t id, void *callbackContext);
void lcd_clock(void);
void lcd_write(uint8_t data);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init(void);
void NumToString(int n, char *buffer);
bool lcd_write_nonblock(uint8_t data);
bool lcd_print_nonblock(char *data);
void lcd_update_data(void);
void lcd_update_display(void);
void lcd_print_pd_details(void);

/******************************************************************************
 * End of declaration
 ******************************************************************************/
#endif /* SRC_LCD_LCD_H_ */
