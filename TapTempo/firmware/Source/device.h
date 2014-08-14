#include <inttypes.h>

#define FIRMWARE_VERSION             "001"
#define HARDWARE_VERSION             "TapTempo Rev02"

#define MODE_SWITCH_PORT             GPIOA
#define MODE_SWITCH_PIN_A            GPIO_Pin_9
#define MODE_SWITCH_PIN_B            GPIO_Pin_10
#define MODE_SWITCH_CLOCK            RCC_AHB1Periph_GPIOA

/* Illuminated pushbutton */
/* PA7 */
#define PUSHBUTTON_PORT                GPIOA
#define PUSHBUTTON_CLOCK               RCC_AHB1Periph_GPIOA
#define PUSHBUTTON_PORT_SOURCE         EXTI_PortSourceGPIOA
#define PUSHBUTTON_PIN                 GPIO_Pin_7
#define PUSHBUTTON_PIN_SOURCE          EXTI_PinSource7
#define PUSHBUTTON_PIN_LINE            EXTI_Line7
#define PUSHBUTTON_IRQ                 EXTI2_IRQn
#define PUSHBUTTON_HANDLER             EXTI2_IRQHandler

/* LED */
/* PA6 and PA8  */
#define LED_PORT                     GPIOA
#define LED_GREEN                    GPIO_Pin_8
#define LED_RED                      GPIO_Pin_6
#define LED_CLOCK                    RCC_AHB1Periph_GPIOA

#ifdef  USE_FULL_ASSERT
#ifdef __cplusplus
 extern "C" {
#endif
   void assert_failed(uint8_t* file, uint32_t line);
#ifdef __cplusplus
}
#endif
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
#endif
