#include <inttypes.h>

#define FIRMWARE_VERSION             "004"
#define HARDWARE_VERSION             "TapTempo Rev03"

#if 0
/*
  left toggle PB8 / PB9
  right toggle PA9 / PA10
  trigger input PB0
  trigger output PB1
  DAC1 PA4
  DAC2 PA5
 */

#define TRIGGER_OUTPUT_PORT          GPIOB
#define TRIGGER_OUTPUT_PIN           GPIO_Pin_0

#define TOGGLE_L_PORT                GPIOB
#define TOGGLE_L_PIN_A               GPIO_Pin_8
#define TOGGLE_L_PIN_B               GPIO_Pin_9
#define TOGGLE_L_CLOCK               RCC_AHB1Periph_GPIOB

#define TOGGLE_R_PORT                GPIOA
#define TOGGLE_R_PIN_A               GPIO_Pin_9
#define TOGGLE_R_PIN_B               GPIO_Pin_10
#define TOGGLE_R_CLOCK               RCC_AHB1Periph_GPIOA

#define TRIGGER_INPUT_PORT           GPIOB
#define TRIGGER_INPUT_PIN            GPIO_Pin_1
#define TRIGGER_INPUT_CLOCK          RCC_APB2Periph_AFIO
#define TRIGGER_INPUT_PORT_SOURCE    GPIO_PortSourceGPIOB
#define TRIGGER_INPUT_PIN_SOURCE     GPIO_PinSource1
#define TRIGGER_INPUT_PIN_LINE       EXTI_Line1
#define TRIGGER_INPUT_IRQ            EXTI1_IRQn
#define TRIGGER_INPUT_HANDLER        EXTI1_IRQHandler

/* Illuminated pushbutton */
#define PUSHBUTTON_PORT              GPIOA
#define PUSHBUTTON_CLOCK             RCC_APB2Periph_AFIO
#define PUSHBUTTON_PORT_SOURCE       GPIO_PortSourceGPIOA
#define PUSHBUTTON_PIN               GPIO_Pin_2
#define PUSHBUTTON_PIN_SOURCE        GPIO_PinSource2
#define PUSHBUTTON_PIN_LINE          EXTI_Line2
#define PUSHBUTTON_IRQ               EXTI2_IRQn
#define PUSHBUTTON_HANDLER           EXTI2_IRQHandler

/* LED */
#define LED_PORT                     GPIOA
#define LED_GREEN                    GPIO_Pin_8
#define LED_RED                      GPIO_Pin_6
#define LED_CLOCK                    RCC_AHB1Periph_GPIOA

#endif // 0

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
