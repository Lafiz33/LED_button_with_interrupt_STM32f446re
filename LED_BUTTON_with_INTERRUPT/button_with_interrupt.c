#include "stm32f446XX.h"



void turnLedOn();
void turnLedOff();
void blink();
void delay(int delay);





int main(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	
	//LED init
	GPIOA->MODER &= ~(3<<10);
	GPIOA->MODER |= (1<<10);
	GPIOA->OTYPER &=~(1<<5);
	GPIOA->OSPEEDR &=~ (3<<10);
	GPIOA->OSPEEDR |= (3<<10);
	GPIOA->PUPDR &=~ (3<<10);

	//PA4 for button
	GPIOA->MODER &= ~(3<<8);
	GPIOA->OTYPER &= ~(1<<4);
	GPIOA->OSPEEDR &=~ (3<<8);
	GPIOA->OSPEEDR |= (3<<8);
	GPIOA->PUPDR &=~ (3<<8);
	
	//select trigger for EXTI4
	EXTI->RTSR |= (1<<4);
	
	//enable interrupt over EXTI4 in mask register
	EXTI->IMR |= (1<<4);
	
	//enable interrupt for NVIC IRQ
	NVIC->ISER[0] |= (1<<10); //EXTI4 is interrupt no. 10  
	
	
	
	//loop
while(1){

}

}

void EXTI4_IRQHandler(void){
	
	//clear EXTI4 pending bit
	if((EXTI->PR & 0x10)!=0){
		EXTI->PR |= (1<<10);
	}
	blink(1);
}

void blink(int a){
	turnLedOn();
	delay(a);
	turnLedOff();
}
void turnLedOn(){
		GPIOA->BSRR |= (1<<5);
}
void turnLedOff(){
	  GPIOA->BSRR |= (1<<(5+16));
}
void delay(int delay){
	for(int i=0; i<delay*1000000; i++);
}

