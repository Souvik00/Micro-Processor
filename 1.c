
// Using Timer (TIM2)
#define RCC_BASE        0x40021000
#define GPIOC_BASE      0x40011000
#define TIM2_BASE				0x40000000

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR     (*(volatile unsigned int *)(RCC_BASE + 0x1C))

#define GPIOC_CRH       (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define TIM2_CR1				(*(volatile unsigned int *)(TIM2_BASE + 0x00))
#define TIM2_PSC        (*(volatile unsigned int *)(TIM2_BASE + 0x28))
#define TIM2_ARR        (*(volatile unsigned int *)(TIM2_BASE + 0x2C))
#define TIM2_SR         (*(volatile unsigned int *)(TIM2_BASE + 0x10))

void delay(volatile unsigned int ms){

    TIM2_PSC = 8000 - 1;  // 8 mhz/8kz for 1 tik in 1ms
  TIM2_ARR = ms - 1;  //set the limit

  // Clear update flag
  TIM2_SR &= ~(0x01);

  // Enable the counter
  TIM2_CR1 |= (1 << 0);

  // Wait for the update event
  while (!(TIM2_SR & 0x01));

  // Disable the counter
  TIM2_CR1 &= ~((1 << 0));
}


int main(void) {

    RCC_APB2ENR |= (1 << 4);
    RCC_APB1ENR |= (1 << 0);

    GPIOC_CRH |= (3 << 20);  //set to 50Mhsz
    GPIOC_CRH &= ~(3 << 22); //set to on-off mode
      while (1)
      {
          GPIOC_ODR ^= (1 << 13);

        delay(1000);
    }
}
