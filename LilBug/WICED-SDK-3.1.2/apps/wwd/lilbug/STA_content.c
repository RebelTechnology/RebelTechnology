/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/**
 * @file
 * This provides the content (web pages) which will be served when the
 * Appliance App has been configured and connected to an external Access Point.
 *
 * It does not use a filesystem, all pages are generated by handler functions.
 * These functions simply copy data into the outgoing packet buffer.
 *
 */

#include "web_server.h"
#include "brcmlogos.h"
#include "wwd_wifi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wwd_assert.h"
#include "lilbug.h"
#include "internal/wwd_sdpcm.h"
#include "wwd_wlioctl.h"

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/
#define SSID_FIELD_NAME            "ssid"
#define SECURITY_FIELD_NAME        "sec"
#define CHANNEL_FIELD_NAME         "chan"
#define BSSID_FIELD_NAME           "bssid"
#define PASSPHRASE_FIELD_NAME      "pwd"
#define PIN_FIELD_NAME             "pin"

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/
typedef struct
{
    uint8_t scan_done;
    host_semaphore_type_t result_avail_sema;
    wiced_scan_result_t* result_buff;
} scan_cb_t;

/******************************************************
 *               Static Function Declarations
 ******************************************************/
static int  process_top           ( void* socket, char * params, int params_len );

/******************************************************
 *               Variable Definitions
 ******************************************************/

/**
 * URL Handler List
 */
const url_list_elem_t config_STA_url_list[] = {
                                     { "/",             "text/html",                process_top },
                                     { "/favicon.ico",  "image/vnd.microsoft.icon", process_favicon },
                                     { "/brcmlogo.jpg", "image/jpeg",               process_brcmlogo },
                                     /* Add more pages here */
                                     { NULL, NULL, NULL }
                                   };


/**
 * HTML data for main sensor web page
 */
static const char top_web_page_top[] =
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN " "http://www.w3.org/TR/html4/strict.dtd\">\n"
    "<html>\n"
    "  <head>\n"
    "    <title>WICED Appliance</title>\n"
    "  </head>\n"
    "  <body style=\"font-family:verdana;\" >\n"
    "    <h2 align=\"center\"><img src=\"brcmlogo.jpg\"/> <span style=\"color:#ff0000\">Broadcom</span> WICED Appliance</h2><hr>\n"
    "<p>Button presses are sent to " PLATFORM " UART.</p>"
    "<form name=\"input\" action=\"/\" method=\"get\"> <table> <tr>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-01\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-02\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-03\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-04\" /></td>\n"
    "</tr>"
    "<td><input type=\"submit\" name=btname value=\"Button-05\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-06\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-07\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-08\" /></td>\n"
    "</tr>"
    "<td><input type=\"submit\" name=btname value=\"Button-09\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-10\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-11\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-12\" /></td>\n"
    "</tr>"
    "<td><input type=\"submit\" name=btname value=\"Button-13\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-14\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-15\" /></td>\n"
    "<td><input type=\"submit\" name=btname value=\"Button-16\" /></td>\n"
    "</tr>"
    "</form>"
    "  </body>\n"
    "</html>\n";


/******************************************************
 *               Function Definitions
 ******************************************************/

/**
 * URL handler for serving web buttons / UART demo
 *
 * Checks if the GET parameters contain a button name, and writes any names found to the UART
 *
 * @param  socket  : a handle for the TCP socket over which the data will be sent
 * @param  params     : a byte array containing any parameters included in the URL
 * @param  params_len : size of the params byte array in bytes
 */
static int process_top( void* socket, char * params, int params_len )
{
    char * found_loc = NULL;
    char  end_found = 0;
    /* Process the GET parameter list to determine if buttons have been pressed */

    /* Cycle through parameter list string until end or newline */
    while ( end_found == 0 )
    {
        /* Check if parameter is "led" */
        if ( 0 == strncmp( params, "btname", 6 ) )
        {
            found_loc = &params[7];
        }

        /* Scan ahead to the next parameter or the end of the parameter list */
        while ( ( *params != '&' ) && ( *params != '\n' ) && ( params_len > 0 ) )
        {
            params++;
            params_len--;
        }

        if  ( *params != '&' )
        {
            end_found = 1;
        }


        if ( found_loc != NULL )
        {
            *params = '\x00';
            WPRINT_APP_INFO( ( "\nDetected button press: %s\n\n", found_loc ) );
        }


        if ( end_found == 0 )
        {
            /* Skip over the "&" which joins parameters if found */
            params++;
        }
    }


    send_web_data( socket, (unsigned char*) top_web_page_top, sizeof( top_web_page_top ) - 1 ); /* minus one to avoid copying terminating null */

    return 0;
}






