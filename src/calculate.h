#include"stm32f10x.h"
#include<math.h>
#define JOINT_N 3
#define DT 0.0001
#define PI 3.14159265358979323846 
#define STENG_RES 0.09  //舵机分辨力

typedef struct oscillator{
    float phase;
    float amplitude;
    float frequent;
    float in_amp;
    float time_para;
    float out;
} osi;

static float weight[JOINT_N * 2][JOINT_N * 2];
static float phase_bias[JOINT_N * 2][JOINT_N * 2];

int calculate(int,uint16_t*);
