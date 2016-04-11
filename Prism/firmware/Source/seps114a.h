#define SEPS114A_SOFT_RESET 0x01
#define SEPS114A_DISPLAY_ON_OFF 0x02
#define SEPS114A_ANALOG_CONTROL 0x0F    //
#define SEPS114A_STANDBY_ON_OFF 0x14
#define SEPS114A_OSC_ADJUST 0x1A
#define SEPS114A_ROW_SCAN_DIRECTION 0x09
#define SEPS114A_DISPLAY_X1 0x30
#define SEPS114A_DISPLAY_X2 0x31
#define SEPS114A_DISPLAY_Y1 0x32
#define SEPS114A_DISPLAY_Y2 0x33
#define SEPS114A_DISPLAYSTART_X 0x38
#define SEPS114A_DISPLAYSTART_Y 0x39
#define SEPS114A_CPU_IF 0x0D
#define SEPS114A_MEM_X1 0x34
#define SEPS114A_MEM_X2 0x35
#define SEPS114A_MEM_Y1 0x36
#define SEPS114A_MEM_Y2 0x37
#define SEPS114A_MEMORY_WRITE_READ 0x1D
#define SEPS114A_DDRAM_DATA_ACCESS_PORT 0x08
#define SEPS114A_DISCHARGE_TIME 0x18
#define SEPS114A_PEAK_PULSE_DELAY 0x16
#define SEPS114A_PEAK_PULSE_WIDTH_R 0x3A
#define SEPS114A_PEAK_PULSE_WIDTH_G 0x3B
#define SEPS114A_PEAK_PULSE_WIDTH_B 0x3C
#define SEPS114A_PRECHARGE_CURRENT_R 0x3D
#define SEPS114A_PRECHARGE_CURRENT_G 0x3E
#define SEPS114A_PRECHARGE_CURRENT_B 0x3F
#define SEPS114A_COLUMN_CURRENT_R 0x40
#define SEPS114A_COLUMN_CURRENT_G 0x41
#define SEPS114A_COLUMN_CURRENT_B 0x42
#define SEPS114A_ROW_OVERLAP 0x48
#define SEPS114A_SCAN_OFF_LEVEL 0x49
#define SEPS114A_ROW_SCAN_ON_OFF 0x17
#define SEPS114A_ROW_SCAN_MODE 0x13
#define SEPS114A_SCREEN_SAVER_CONTROL 0xD0
#define SEPS114A_SS_SLEEP_TIMER 0xD1
#define SEPS114A_SCREEN_SAVER_MODE 0xD2
#define SEPS114A_SS_UPDATE_TIMER 0xD3
#define SEPS114A_RGB_IF 0xE0
#define SEPS114A_RGB_POL 0xE1
#define SEPS114A_DISPLAY_MODE_CONTROL 0xE5

extern SPI_HandleTypeDef hspi1;

void spiwrite(const uint8_t* data, size_t size){
  while(hspi1.State != HAL_SPI_STATE_READY);
  clearPin(OLED_SCK_GPIO_Port, OLED_SCK_Pin);
  clearCS();
  HAL_StatusTypeDef ret = HAL_SPI_Transmit(&hspi1, (uint8_t*)data, size, 100);
  assert_param(ret == HAL_OK);
  setCS();
}

void spiwrite(uint8_t c){
  spiwrite(&c, 1);
}

//Send command to OLED C display

void writeCommand(unsigned char reg_index, unsigned char reg_value){
  /* uint8_t cmd[] = {reg_index, reg_value}; */
  clearDC();
  spiwrite(reg_index);
  setDC();
  spiwrite(reg_value);
/* //Select index addr */
/*     OLED_CS = 0; */
/*     OLED_DC = 0; */
/*     SPI3_Write(reg_index); */
/*     OLED_CS = 1; */
/* //Write data to reg */
/*     OLED_CS = 0; */
/*     OLED_DC = 1; */
/*     SPI3_Write(reg_value); */
/*     OLED_CS = 1; */
}

