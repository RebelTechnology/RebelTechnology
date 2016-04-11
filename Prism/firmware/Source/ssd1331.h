
#define SSD1331_COLORORDER_RGB
// #define SSD1331_COLORORDER_BGR

#if defined SSD1331_COLORORDER_RGB && defined SSD1331_COLORORDER_BGR
  #error "RGB and BGR can not both be defined for SSD1331_COLORODER."
#endif
#define OLED_MW			(OLED_WIDTH-1)
#define OLED_MH			(OLED_HEIGHT-1)

// list of the registers
#define SSD1331_DRAWLINE 		0x21
#define SSD1331_DRAWRECT 		0x22
#define SSD1331_DRAWCOPY 		0x23 //--
#define SSD1331_DIMWINDOW 		0x24 //--
#define SSD1331_CLRWINDOW 		0x25 //--
#define SSD1331_FILL 			0x26
#define SSD1331_PHASEPERIOD 	0x12 //--
#define SSD1331_SETCOLUMN 		0x15 
#define SSD1331_SETROW    		0x75 
#define SSD1331_CONTRASTA 		0x81 
#define SSD1331_CONTRASTB 		0x82 
#define SSD1331_CONTRASTC		0x83 
#define SSD1331_MASTERCURRENT 	0x87 
#define SSD1331_SETREMAP 		0xA0 
#define SSD1331_STARTLINE 		0xA1 
#define SSD1331_DISPLAYOFFSET 	0xA2 
#define SSD1331_NORMALDISPLAY 	0xA4
#define SSD1331_DISPLAYALLON  	0xA5
#define SSD1331_DISPLAYALLOFF 	0xA6
#define SSD1331_INVERTDISPLAY 	0xA7
#define SSD1331_SETMULTIPLEX  	0xA8
#define SSD1331_SETMASTER 		0xAD
#define SSD1331_DISPLAYOFF 	0xAE
#define SSD1331_DISPLAYON     	0xAF
#define SSD1331_POWERMODE 		0xB0
#define SSD1331_PRECHARGE 		0xB1
#define SSD1331_CLOCKDIV 		0xB3
#define SSD1331_GRAYSCALE 		0xB8
#define SSD1331_PRECHARGEA 	0x8A 
#define SSD1331_PRECHARGEB 	0x8B 
#define SSD1331_PRECHARGEC 	0x8C 
#define SSD1331_PRECHARGELEVEL     0xBB 
#define SSD1331_VCOMH 		0xBE
#define	SSD1331_VPACOLORLVL	0xBB
#define	SSD1331_VPBCOLORLVL	0xBC
#define	SSD1331_VPCCOLORLVL	0xBD
#define SSD1331_NOP		0xE3

void Graphics::zero() {
  uint8_t cmd[] = {0x15, 0, OLED_MW, 0x75, 0, OLED_MH };
  writeCommands(cmd, 6);
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
}

void Graphics::off() {
  writeCommand(SSD1331_DISPLAYOFF);
}

void Graphics::on() {
  writeCommand(SSD1331_DISPLAYON);
}
