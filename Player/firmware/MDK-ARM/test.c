#include "HAL_Triggers.h"
#include "HAL_Encoders.h"
#include "HAL_CV_IO.h"
#include "stm32f7xx_hal.h"
#include "usb_device.h"
#include "usb_host.h"

void setup(void);
void run(void);

extern DAC_HandleTypeDef hdac;
extern SDRAM_HandleTypeDef hsdram1;

uint16_t SDRAM_In_Buffer[100], SDRAM_Out_Buffer[100]; 
uint32_t* SDRAM_Address;
uint8_t	SDRAM_Status, x;

void setup(void){
// Product Specific Initialisation
  Triggers_Config();
  Encoders_Config();
  CV_IO_Config();
	
  CV_Out_A(&hdac, 2048);
  CV_Out_B(&hdac, 1024);
}

void run(void){
  // Main Loop
  while (1)
  {
		// USB Host Processes
    MX_USB_HOST_Process();

		
		SDRAM_Address = (uint32_t*)1;
		
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