//Send data to OLED C display
void seps114a_data(unsigned char data_value){
  setDC();
  spiwrite(data_value);
    /* OLED_CS = 0; */
    /* OLED_DC = 1; */
    /* SPI3_Write(data_value); */
    /* OLED_CS = 1; */
}

// Init sequence for 96x96 OLED color module
void Graphics::chipInit(){
  /* OLED_RST=0; */
  /* Delay_ms(10); */
  /* OLED_RST=1; */
  /* Delay_ms(10); */
  /* commonInit(); */
  /*  Soft reset */
  writeCommand(SEPS114A_SOFT_RESET,0x00);      
  /* Standby ON/OFF*/
  writeCommand(SEPS114A_STANDBY_ON_OFF,0x01);          // Standby on
  delay(5);                                           // Wait for 5ms (1ms Delay Minimum)
  writeCommand(SEPS114A_STANDBY_ON_OFF,0x00);          // Standby off
  delay(5);                                           // 1ms Delay Minimum (1ms Delay Minimum)
  /* Display OFF */
  writeCommand(SEPS114A_DISPLAY_ON_OFF,0x00);
  /* Set Oscillator operation */
  writeCommand(SEPS114A_ANALOG_CONTROL,0x00);          // using external resistor and internal OSC
  /* Set frame rate */
  writeCommand(SEPS114A_OSC_ADJUST,0x03);              // frame rate : 95Hz
  /* Set active display area of panel */
  writeCommand(SEPS114A_DISPLAY_X1,0x00);
  writeCommand(SEPS114A_DISPLAY_X2,0x5F);
  writeCommand(SEPS114A_DISPLAY_Y1,0x00);
  writeCommand(SEPS114A_DISPLAY_Y2,0x5F);
  /* Select the RGB data format and set the initial state of RGB interface port */
  writeCommand(SEPS114A_RGB_IF,0x00);                 // RGB 8bit interface
  /* Set RGB polarity */
  writeCommand(SEPS114A_RGB_POL,0x00);
  /* Set display mode control */
  writeCommand(SEPS114A_DISPLAY_MODE_CONTROL,0x80);   // SWAP:BGR, Reduce current : Normal, DC[1:0] : Normal
  /* Set MCU Interface */
  writeCommand(SEPS114A_CPU_IF,0x00);                 // MPU External interface mode, 8bits
  /* Set Memory Read/Write mode */
  writeCommand(SEPS114A_MEMORY_WRITE_READ,0x00);
  /* Set row scan direction */
  writeCommand(SEPS114A_ROW_SCAN_DIRECTION,0x00);     // Column : 0 --> Max, Row : 0 --> Max
  /* Set row scan mode */
  writeCommand(SEPS114A_ROW_SCAN_MODE,0x00);          // Alternate scan mode
  /* Set column current */
  writeCommand(SEPS114A_COLUMN_CURRENT_R,0x6E);
  writeCommand(SEPS114A_COLUMN_CURRENT_G,0x4F);
  writeCommand(SEPS114A_COLUMN_CURRENT_B,0x77);
  /* Set row overlap */
  writeCommand(SEPS114A_ROW_OVERLAP,0x00);            // Band gap only
  /* Set discharge time */
  writeCommand(SEPS114A_DISCHARGE_TIME,0x01);         // Discharge time : normal discharge
  /* Set peak pulse delay */
  writeCommand(SEPS114A_PEAK_PULSE_DELAY,0x00);
  /* Set peak pulse width */
  writeCommand(SEPS114A_PEAK_PULSE_WIDTH_R,0x02);
  writeCommand(SEPS114A_PEAK_PULSE_WIDTH_G,0x02);
  writeCommand(SEPS114A_PEAK_PULSE_WIDTH_B,0x02);
  /* Set precharge current */
  writeCommand(SEPS114A_PRECHARGE_CURRENT_R,0x14);
  writeCommand(SEPS114A_PRECHARGE_CURRENT_G,0x50);
  writeCommand(SEPS114A_PRECHARGE_CURRENT_B,0x19);
  /* Set row scan on/off  */
  writeCommand(SEPS114A_ROW_SCAN_ON_OFF,0x00);        // Normal row scan
  /* Set scan off level */
  writeCommand(SEPS114A_SCAN_OFF_LEVEL,0x04);         // VCC_C*0.75
  /* Set memory access point */
  writeCommand(SEPS114A_DISPLAYSTART_X,0x00);
  writeCommand(SEPS114A_DISPLAYSTART_Y,0x00);
  /* Display ON */
  writeCommand(SEPS114A_DISPLAY_ON_OFF,0x01);
}

