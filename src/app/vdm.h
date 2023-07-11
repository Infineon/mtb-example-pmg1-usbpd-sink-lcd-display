/******************************************************************************
* File Name: vdm.h
*
* Description: This header file defines data structures and function prototypes
*              for the Vendor Defined Message (VDM) handler as part of the PMG1
*              MCU USB-PD Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#ifndef _VDM_H_
#define _VDM_H_

/*******************************************************************************
 * Header files including
 ******************************************************************************/

#include "cy_pdstack_common.h"

/* Data object index of the ID Header field in the Discover Identity response. */
#define ID_HEADER_DO_INDEX                      (1u)

/* Data object index of the Product VDO field in the Discover Identity response. */
#define PRODUCT_VDO_DO_INDEX                    (3u)

/* Position of Vendor ID portion in ID Header VDO. */
#define ID_HEADER_VID_POS                       (0u)

/* Mask for Vendor ID portion in ID Header VDO. */
#define ID_HEADER_VID_MASK                      (0xFFFFUL)

/* Position of Product ID portion in Product VDO. */
#define PRODUCT_VDO_PID_POS                     (16u)

/* Mask for Product ID portion in Product VDO. */
#define PRODUCT_VDO_PID_MASK                    (0xFFFF0000UL)

/*****************************************************************************
 * Global Function Declaration
 *****************************************************************************/

/**
 * @brief Store the VDM data from the configuration table.
 *
 * This function retrieves the VDM data (for CCG as UFP) that is stored in
 * the configuration table and stores it in the run-time data structures.
 *
 * @param port USB-PD port for which the data is to be stored.
 *
 * @return None.
 */
void vdm_data_init (cy_stc_pdstack_context_t * context);

/**
 * @brief This function is responsible for analysing and processing received VDM.
 * This function also makes a decision about necessity of response to the received
 * VDM.
 *
 * @param port Port index the function is performed for.
 * @param vdm Pointer to pd packet which contains received VDM.
 * @param vdm_resp_handler VDM handler callback function.
 *
 * @return None
 */
void eval_vdm(cy_stc_pdstack_context_t * context, const cy_stc_pdstack_pd_packet_t *vdm,
        cy_pdstack_vdm_resp_cbk_t vdm_resp_handler);

#endif /* _VDM_H_ */

/* End of File */

