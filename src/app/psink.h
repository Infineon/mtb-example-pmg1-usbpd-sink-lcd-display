/******************************************************************************
* File Name: psink.h
*
* Description: This header file defines function prototypes for power consumer
*              path control and fault detection as part of the PMG1 MCU USB-PD
*              Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#ifndef _PSINK_H_
#define _PSINK_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/
#include "cy_pdstack_common.h"

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief This function sets the expected VBus voltage when
 * PMG1 is functioning as a sink. The voltage level is used
 * to configure the Over-Voltage Protection on the device.
 *
 * @param port Port index the function is performed for.
 * @param volt_mV Expected VBus voltage level in mV units.
 *
 * @return None
 */
void psnk_set_voltage (cy_stc_pdstack_context_t * context, uint16_t volt_mV);

/**
 * @brief This function notifies the application code about
 * the amount of current the system is allowed to take from
 * the VBus power supply. The application logic should configure its
 * load and battery charging circuits based on this value so that
 * the power source does not see any overload condition.
 *
 * @param port Port index the function is performed for.
 * @param cur_10mA Maximum allowed current in 10mA units.
 *
 * @return None
 */
void psnk_set_current (cy_stc_pdstack_context_t * context, uint16_t cur_10mA);

/**
 * @brief Function to enable the power consumer path to that the system
 * can received power from the Type-C VBus. The expected voltage and maximum
 * allowed current would have been notified through the psnk_set_voltage()
 * and psnk_set_current() functions.
 *
 * @param port Port index the function is performed for.
 * @return None
 */
void psnk_enable (cy_stc_pdstack_context_t * context);

/**
 * @brief Disable the VBus power sink path and discharge VBus supply down
 * to a safe level. This function is called by the PD stack at times when
 * the system is not allowed to draw power from the VBus supply. The application
 * can use this call to initiate a VBus discharge operation so that a subsequent
 * Type-C connection is speeded up. The snk_discharge_off_handler callback
 * function should be called once VBus has been discharged down to vSafe0V.
 *
 * @param port Port index the function is performed for.
 * @param snk_discharge_off_handler Sink Discharge fet off callback pointer
 * @return None
 */
void psnk_disable (cy_stc_pdstack_context_t * context, cy_pdstack_sink_discharge_off_cbk_t snk_discharge_off_handler);

#endif /* _PSINK_H_ */

/* End of File */