//Sekvence before writing data to memory
void DDRAM_access(){
    /* OLED_CS=0; */
    /* OLED_DC=0; */
  clearDC();
  spiwrite(0x08);
    /* OLED_CS=1; */
}

//Set memory area(address) to write a display data
void seps114a_MemorySize(char X1, char X2, char Y1, char Y2){
  writeCommand(SEPS114A_MEM_X1,X1);
  writeCommand(SEPS114A_MEM_X2,X2);
  writeCommand(SEPS114A_MEM_Y1,Y1);
  writeCommand(SEPS114A_MEM_Y2,Y2);
}

//Select color
void seps114a_Color(char colorMSB, char colorLSB ){
  seps114a_data(colorMSB);
  seps114a_data(colorLSB);
}

void seps114a_bg(){
  unsigned j;
    
  writeCommand(0x1D,0x02);                //Set Memory Read/Write mode
    
  seps114a_MemorySize(0x00,0x5F,0x00,0x5F);
  DDRAM_access();
  for(j=0;j<9216;j++){
    seps114a_Color(0xFF,0xFF);
  }
  //delay_ms(1000);
    
  seps114a_MemorySize(0x05,0x5A,0x05,0x5A);
  DDRAM_access();
  for(j=0;j<8100;j++){
    seps114a_Color(0x0C,0xC0);
  }
  //delay_ms(1000);
     
  seps114a_MemorySize(0x0A,0x55,0x0A,0x55);
  DDRAM_access();
  for(j=0;j<7225;j++){
    seps114a_Color(0xFF,0x00);
  }
  //delay_ms(1000);
                       
  seps114a_MemorySize(0x0F,0x50,0x0F,0x50);
  DDRAM_access();
  for(j=0;j<6400;j++){
    seps114a_Color(0x80,0x00);
  }
  // delay_ms(1000);
                       
  seps114a_MemorySize(0x14,0x4B,0x14,0x4B);
  DDRAM_access();
  for(j=0;j<5625;j++){
    seps114a_Color(0xF8,0x00);
  }
  //delay_ms(1000);
                       
  seps114a_MemorySize(0x19,0x46,0x19,0x46);
  DDRAM_access();
  for(j=0;j<4900;j++){
    seps114a_Color(0x00,0xFF);
  }
  // delay_ms(1000);
  seps114a_MemorySize(0x1E,0x41,0x1E,0x41);
  DDRAM_access();
  for(j=0;j<4225;j++){
    seps114a_Color(0x80,0xFF);
  }
  /* delay_ms(5000); */
}

void Graphics::zero() {
  // uint8_t cmd[] = {0x38, 0, 0x39, 0 };
  /* uint8_t cmd[] = {0x34, 0x00, 0x35, 0x5F, 0x36, 0x00, 0x37, 0x5F, 0x08}; */
  /* writeCommands(cmd, sizeof(cmd)); */

  seps114a_MemorySize(0x00,0x5F,0x00,0x5F);
  DDRAM_access();
}

/* void main(){ */
/*       int i; */
/*       InitMCU(); */
/*       UART1_Init(56000); */
/*       seps114a_Init(); */
/*       seps114a_Beckground(); */

/*      while(1){ */
/*              for(i=0;i<8;i++){ */
/*                              writeCommand(SEPS114A_SCREEN_SAVER_MODE,i); */
/*                              writeCommand(SEPS114A_SCREEN_SAVER_CONTROL,0x88); */
/*                              delay_ms(5000); */
/*                              writeCommand(SEPS114A_SCREEN_SAVER_CONTROL,0x00); */
/*                              } */
/*       delay_ms(5000);   */
/*       } */
/* } */
