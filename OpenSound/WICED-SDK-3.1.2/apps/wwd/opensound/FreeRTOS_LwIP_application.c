#include "wwd_wifi.h"
#include "wwd_management.h"
#include "wwd_network.h"
#include "network/wwd_buffer_interface.h"
#include "platform/wwd_platform_interface.h"
#include "lwip/opt.h"
#include "lwip/mem.h"
#include <string.h>
#include "lwip/init.h"
#include "lwip/tcpip.h"
#include "netif/etharp.h"
#include "lwip/sockets.h"  /* equivalent of <sys/socket.h> */
#include "lwip/inet.h"
#include "lwip/dhcp.h"
#include "wwd_wifi.h"
#include "wwd_management.h"
#include "network/wwd_buffer_interface.h"
#include "network/wwd_network_interface.h"
#include "platform/wwd_platform_interface.h"
#include "wwd_debug.h"
#include "wwd_assert.h"
#include <math.h>
#include "application.h"
#include "uart.h"

#include "web_server.h"
/* #include "socket_server.h" */
#include "websocket_server.h"

/******************************************************
 *                      Macros
 ******************************************************/
/** @cond */
#define MAKE_IPV4_ADDRESS(a, b, c, d)          ((((uint32_t) (a)) << 24) | (((uint32_t) (b)) << 16) | (((uint32_t) (c)) << 8) | ((uint32_t) (d)))
/** @endcond */

/******************************************************
 *                    Constants
 ******************************************************/

#define COUNTRY                 WICED_COUNTRY_UNITED_KINGDOM
#define AP_IP_ADDR              MAKE_IPV4_ADDRESS( 192, 168,   1,  1 )
#define AP_NETMASK              MAKE_IPV4_ADDRESS( 255, 255, 255,   0 )
#define JOIN_TIMEOUT            (10000)   /** timeout for joining the wireless network in milliseconds  = 10 seconds */

#define SAMPLES_PER_SEND        (26)
#define TIME_MS_BETWEEN_SAMPLES (1000)
#define DESTINATION_UDP_PORT    (50007)
#define AP_SSID_START           "OpenSound_"
#define AP_PASS                 "12345678" /* must be 8 chars */
/* #define AP_SEC                  WICED_SECURITY_WPA2_AES_PSK  /\* WICED_SECURITY_OPEN *\/ */
#define AP_SEC                  WICED_SECURITY_OPEN
#define AP_CHANNEL              (1)
#define APP_THREAD_STACKSIZE    (2048)
#define DHCP_THREAD_STACKSIZE   (800)
#define WEB_SERVER_STACK_SIZE   (1024)
#define OPENSOUND_SERVER_STACK_SIZE   (1024)
#define UDP_SERVER_STACK_SIZE   (2048)

static struct netif wiced_if;
static xTaskHandle startup_thread_handle;

/* Sensor Configuration settings variables */
application_config_t       application_config   = { .config_type = CONFIG_NONE };

static void startup_thread  ( void *arg );
static void tcpip_init_done ( void * arg );
static void run_ap_webserver( void );
static void run_sta_web_server( void );

/**
 * Main opensound app thread
 *
 * Obtains network information and credentials via AP mode web server
 *
 */
#include "app.h"
static void app_main( void )
{
  setup();

  static xTaskHandle poll_opensound_thread_handle;
  xTaskCreate(pollOpenSoundTask, (signed char*)"Poll OPENSOUND",
  	      OPENSOUND_SERVER_STACK_SIZE/sizeof(portSTACK_TYPE), NULL,
  	      DEFAULT_THREAD_PRIO, &poll_opensound_thread_handle);

  static xTaskHandle udp_server_thread_handle;
  xTaskCreate(udp_server_task, (signed char*)"udp",
  	      UDP_SERVER_STACK_SIZE/sizeof(portSTACK_TYPE), NULL,
  	      DEFAULT_THREAD_PRIO, &udp_server_thread_handle);

  /* Run the web server to obtain the configuration */
  run_ap_webserver( );
  run_sta_web_server( );
}

