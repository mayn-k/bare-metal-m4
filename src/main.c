#include <stdint.h>

#define LED_PIN 5

#define RCC_BASE (0x40021000U)
#define RCC_AHB2ENR_OFFSET (0x4CU)
#define RCC_AHB2ENR (*((volatile uint32_t*)(RCC_BASE + RCC_AHB2ENR_OFFSET)))
#define RCC_AHB2ENR_GPIOAEN (0x1U)

#define GPIOA_BASE (0x48000000U)
#define GPIOA_MODER_OFFSET (0x00U)
#define GPIOA_MODER (*((volatile uint32_t*)(GPIOA_BASE + GPIOA_MODER_OFFSET)))
#define GPIO_MODER_MODER5 (0x400U)
#define GPIOA_ODR_OFFSET (0x14U)
#define GPIOA_ODR (*((volatile uint32_t*)(GPIOA_BASE + GPIOA_ODR_OFFSET)))

void delay(uint32_t iterations) {
    for (uint32_t i = 0; i < iterations; ++i);
}

int main(void) {
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    volatile uint32_t dummy;
    dummy = RCC_AHB2ENR;
    dummy = RCC_AHB2ENR;

    GPIOA_MODER |= GPIO_MODER_MODER5;

    while (1) {
        GPIOA_ODR ^= (1 << LED_PIN);
        delay(1000000);
    }

    return 0;
}
