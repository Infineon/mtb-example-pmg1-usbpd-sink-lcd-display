/******************************************************************************
* File Name: pdo.h
*
* Description: This header file implements defines function prototypes for the
*              source capability (PDO) evaluation functions which are part of
*              the PMG1 MCU USB-PD Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#ifndef _PDO_H_
#define _PDO_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/

#include "cy_pdstack_common.h"

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief This function is called by the PD stack to allow the application
 * logic to evaluate the Source Capabilities received from the port partner
 * and generate the desired request. The request object is expected to be
 * passed back to the stack through the app_resp_handler() callback.
 *
 * The default implementation of this function matches each of the received
 * source PDOs against the active sink capabilities; and then selects the
 * source PDO that can deliver the maximum power to the system as a sink.
 *
 * @param port Port index the function is performed for.
 * @param srcCap Pointer to PD packet which contains source capabilities.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_src_cap(cy_stc_pdstack_context_t* context, const cy_stc_pdstack_pd_packet_t* srcCap,
        cy_pdstack_app_resp_cbk_t app_resp_handler) ;

/**
 * @brief This function is called by the PD stack to allow the application
 * to evaluate a power request data object received from the port partner and
 * decide whether it should be satisfied. The response to the request should
 * be passed back to the stack through the app_resp_handler() callback.
 *
 * @param port Port index the function is performed for.
 * @param rdo The request data object received.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_rdo(cy_stc_pdstack_context_t* context, cy_pd_pd_do_t rdo, cy_pdstack_app_resp_cbk_t app_resp_handler) ;

#endif /* _PDO_H_ */

/* End of File */

