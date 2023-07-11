/******************************************************************************
* File Name: config.h
*
* Description: This header file defines the application configuration for the PMG1
*              MCU USBPD Sink Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "cybsp.h"

/* Use the default Source PDO selection algorithm. */
#define PD_PDO_SEL_ALGO                         (0u)

/* PMG1-S0 only: Gate driver which supports pull-up for faster turn off when a fault is detected. */
#define VBUS_FET_CTRL_0                         (1u)

/* PMG1-S0 only: Gate driver which does not support internal pull-up (requires external pull-up for turning off. */
#define VBUS_FET_CTRL_1                         (0u)

/* PMG1-S0: Choose the gate driver which should be used to turn the consumer power path ON. */
#define VBUS_FET_CTRL                           (VBUS_FET_CTRL_0)

/* The ADC which should be used to measure VBus voltage on the Type-C side. */
#define APP_VBUS_POLL_ADC_ID                    (CY_USBPD_ADC_ID_0)

/* Period in ms for turning on VBus FET. */
#define APP_VBUS_FET_ON_TIMER_PERIOD            (5u)

/* Period in ms for turning off VBus FET. */
#define APP_VBUS_FET_OFF_TIMER_PERIOD           (1u)

/*
 * The Analog-MUX bus input which is used to measure VBus voltage. Choose AMUXBUS_A on PMG1-S2 and AMUXBUS_B on
 * other devices.
 */
#if defined(CY_DEVICE_SERIES_PMG1S2)
#define APP_VBUS_POLL_ADC_INPUT                 (CY_USBPD_ADC_INPUT_AMUX_A)
#else
#define APP_VBUS_POLL_ADC_INPUT                 (CY_USBPD_ADC_INPUT_AMUX_B)
#endif /* defined(CY_DEVICE_SERIES_PMG1S2) */

/*
 * Enable/Disable delay between fault retries for Type-C/PD faults.
 */
#define FAULT_RETRY_DELAY_EN                    (0u)

#if FAULT_RETRY_DELAY_EN

/*
 * Delay between fault retries in ms.
 */
#define FAULT_RETRY_DELAY_MS                    (500u)

#endif /* FAULT_RETRY_DELAY_EN */

/*
 * Enable/Disable delayed infinite fault recovery for Type-C/PD faults.
 * Fault recovery shall be tried with a fixed delay after configured
 * fault retry count is elapsed.
 */
#define FAULT_INFINITE_RECOVERY_EN              (0u)

#if FAULT_INFINITE_RECOVERY_EN

/*
 * Delayed fault recovery period in ms.
 */
#define FAULT_INFINITE_RECOVERY_DELAY_MS        (5000u)

#endif /* FAULT_INFINITE_RECOVERY_EN */

/*
 * Disable PMG1 device reset on error (watchdog expiry or hard fault).
 * NOTE: Enabling this feature can cause unexpected device reset during SWD debug sessions.
 */
#define RESET_ON_ERROR_ENABLE                   (0u)

/*
 * Watchdog reset period in ms. This should be set to a value greater than
 * 500 ms to avoid significant increase in power consumption.
 */
#define WATCHDOG_RESET_PERIOD_MS                (750u)

/* Disable tracking of maximum stack usage. Can be enabled for debug purposes. */
#define STACK_USAGE_CHECK_ENABLE                (0u)

/*
 * Set this to 1 to Shutdown the SNK FET in the application layer in states where power consumption needs to be
 * reduced to standby level.
 */
#define SNK_STANDBY_FET_SHUTDOWN_ENABLE         (1u)

/*
 * Enable/Disable firmware active LED operation.
 *
 * The blinking LED is enabled by default but it is recommended to disable it
 * for production designs to save power.
 */
#define APP_FW_LED_ENABLE                       (1u)

/*
 * Activity indicator LED timer. The timer is used to indicate that the firmware
 * is functional. The feature is controlled by APP_FW_LED_ENABLE.
 */
#define LED_TIMER_ID                            (CY_PDUTILS_TIMER_USER_START_ID)

/*
 * The LED toggle period (ms) to be used when Type-C connection hasn't been detected.
 */
#define LED_TIMER_PERIOD_DETACHED               (1000u)

/*
 * The LED toggle period (ms) to be used when a Type-C power source is connected.
 */
#define LED_TIMER_PERIOD_TYPEC_SRC              (500u)

/*
 * The LED toggle period (ms) to be used when a USB-PD power source is connected.
 */
#define LED_TIMER_PERIOD_PD_SRC                 (100u)

/*
 * The LED toggle period (ms) to be used when a BC 1.2 DCP (Downstream Charging Port) source without PD support is connected.
 */
#define LED_TIMER_PERIOD_DCP_SRC                (3000u)

/*
 * The LED toggle period (ms) to be used when a BC 1.2 CDP (Charging Downstream Port) source without PD support is connected.
 */
#define LED_TIMER_PERIOD_CDP_SRC                (10000u)

/*
 * Enable watchdog hardware reset for CPU lock-up recovery. Note that watchdog reset can only be enabled if we have
 * any periodic timers running in the application.
 */
#if ((APP_FW_LED_ENABLE) || (RESET_ON_ERROR_ENABLE))
#define WATCHDOG_HARDWARE_RESET_ENABLE          (1u)
#else
#define WATCHDOG_HARDWARE_RESET_ENABLE          (0u)
#endif /* ((APP_FW_LED_ENABLE) || (RESET_ON_ERROR_ENABLE)) */

#endif /* _CONFIG_H_ */

/* End of file */
