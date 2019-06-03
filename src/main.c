
#include "stm32f10x.h"
#include "calculate.h"
#include "bsp_GeneralTim.h"  



int main(void){
	int time = 0;
	uint16_t CCR[JOINT_N],CCR1,CCR2,CCR3;
	calculate(time,CCR);
	GENERAL_TIM_Init();
	do{
		if(TIM_GetFlagStatus(GENERAL_TIM, TIM_FLAG_Update) == SET){
			CCR1 = CCR[0];
			CCR2 = CCR[1];
			CCR3 = CCR[2];
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_SetCompare1(GENERAL_TIM,CCR1);
			TIM_SetCompare2(GENERAL_TIM,CCR2);
			TIM_SetCompare3(GENERAL_TIM,CCR3);
			calculate(time,CCR);
		}

	}while(1);
}
