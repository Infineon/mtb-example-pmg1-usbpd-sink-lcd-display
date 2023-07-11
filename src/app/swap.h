/******************************************************************************
* File Name: swap.h
*
* Description: This header file defines function prototypes for handling of
*              USB Power-Delivery Role Swap requests as part of the PMG1 MCU USB-PD
*              Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#ifndef _SWAP_H_
#define _SWAP_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/

#include "config.h"
#include "cy_pdstack_common.h"

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/
/**
 * @brief This function evaluates Data role swap request
 *
 * @param port Port index the function is performed for.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_dr_swap(cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler);

/**
 * @brief This function evaluates Power role swap request
 *
 * @param port Port index the function is performed for.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_pr_swap(cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler);

/**
 * @brief This function evaluates VConn swap request
 *
 * @param port Port index the function is performed for.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_vconn_swap(cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler);

/**
 * @brief This function evaluates Fast role swap request
 *
 * @param port Port index the function is performed for.
 * @param app_resp_handler Application handler callback function.
 *
 * @return None
 */
void eval_fr_swap(cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler);

#endif /* _SWAP_H_ */

/* End of File */

