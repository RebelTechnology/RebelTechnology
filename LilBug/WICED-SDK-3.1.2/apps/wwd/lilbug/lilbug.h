#ifndef INCLUDED_LILBUG_H
#define INCLUDED_LILBUG_H

#include "wwd_wifi.h"
#include "web_server.h"

#ifdef APPLIANCE_ENABLE_WPS
#include "wps_host.h"
#endif /* ifdef APPLIANCE_ENABLE_WPS */

#ifdef __cplusplus
extern "C" {
#endif

void debug_message(const char* string);

  void pnprintf(const char* fmt, ...);

/* #define Serial_printf(fmt, ...) pnprintf(128, fmt, __VA_ARGS__) */

#undef WPRINT_MACRO
#undef WPRINT_APP_INFO
#undef WPRINT_APP_ERROR
#define WPRINT_MACRO(args) do {pnprintf args;} while(0==1)

#define WPRINT_APP_INFO(args) WPRINT_MACRO(args)
#define WPRINT_APP_ERROR(args) do { WPRINT_MACRO(args); WICED_ASSERTION_FAIL_ACTION(); } while(0)
/* #define WPRINT_APP_INFO(fmt, ...) pnprintf(128, fmt, __VA_ARGS__) */
/* #define WPRINT_APP_ERROR(fmt, ...)  pnprintf(128, fmt, __VA_ARGS__) */

typedef struct
{
    enum
    {
        CONFIG_NONE = 0,
        CONFIG_WPS_PBC,
        CONFIG_WPS_PIN,
        CONFIG_SCANJOIN,
    } config_type;
    union
    {
        struct
        {
            char                pin[9]; /* extra byte for terminating null */
        } wps_pin;
        struct
        {
            wiced_scan_result_t scanresult;
            char                passphrase[WSEC_MAX_PSK_LEN];
            unsigned char       passphrase_len;
        } scanjoin;
    } vals;
} lilbug_config_t;

extern lilbug_config_t       lilbug_config;
extern const url_list_elem_t    config_STA_url_list[];
extern const url_list_elem_t    config_AP_url_list[];

void start_dns_server( uint32_t local_addr );
void quit_dns_server( void );
void start_dhcp_server( uint32_t local_addr );
void quit_dhcp_server( void );

#ifdef APPLIANCE_ENABLE_WPS
void do_wps( wiced_wps_mode_t wps_mode, char* pin );
#endif /* ifdef APPLIANCE_ENABLE_WPS */


#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_LILBUG_H */
