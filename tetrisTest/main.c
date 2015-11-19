#include "main.h"

#include "usart.h"
#include "utils/buffer8.h"

static uint16_t __timer = 0;

void Delay(uint16_t n)
{
    __timer = n;
    while (__timer > 0);
}

int main()
{

  RCC->AHBENR |= 0xFFFFFFFF;
  RCC->APB2ENR |= 0xFFFFFFFF;
  RCC->APB1ENR |= 0xFFFFFFFF;

  initIGVCUsart();

  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);

  STM_EVAL_LEDOff(LED6);
  STM_EVAL_LEDOff(LED7);

  SysTick_Config(SystemCoreClock / 1000);

  //initS29gl();

  Delay(10);

  //enterQueryMode();

  Delay(10);

  //sweepAddresses(0, 0x60);

  printf("Done\r\n");

  while (1)
  {
     Delay(5);
  }

  while (1)
  {
    if (usartHaveBytes())
    {
       runCommsFSM(usartGet());
    }
  } 

  while(1)
  {
    uint32_t bytes;
    uint8_t data[32];
    if ((bytes = usartHaveBytes()) > 5)
    {
      usartRead(data, bytes);
      usartWrite(data, bytes);
    }
  }

  while(1)
  {
    usartPrint("STM32\r\n");
    //usartPut('1');
    Delay(100);
  }
}

/*void USART1_IRQHandler()
{
  uint16_t data;
  data = USART_ReceiveData(USART1);

  USART_SendData(USART1, data + 1);
}*/

void Timer_Decrement()
{
    if (__timer > 0)
        __timer--;
} 

void assert_param(int x)
{

}
