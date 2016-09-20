#include "stm32f1xx_hal.h"
 
// Port Mapping
#define Pixi_PORT_1         0
#define Pixi_PORT_2         1
#define Pixi_PORT_3         2
#define Pixi_PORT_4         3
#define Pixi_PORT_5         4
#define Pixi_PORT_6         5
#define Pixi_PORT_7         6
#define Pixi_PORT_8         7
#define Pixi_PORT_9         8
#define Pixi_PORT_10        9
#define Pixi_PORT_11        10
#define Pixi_PORT_12        11
#define Pixi_PORT_13        12
#define Pixi_PORT_14        13
#define Pixi_PORT_15        14
#define Pixi_PORT_16        15
#define Pixi_PORT_17        16
#define Pixi_PORT_18        17
#define Pixi_PORT_19        18
#define Pixi_PORT_20        19
 
// SPI Base Addresses
#define ADDR_CFGbase        0x20
#define ADDR_ADCbase        0x40
#define ADDR_DACbase        0x60
 
#define SPI_Read                0
#define SPI_Write               1
 
// Configuration Values
#define CFG_ADCSamples_1                    (0<<5)
#define CFG_ADCSamples_2                    (1<<5)
#define CFG_ADCSamples_4                    (2<<5)
#define CFG_ADCSamples_8                    (3<<5)
#define CFG_ADCSamples_16                   (4<<5)
#define CFG_ADCSamples_32                   (5<<5)
#define CFG_ADCSamples_64                   (6<<5)
#define CFG_ADCSamples_128              (7<<5)
 
#define CFG_Range_ADC_None              (0<<8)
#define CFG_Range_ADC_0_P10             (1<<8)    //  0V to +10V
#define CFG_Range_ADC_M5_P5             (2<<8)    // -5V to +5V
#define CFG_Range_ADC_M10_0             (3<<8)    // -10 to 0V
#define CFG_Range_ADC_0_P2p5            (4<<8)    //   0 to +2.5 
 
#define CFG_Range_DAC_None              (0<<8)
#define CFG_Range_DAC_0_P10             (1<<8)    //  0V to +10V
#define CFG_Range_DAC_M5_P5             (2<<8)    // -5V to +5V
#define CFG_Range_DAC_M10_0             (3<<8)    // -10 to 0V
 
#define CFG_ADCref_INT                      (0<11)
#define CFG_ADCref_EXT                      (1<11)
 
#define CFG_GPI_notINV                      (0<11)
#define CFG_GPI_INV                             (1<11)
 
#define CFG_Mode_HighZ                      (0<<12)       // Mode 0  - High Impedance
#define CFG_Mode_GPI                            (1<<12)       // Mode 1  - Digital input with programmable threshold
#define CFG_Mode_BidirTrans             (2<<12)       // Mode 2  - Bidirectional level translator terminal
#define CFG_Mode_GPO                            (3<<12)       // Mode 3  - Register-driven digital output with DAC-controlled level
#define CFG_Mode_GPO_Unidir             (4<<12)       // Mode 4  - Unidirectional path output with DAC-controlled level
#define CFG_Mode_DAC                            (5<<12)       // Mode 5  - Analog output for DAC
#define CFG_Mode_DAC_ADCMon             (6<<12)       // Mode 6  - Analog output for DAC with ADC monitoring
#define CFG_Mode_ADC_SgEn_PosIn     (7<<12)       // Mode 7  - Positive analog input to single-ended ADC
#define CFG_Mode_ADC_Diff_PosIn     (8<<12)       // Mode 8  - Positive analog input to differential ADC
#define CFG_Mode_ADC_Diff_NegIn     (9<<12)       // Mode 9  - Negative analog input to differential ADC
#define CFG_Mode_DACOut_ADCNegIn    (10<<12)  // Mode 10 - Analog output for DAC and negative analog input to differential ADC
#define CFG_Mode_GPISwitch_Term     (11<<12)  // Mode 11 - Terminal to GPI-controlled analog switch
#define CFG_Mode_RegSwitch_Term     (12<<12)  // Mode 12 - Terminal to register-controlled analog switch
 
// Pin Control
#define pbarCS(state)       HAL_GPIO_WritePin(MAX_CS_GPIO_Port,  MAX_CS_Pin,  (GPIO_PinState)state)
 
// Prototypes
void MAX11300_init(SPI_HandleTypeDef *spiconfig);
void MAX11300_ConfigPort(unsigned char port, unsigned short config);
