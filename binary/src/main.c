#include <ch32v00x.h>

void Delay_Init(void);
void Delay_Ms(uint32_t n);

int main(void) {
	#ifdef NVIC_PriorityGroup_2
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	#else
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	#endif
	SystemCoreClockUpdate();
	Delay_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	uint8_t a = 1;
	uint8_t b = 0;
	while (1) {
		GPIO_WriteBit(GPIOC, GPIO_Pin_0, a);
		GPIO_WriteBit(GPIOC, GPIO_Pin_1, b);
		GPIO_WriteBit(GPIOC, GPIO_Pin_2, a^b);
		Delay_Ms(1000);
	}
}
