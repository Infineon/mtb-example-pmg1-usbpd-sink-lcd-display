/******************************************************************************
* File Name: instrumentation.h
*
* Description: This header file defines data structures and function prototypes
*              to monitor CPU resource (execution time and stack) usage in the
*              PMG1 MCU USB-PD Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#ifndef _INSTRUMENTATION_H_
#define _INSTRUMENTATION_H_

#include <stdint.h>

/**
 * @brief Enumeration of all instrumentation fault events.
 */
typedef enum instrumentation_events
{
    INST_EVT_WDT_RESET = 0,                 /**< 0x00: Instrumentation fault event for watchdog reset. */
    INST_EVT_HARD_FAULT = 1                 /**< 0x01: Instrumentation fault event for hard fault. */
} inst_evt_t;

/**
 * @brief Callback function to solution level handler for instrumentation faults.
 */
typedef void (*instrumentation_cb_t)(uint8_t port, uint8_t evt);

/**
 * @brief Initialize data structures associated with application instrumentation.
 * @return None
 */
void instrumentation_init(void);

/**
 * @brief Start any timers or tasks associated with application instrumentation.
 * @return None
 */
void instrumentation_start(void);

/**
 * @brief Perform tasks associated with application instrumentation. The specific
 * functionality implemented is user defined and can vary.
 * @return None
 */
void instrumentation_task(void);

/**
 * @brief Register solution level callback function to be executed when instrumentation fault occurs.
 * @return None
 */
void instrumentation_register_cb(instrumentation_cb_t cb);

#endif /* _INSTRUMENTATION_H_ */

