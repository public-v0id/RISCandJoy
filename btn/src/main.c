#include <ch32v00x.h>

int main(void) {
	#ifdef NVIC_PriorityGroup_2
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        #else
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
        #endif
	SystemCoreClockUpdate();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitTypeDef GPIO_InitStructIn = {0};
	GPIO_InitStructIn.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructIn.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructIn.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructIn);
	int curMode = 0;
	int itersHeld = 0;
	int itersUnheld = 0;
	while(1) {
		int val = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
		if (val) {
			itersHeld++;			
		}
		else if (itersHeld > 0) {
			itersUnheld++;
		}
		if (itersHeld+itersUnheld >= 50 && itersUnheld > itersHeld) {
			itersHeld = 0;
			itersUnheld = 0;
			continue;
		}
		if (itersHeld+itersUnheld >= 50) {
			curMode = !curMode;
			GPIO_WriteBit(GPIOC, GPIO_Pin_0, curMode);
			itersHeld = 0;
			itersUnheld = 0;
		}
	}
}
