/******************************************************************************
* File Name: swap.c
*
* Description: This source file implements functions that evaluate various
*              USB Power-Delivery Role Swap requests as part of the PMG1 MCU USB-PD
*              Sink Code Example for ModusToolBox.
*
* Related Document: See README.md
*
*******************************************************************************/


#include "config.h"
#include "swap.h"
#include "app.h"

#define APP_PD_SWAP_RESP_ACCEPT         (0u)
#define APP_PD_SWAP_RESP_REJECT         (1u)
#define APP_PD_SWAP_RESP_WAIT           (2u)
#define APP_PD_SWAP_RESP_NOT_SUPP       (3u)

/* Configure the Swap Responses. Should be REJECT for USBPD Sink-UFP Example */
volatile uint8_t pr_swap_response = APP_PD_SWAP_RESP_NOT_SUPP;
volatile uint8_t dr_swap_response = APP_PD_SWAP_RESP_NOT_SUPP;
volatile uint8_t vconn_swap_response = APP_PD_SWAP_RESP_NOT_SUPP;

static cy_en_pdstack_app_req_status_t get_response(cy_stc_pdstack_context_t * context, uint8_t raw_resp)
{
#if CY_PD_REV3_ENABLE
    cy_stc_pd_dpm_config_t* dpm = &(context->dpmConfig);
#endif /* CY_PD_REV3_ENABLE */

    cy_en_pdstack_app_req_status_t retVal;

    switch (raw_resp)
    {
    case APP_RESP_ACCEPT:
        retVal = CY_PDSTACK_REQ_ACCEPT;
        break;

    case APP_RESP_WAIT:
        retVal =  CY_PDSTACK_REQ_WAIT;
        break;

#if CY_PD_REV3_ENABLE
    case APP_RESP_NOT_SUPPORTED:
        if(dpm->specRevSopLive <= CY_PD_REV2)
        {
            retVal = CY_PDSTACK_REQ_REJECT;
        }
        else
        {
            retVal = CY_PDSTACK_REQ_NOT_SUPPORTED;
        }
        break;
#endif /* CY_PD_REV3_ENABLE */

    default:
        retVal = CY_PDSTACK_REQ_REJECT;
        break;
    }
    return retVal;
}

void eval_dr_swap (cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    cy_en_pdstack_app_req_status_t result = CY_PDSTACK_REQ_REJECT;

    if (app_get_status(context->port)->alt_mode_entered == true)
    {
        result = CY_PDSTACK_REQ_SEND_HARD_RESET;
    }
    else
    {
        result = get_response(context, dr_swap_response);
    }

    app_get_resp_buf(context->port)->reqStatus = result;
    app_resp_handler(context, app_get_resp_buf(context->port));
}

void eval_pr_swap (cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    cy_en_pdstack_app_req_status_t result = CY_PDSTACK_REQ_REJECT;

#if ((!CY_PD_SINK_ONLY) && (!CY_PD_SOURCE_ONLY))
    const dpm_status_t* dpm = dpm_get_info(context->port);
    uint8_t pdo_mask;

    if(dpm->curPortRole == PRT_ROLE_SOURCE)
    {
        pdo_mask = dpm->srcPdoMask;
    }
    else
    {
        pdo_mask = dpm->snkPdoMask;
    }

    /*
     * Default response shall be NOT_SUPPORTED instead of REJECT if current mode
     * is PD REV3 and port role is source/sink only.
     */
#if CY_PD_REV3_ENABLE
    if (
            (dpm->specRevSopLive >= PD_REV3) &&
            (dpm->portRole != PRT_DUAL)
       )
    {
        result = REQ_NOT_SUPPORTED;
    }
#endif /* CY_PD_REV3_ENABLE */

    if (
            (dpm->deadBat == false) && (dpm->portRole == PRT_DUAL) &&
            (
             ((pdo_mask & (0x1 << PD_EXTERNALLY_POWERED_BIT_POS)) == 0) ||
             (dpm->curPortRole == PRT_ROLE_SINK) ||
             (PD_GET_PTR_HOST_CFG_TBL(context->port)->ext_powered_prs != 0)
            )
       )
    {
        result = get_response(context->port, pr_swap_response);
    }

#else /* (CY_PD_SINK_ONLY || CY_PD_SOURCE_ONLY) */

    if (context->dpmConfig.specRevSopLive >= CY_PD_REV3)
    {
        result = CY_PDSTACK_REQ_NOT_SUPPORTED;
    }

#endif /* ((!CY_PD_SINK_ONLY) && (!CY_PD_SOURCE_ONLY)) */

    app_get_resp_buf(context->port)->reqStatus = result;
    app_resp_handler(context, app_get_resp_buf(context->port));
}

void eval_vconn_swap (cy_stc_pdstack_context_t * context, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    cy_en_pdstack_app_req_status_t result = CY_PDSTACK_REQ_REJECT;

#if !PMG1_VCONN_DISABLE
    const cy_stc_pd_dpm_config_t* dpm = &(context->dpmConfig);

    /* We can always accept a swap away from the VConn Source role. */
    if (
            (dpm->vconnLogical == true)
       )
    {
        result = CY_PDSTACK_REQ_ACCEPT;
    }
    else
    {
        result = get_response(context, vconn_swap_response);

        if (result == CY_PDSTACK_REQ_ACCEPT)
        {
#if VCONN_OCP_ENABLE
            /* Do not allow VCONN_SWAP to become VConn source if fault is active. */
            if ((app_get_status(context->port)->fault_status & APP_PORT_VCONN_FAULT_ACTIVE) != 0)
            {
                result = CY_PDSTACK_REQ_REJECT;
            }
#endif /* VCONN_OCP_ENABLE */
        }
    }
#endif /* !PMG1_VCONN_DISABLE */

    app_get_resp_buf(context->port)->reqStatus = result;
    app_resp_handler(context, app_get_resp_buf(context->port));
}

#if ((!CY_PD_SOURCE_ONLY) && (!CY_PD_SINK_ONLY))
#if CY_PD_REV3_ENABLE

void eval_fr_swap (cy_stc_pdstack_context_t context, cy_pdstack_app_resp_cbk_t app_resp_handler)
{
    /* Always accept, FRS message will only be received if we have previously initiated a FRS signal. */
    app_req_status_t result = CY_PDSTACK_REQ_ACCEPT;

    app_get_resp_buf(context->port)->reqStatus = result;
    app_resp_handler(context, app_get_resp_buf(context->port));

}

#endif /* CY_PD_REV3_ENABLE */
#endif /* ((!CY_PD_SOURCE_ONLY) && (!CY_PD_SINK_ONLY)) */

 /* End of File */
