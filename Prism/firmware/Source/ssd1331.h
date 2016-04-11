
#define SSD1331_COLORORDER_RGB
// #define SSD1331_COLORORDER_BGR

#if defined SSD1331_COLORORDER_RGB && defined SSD1331_COLORORDER_BGR
  #error "RGB and BGR can not both be defined for SSD1331_COLORODER."
#endif
#define OLED_MW			(OLED_WIDTH-1)
#define OLED_MH			(OLED_HEIGHT-1)

// #define _DLY_LINE			400
// #define _DLY_FILL			800
// // list of the registers
// #define _CMD_DRAWLINE 		0x21
// #define _CMD_DRAWRECT 		0x22
// #define _CMD_DRAWCOPY 		0x23 //--
// #define _CMD_DIMWINDOW 		0x24 //--
// #define _CMD_CLRWINDOW 		0x25 //--
// #define _CMD_FILL 			0x26
// #define _CMD_PHASEPERIOD 	0x12 //--
// #define _CMD_SETCOLUMN 		0x15 
// #define _CMD_SETROW    		0x75 
// #define _CMD_CONTRASTA 		0x81 
// #define _CMD_CONTRASTB 		0x82 
// #define _CMD_CONTRASTC		0x83 
// #define _CMD_MASTERCURRENT 	0x87 
// #define _CMD_SETREMAP 		0xA0 
// #define _CMD_STARTLINE 		0xA1 
// #define _CMD_DISPLAYOFFSET 	0xA2 
// #define _CMD_NORMALDISPLAY 	0xA4
// #define _CMD_DISPLAYALLON  	0xA5
// #define _CMD_DISPLAYALLOFF 	0xA6
// #define _CMD_INVERTDISPLAY 	0xA7
// #define _CMD_SETMULTIPLEX  	0xA8
// #define _CMD_SETMASTER 		0xAD
// #define _CMD_DISPLAYOFF 	0xAE
// #define _CMD_DISPLAYON     	0xAF
// #define _CMD_POWERMODE 		0xB0
// #define _CMD_PRECHARGE 		0xB1
// #define _CMD_CLOCKDIV 		0xB3
// #define _CMD_GRAYSCALE 		0xB8
// #define _CMD_PRECHARGEA 	0x8A 
// #define _CMD_PRECHARGEB 	0x8B 
// #define _CMD_PRECHARGEC 	0x8C 
// #define _CMD_PRECHARGELEVEL     0xBB 
// #define _CMD_VCOMH 		0xBE
// #define	_CMD_VPACOLORLVL	0xBB
// #define	_CMD_VPBCOLORLVL	0xBC
// #define	_CMD_VPCCOLORLVL	0xBD
// #define _CMD_NOP		0xE3


void Graphics::zero() {
#ifdef SSD1331
  uint8_t cmd[] = {0x15, 0, OLED_MW, 0x75, 0, OLED_MH };
  writeCommands(cmd, 6);
#elif defined SEPS114A
  // uint8_t cmd[] = {0x38, 0, 0x39, 0 };
  uint8_t cmd[] = {0x34, 0x00, 0x35, 0x5F, 0x36, 0x00, 0x37, 0x5F, 0x08};
  writeCommands(cmd, sizeof(cmd));
#endif
}

void Graphics::chipInit() {
  static const uint8_t initSequence[] = {
    0xae, 0xa0, 0x76, 0xa1, 0x00, 0xa2, 0x00, 0xa4, 0xa8, 0x3f, 0xad, 0x8e,
    0xb0, 0x0b, 0xb1, 0x31, 0xb3, 0xf0, 0x8a, 0x64, 0x8b, 0x78, 0x8c, 0x64, 0xbb, 0x3a,
    0xbe, 0x3e, 0x87, 0x06, 0x81, 0x91, 0x82, 0x50, 0x83, 0x7d, // 0xaf display on
    0x2e // deactivate scrolling
  };
  //set display chip registers
  writeCommands(initSequence, sizeof(initSequence));
/* #elif defined SEPS114A */
/*   static const uint8_t initSequence[] = { */
/*     // 0x01, 0x00, 0x14, 0x01, /\* 1ms delay *\/ */
/*     // 0x14, 0x00, /\* 1ms delay *\/ */
/*     /\* display off 0x02, 0x00, *\/ */
/*     // 0x0f, 0x40,  */
/*     0x0f, 0x00, // external resistor, internal osc */
/*     // 0x1a, 0x03,  */
/*     0x1a, 0x0a, // frame rate 95Hz */
/*     0x30, 0x00, 0x31, 0x5f, 0x32, 0x00, 0x33, 0x5f, // set display x/y 1/2 */
/*     0xe0, 0x01, // RGB IF 16bit (doesn't matter for SPI) */
/*     0xe1, 0x00, // RGB polarity */
/*     0xe5, 0x80, // display mode control */
/*     0x0d, 0x00, // CPU_IF */
/*     0x1d, 0x00, // memory write read */
/*     0x09, 0x00, 0x13, 0x00,  */
/*     0x40, 0x6e, 0x41, 0x4f, 0x42, 0x77, // column current */
/*     0x48, 0x00, // row overlap */
/*     0x18, 0x01, // discharge time */
/*     0x16, 0x00, // peak pulse delay */
/*     0x3a, 0x02, 0x3b, 0x02, 0x3c, 0x02, // peak pulse width */
/*     0x3d, 0x14, 0x3e, 0x50, 0x3f, 0x19, // precharge current */
/*     0x17, 0x00, 0x49, 0x04, /\* clear screen *\/ */
/*     /\* zero 0x38, 0x00, 0x39, 0x00, *\/ */
/*     /\* display on 0x02, 0x01 *\/ */
/*   }; */
/*   static const uint8_t rst[] = {0x01, 0x00, 0x14, 0x01}; /\* reset, standby on *\/ */
/*   writeCommands(rst, sizeof(rst));  */
/*   delay(1);   */
/*   static const uint8_t stdby[] = {0x14, 0x00}; /\* standby off *\/ */
/*   writeCommands(stdby, sizeof(stdby)); */
/*   delay(1);   */
/*   writeCommands(initSequence, sizeof(initSequence));   */
/* #endif */
}
