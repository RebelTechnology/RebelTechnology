#include "stm32f10x.h"
#include "device.h"
#include "serial.h"
#include "device.h"

int USART_getc(USART_TypeDef* USARTx);
void USART_puts(USART_TypeDef* USARTx, volatile const char *s);
void USART_putc(USART_TypeDef* USARTx, char c);
USART_TypeDef* usart = 0;

void serialputchar(uint8_t c){
  if(usart != 0)
    USART_putc(usart, c);
}  

void serial_setup(uint32_t baudrate) {
  usart = USART1;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 

  /* Enable PORT B clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef gpioConfig;
  GPIO_StructInit(&gpioConfig);
  // was: PA9
  // PB6 = USART1.TX => Alternative Function Output
  gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
  gpioConfig.GPIO_Pin = GPIO_Pin_6;
  gpioConfig.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpioConfig);
 
  // was: PA10
  // PB7 = USART1.RX => Input
  gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  gpioConfig.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOB, &gpioConfig);

  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

  USART_InitTypeDef usartConfig;
  USART_StructInit(&usartConfig);
  usartConfig.USART_BaudRate = baudrate; 
  usartConfig.USART_WordLength = USART_WordLength_8b; 
  usartConfig.USART_StopBits = USART_StopBits_1; 
  usartConfig.USART_Parity = USART_Parity_No;
  usartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  usartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &usartConfig);

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SERIAL_PORT_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SERIAL_PORT_SUBPRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  USART_Cmd(USART1, ENABLE);
}

int USART_getc(USART_TypeDef* USARTx){
  while((USARTx->SR & USART_SR_RXNE) == 0);
  return (unsigned char)USART_ReceiveData(USARTx);
}

void USART_puts(USART_TypeDef* USARTx, volatile const char *s){
  while(*s){
    // wait until TX data register is empty
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    /* while( !(USARTx->SR & 0x00000040) ); */
    USART_SendData(USARTx, *s);
    *s++;
  }
}

void USART_putc(USART_TypeDef* USARTx, char c){
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART_SendData(USARTx, c);
}

void printString(const char* s){
  if(usart)
    USART_puts(usart, s);
}

void printByte(char c){
  if(usart)
    USART_putc(usart, c);
}

void printIntegerInBase(unsigned long n, unsigned long base){ 
  unsigned char buf[8 * sizeof(long)]; // Assumes 8-bit chars. 
  unsigned long i = 0;
  if (n == 0) {
    printByte('0');
    return;
  } 
  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }
  for (; i > 0; i--)
    printByte(buf[i - 1] < 10 ?
	      '0' + buf[i - 1] :
	      'A' + buf[i - 1] - 10);
}

void printInteger(long n)
{
  if(n < 0){
    printByte('-');
    n = -n;
  }
  printIntegerInBase(n, 10);
}

void printHex(unsigned long n)
{
  printIntegerInBase(n, 16);
}

void printOctal(unsigned long n)
{
  printIntegerInBase(n, 8);
}

void printBinary(unsigned long n){
  printIntegerInBase(n, 2);
}

void printDouble(double val, uint8_t precision){
  if(val < 0.0){
    printByte('-');
    val = -val;
  }
  printInteger((long)val);
  if(precision > 0) {
    printByte('.');
    unsigned long frac;
    unsigned long mult = 1;
    uint8_t padding = precision -1;
    while(precision--)
      mult *=10;
    if(val >= 0)
      frac = (val - (int)val) * mult;
    else
      frac = ((int)val- val) * mult;
    unsigned long frac1 = frac;
    while(frac1 /= 10 )
      padding--;
    while(padding--)
      printByte('0');
    printInteger(frac);
  }
}

void serial_write(uint8_t* data, uint16_t size){
  if(usart){
    for(int i=0; i<size; ++i)
      USART_putc(usart, data[i]);
  }
}
