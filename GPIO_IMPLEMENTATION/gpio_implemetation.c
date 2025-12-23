#include "main.h"

/* USER CODE BEGIN PV */

#define UH 	GPIO_PIN_8
#define VH	GPIO_PIN_9
#define WH	GPIO_PIN_10

#define ENu GPIO_PIN_10
#define ENv GPIO_PIN_11
#define ENw	GPIO_PIN_12

uint8_t hall_A= 0b0;
uint8_t hall_B= 0b0;
uint8_t hall_C= 0b0;

uint8_t hall_state = 0b111;

uint32_t state_1 =0;
uint32_t state_2 =0;
uint32_t state_3 =0;
uint32_t state_4 =0;
uint32_t state_5 =0;
uint32_t state_6 =0;

uint8_t dir = 0;

const uint8_t fr_control_lookup[7][6] = {{0,0,0,0,0,0},// reset   // DIR 0
										{0,0,1,1,0,1},// reaching hal state 3
										{0,1,0,0,1,1},// reaching hal state 6
									    {0,1,0,1,1,0},// reaching hal state 2
									    {1,0,0,1,1,0},// reaching hal state 5
									    {0,0,1,0,1,1},// reaching hal state 1
									  	{1,0,0,1,0,1},// reaching hal state 4
		                            };

const uint8_t re_control_lookup[7][6] = {{0,0,0,0,0,0},//reset        //DIR 1 //ok
										{1,0,0,1,1,0},// reaching hal state 5
										{0,0,1,1,0,1},// reaching hal state 3
										{0,0,1,0,1,1},// reaching hal state 1
										{0,1,0,0,1,1},// reaching hal state 6
										{1,0,0,1,0,1},// reaching hal state 4
										{0,1,0,1,1,0},// reaching hal state 2
		                            };


uint8_t control_lookup_pos = 0b000000;
uint8_t delay = 0;

/* USER CODE END PV */

while (1)
{
	state_1 += (hall_state == 1) ? 1 : 0;
	state_2 += (hall_state == 2) ? 1 : 0;
	state_3 += (hall_state == 3) ? 1 : 0;
	state_4 += (hall_state == 4) ? 1 : 0;
	state_5 += (hall_state == 5) ? 1 : 0;
	state_6 += (hall_state == 6) ? 1 : 0;
	
	hall_A = (GPIOA ->IDR& GPIO_PIN_15)?1:0;
	hall_B = (GPIOB ->IDR& GPIO_PIN_3)?1:0;
	hall_C = (GPIOB ->IDR& GPIO_PIN_10)?1:0;
	
	hall_state = (hall_A<<2)|(hall_B<<1)|hall_C;
	
	if(dir == 0)
	{
		HAL_GPIO_WritePin(GPIOA, UH, fr_control_lookup[hall_state][0]);
		HAL_GPIO_WritePin(GPIOA, VH, fr_control_lookup[hall_state][1]);
		HAL_GPIO_WritePin(GPIOA, WH, fr_control_lookup[hall_state][2]);
	
		HAL_GPIO_WritePin(GPIOC, ENu, fr_control_lookup[hall_state][3]);
		HAL_GPIO_WritePin(GPIOC, ENv, fr_control_lookup[hall_state][4]);
		HAL_GPIO_WritePin(GPIOC, ENw, fr_control_lookup[hall_state][5]);
	}
	
	else
	{
		HAL_GPIO_WritePin(GPIOA, UH, re_control_lookup[hall_state][0]);
		HAL_GPIO_WritePin(GPIOA, VH, re_control_lookup[hall_state][1]);
		HAL_GPIO_WritePin(GPIOA, WH, re_control_lookup[hall_state][2]);
	
		HAL_GPIO_WritePin(GPIOC, ENu, re_control_lookup[hall_state][3]);
		HAL_GPIO_WritePin(GPIOC, ENv, re_control_lookup[hall_state][4]);
		HAL_GPIO_WritePin(GPIOC, ENw, re_control_lookup[hall_state][5]);
	}
}
	  
	  	