static void run_sta_web_server( void ) {
    struct ip_addr ipaddr, netmask, gw;
    wwd_result_t result;

    /* Start WICED (starts the 802.11 device) */
    WPRINT_APP_INFO(("Starting Wiced v" WICED_VERSION "\n"));
    while ( WWD_SUCCESS != ( result = wwd_management_init( COUNTRY, NULL ) ) )
    {
        WPRINT_APP_INFO(("Error %d while starting WICED!\n", result));
    }

#ifdef APPLIANCE_ENABLE_WPS
    if ( application_config.config_type == CONFIG_WPS_PBC )
    {
        do_wps( WICED_WPS_PBC_MODE, "" );
    }
    else if ( application_config.config_type == CONFIG_WPS_PIN )
    {
        do_wps( WICED_WPS_PIN_MODE, application_config.vals.wps_pin.pin );
    }
    else
#endif /* ifdef APPLIANCE_ENABLE_WPS */
    {
        if ( application_config.config_type == CONFIG_SCANJOIN )
        {
            /* Join a wireless network */
            while ( WWD_SUCCESS != wwd_wifi_join_specific( &application_config.vals.scanjoin.scanresult, (uint8_t*) application_config.vals.scanjoin.passphrase, application_config.vals.scanjoin.passphrase_len, NULL, WWD_STA_INTERFACE ) )
            {
                WPRINT_APP_INFO(("Failed to join .. retrying\n"));
            }
            WPRINT_APP_INFO( ( "Successfully joined Network\n" ) );
        }
    }

    /* Setup network interface */
    ip_addr_set_zero(&gw);
    ip_addr_set_zero(&ipaddr);
    ip_addr_set_zero(&netmask);

    if ( NULL == netif_add( &wiced_if, &ipaddr, &netmask, &gw, (void*) WWD_STA_INTERFACE, ethernetif_init, ethernet_input ) )
    {
        WPRINT_APP_ERROR( ( "Failed to start network interface\n" ) );
        return;
    }

    netif_set_default( &wiced_if );
    netif_set_up( &wiced_if );

    /* Do DHCP negotiation */
    WPRINT_APP_INFO(("Obtaining IP address via DHCP\n"));
    struct dhcp netif_dhcp;
    dhcp_set_struct( &wiced_if, &netif_dhcp );
    dhcp_start( &wiced_if );
    while ( netif_dhcp.state != DHCP_BOUND )
    {
        /* wait */
        sys_msleep( 10 );
    }

    WPRINT_APP_INFO( ( "Network ready IP: %u.%u.%u.%u\n", (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 24 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 16 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 8 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 0 ) & 0xff ) ) );

    start_websocket_server_thread( wiced_if.ip_addr.addr );
    /* start_socket_server_thread( wiced_if.ip_addr.addr ); */

    run_webserver( wiced_if.ip_addr.addr, config_STA_url_list );

    WPRINT_APP_INFO( ( "Shutting down WICED\n" ) );

    quit_websocket_server();
    /* quit_socket_server(); */

    /* Shut everything down again */
    dhcp_stop( &wiced_if );
    netif_set_down( &wiced_if );
    netif_remove( &wiced_if );
    wwd_wifi_leave( WWD_STA_INTERFACE );
    if ( WWD_SUCCESS != wwd_management_wifi_off( ) )
    {
        WPRINT_APP_ERROR(("WICED de-initialization failed\n"));
    }
}

/**
 * Starts an access point, web server and DHCP server
 *
 * This function initialises the 802.11 device, creates a 802.11 access point, then starts a web server
 * and a DHCP server to allow browser clients to connect.
 */
