#include "HAL_Triggers.h"
#include "HAL_Encoders.h"
#include "HAL_CV_IO.h"
#include "stm32f7xx_hal.h"
#include "usb_device.h"
#include "usb_host.h"
#include "HAL_OLED.h"


void setup(void);
void run(void);

extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;

uint16_t SDRAM_In_Buffer[100], SDRAM_Out_Buffer[100]; 
uint32_t* SDRAM_Address;
uint8_t	SDRAM_Status, x;
unsigned char pixelbuffer[1024];

void setup(void){
	// Product Specific Initialisation
  Triggers_Config();
  Encoders_Config();
  CV_IO_Config();
  OLED_Config(&hspi2, pixelbuffer);
	
  CV_Out_A(&hdac, 0);
  CV_Out_B(&hdac, 0);
}

void run(void){
  
	uint8_t ucPixelTest = 0, Test = 0;;
	
	memset(pixelbuffer, 0x00, sizeof pixelbuffer);

	OLED_setPixel(127, 63);
	
	// Main Loop
  while (1)
  {
		// USB Host Processes
    MX_USB_HOST_Process();
		
		OLED_togglePixel(127, 63);
		
		OLED_Refresh();
		
		SDRAM_Address = (uint32_t*)0xD0000000L;
		
		for (x=0; x<100; x++)
		{
			SDRAM_In_Buffer[x] = rand();
		}
		
		SDRAM_Status = HAL_SDRAM_Write_16b(&hsdram1, SDRAM_Address, SDRAM_In_Buffer, sizeof SDRAM_In_Buffer);
		SDRAM_Status = HAL_SDRAM_Read_16b(&hsdram1, SDRAM_Address, SDRAM_Out_Buffer, sizeof SDRAM_Out_Buffer);
		
		Trigger_OUT_A(LOW);
	  Trigger_OUT_B(LOW);
  }
}

#ifdef USE_FULL_ASSERT
/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
#ifdef DEBUG
  __asm__("BKPT");
#else
  NVIC_SystemReset();
#endif
  /* USER CODE END 6 */

}

#endif