static void run_ap_webserver( void )
{
    wiced_ssid_t ap_ssid;
    wiced_mac_t  my_mac;
    struct ip_addr ap_ipaddr;
    struct ip_addr ap_netmask;
    wwd_result_t result;

    /* Initialise Wiced */
    WPRINT_APP_INFO(("Starting Wiced v" WICED_VERSION "\n"));
    while ( WWD_SUCCESS != ( result = wwd_management_init( COUNTRY, NULL ) ) )
    {
        WPRINT_APP_INFO(("Error %d while starting WICED!\n", result));
    }

    /* Create the SSID */
    wwd_wifi_get_mac_address( &my_mac, WWD_STA_INTERFACE );
    sprintf( (char*) ap_ssid.value, AP_SSID_START "%02X%02X%02X%02X%02X%02X", my_mac.octet[0], my_mac.octet[1], my_mac.octet[2], my_mac.octet[3], my_mac.octet[4], my_mac.octet[5] );
    ap_ssid.length = strlen( (char*)ap_ssid.value );

    WPRINT_APP_INFO(("Starting Access Point: SSID: %s\n", (char*)ap_ssid.value ));

    /* Start the access point */
    wwd_wifi_start_ap( &ap_ssid, AP_SEC, (uint8_t*) AP_PASS, sizeof( AP_PASS ) - 1, AP_CHANNEL );

    /* Setup the network interface */
    ap_ipaddr.addr = htonl( AP_IP_ADDR );
    ap_netmask.addr = htonl( AP_NETMASK );

    if ( NULL == netif_add( &wiced_if, &ap_ipaddr, &ap_netmask, &ap_ipaddr, (void*) WWD_AP_INTERFACE, ethernetif_init, ethernet_input ) )
    {
        WPRINT_APP_ERROR( ( "Failed to start network interface\n" ) );
        return;
    }
    netif_set_default( &wiced_if );
    netif_set_up( &wiced_if );

    WPRINT_APP_INFO( ( "Network ready IP: %u.%u.%u.%u\n", (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 24 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 16 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 8 ) & 0xff ),
                                                      (unsigned char) ( ( htonl( wiced_if.ip_addr.addr ) >> 0 ) & 0xff ) ) );

    /* Create DNS and DHCP servers */
    start_dns_server( ap_ipaddr.addr );
    start_dhcp_server( ap_ipaddr.addr );

    start_websocket_server_thread( ap_ipaddr.addr );
    /* start_socket_server_thread( ap_ipaddr.addr ); */

    run_webserver( ap_ipaddr.addr, config_AP_url_list );

    quit_dhcp_server( );
    quit_dns_server( );

    quit_websocket_server();
    /* quit_socket_server(); */

    /* Shut everything down */
    netif_set_down( &wiced_if );
    netif_remove( &wiced_if );

    if ( WWD_SUCCESS != wwd_wifi_stop_ap( ) )
    {
        WPRINT_APP_ERROR(("Failed to stop WICED access point\n"));
    }
/*
    if ( WICED_SUCCESS != wwd_management_wifi_off( ) )
    {
        WINFO_APP_ERROR(("WICED de-initialization failed\n"));
    }
*/
}

/**
 *  Main function - creates an initial thread then starts FreeRTOS
 *  Called from the crt0 _start function
 *
 */
int main( void )
{

  uart_init();

    /* Create an initial thread */
    xTaskCreate(startup_thread, (signed char*)"app_thread", APP_THREAD_STACKSIZE/sizeof( portSTACK_TYPE ), NULL, DEFAULT_THREAD_PRIO, &startup_thread_handle);

    /* Start the FreeRTOS scheduler - this call should never return */
    vTaskStartScheduler( );

    for(;;);

    /* Should never get here, unless there is an error in vTaskStartScheduler */
    WPRINT_APP_ERROR(("Main() function returned - error" ));
    return 0;
}

/**
 *  Initial thread function - Starts LwIP and calls app_main
 *
 *  This function starts up LwIP using the tcpip_init function, then waits on a semaphore
 *  until LwIP indicates that it has started by calling the callback @ref tcpip_init_done.
 *  Once that has been done, the @ref app_main function of the app is called.
 *
 * @param arg : Unused - required for conformance to thread function prototype
 */

static void startup_thread( void *arg )
{
    UNUSED_PARAMETER( arg);
    xSemaphoreHandle lwip_done_sema;

    WPRINT_APP_INFO( ( "\nPlatform " PLATFORM " initialised\n" ) );
    WPRINT_APP_INFO( ( "Started FreeRTOS " FreeRTOS_VERSION "\n" ) );
    WPRINT_APP_INFO( ( "Starting LwIP " LwIP_VERSION "\n" ) );

    /* Create a semaphore to signal when LwIP has finished initialising */
    lwip_done_sema = xSemaphoreCreateCounting( 1, 0 );
    if ( lwip_done_sema == NULL )
    {
        /* could not create semaphore */
        WPRINT_APP_ERROR(("Could not create LwIP init semaphore"));
        return;
    }

    /* Initialise LwIP, providing the callback function and callback semaphore */
    tcpip_init( tcpip_init_done, (void*) &lwip_done_sema );
    xSemaphoreTake( lwip_done_sema, portMAX_DELAY );
    vQueueDelete( lwip_done_sema );

    /* Run the main application function */
    app_main( );

    /* Clean up this startup thread */
    vTaskDelete( startup_thread_handle );
}

/**
 *  LwIP init complete callback
 *
 *  This function is called by LwIP when initialisation has finished.
 *  A semaphore is posted to allow the startup thread to resume, and to run the app_main function
 *
 * @param arg : the handle for the semaphore to post (cast to a void pointer)
 */

static void tcpip_init_done( void * arg )
{
    xSemaphoreHandle * LwIP_done_sema = (xSemaphoreHandle *) arg;
    xSemaphoreGive( *LwIP_done_sema );
}



