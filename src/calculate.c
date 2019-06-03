#include "calculate.h"

osi joint[JOINT_N * 2] = {
        {0,0,2,0.6,10,0},
        {0,0,2,0.75,10,0},
        {0,0,2,0.9,10,0},
        {0,0,2,0.6,10,0},
        {0,0,2,0.75,10,0},
        {0,0,2,0.9,10,0}
    };

static int weight_init(){
    int i,j;
    for(i = 0;i < JOINT_N * 2;++i){
        for(j = 0;j < JOINT_N * 2;++j){
            if(j == i){
                weight[i][j] = 0;  //parallel coupling.
            }else if(j - i == 1 || i - j == 1){
                weight[i][j] = 10;  //up*down coupling.
            }else{
                weight[i][j] = 0;
            }
        }
    }
    return 0;
}

static int phase_bias_init(){
    int i,j;
    for(i = 0;i < JOINT_N * 2;++i){
        for(j = 0;j < JOINT_N * 2;++j){
            if(j - i == 1 && j != JOINT_N){
                phase_bias[i][j] = PI/4;    //down coupling phase bias.
            }else if(j - i == -1 && i != JOINT_N){
                phase_bias[i][j] = -PI/4;   //up coupling phase bias.
            }else{
                phase_bias[i][j] = 0;
            }
        }
    }
    return 0;
}

int calculate(int time,uint16_t CCR[JOINT_N]){
    weight_init();
    phase_bias_init();
    int i,j;
    float add = 0;
    float time_start,time_stop ;
    for(time_start = time * 0.02,time_stop = (time + 1) * 0.02;time_start < time_stop;time_start += DT){
        for(i = 0;i < JOINT_N * 2;++i){
            joint[i].amplitude += (joint[i].time_para * (joint[i].time_para / 4 * (joint[i].in_amp - joint[i].amplitude / DT))) * DT * DT;
       }
       for(i = 0;i < JOINT_N * 2;++i){
           for(j = 0;j < JOINT_N * 2;++j){
               if(j != i){
                   add += joint[i].amplitude * weight[i][j] * sin(joint[j].phase - joint[i].phase - phase_bias[i][j]);
               }
           }
           joint[i].phase += (2 * PI * joint[i].frequent + add) * DT;
       }
    }
    for(i = 0;i < JOINT_N;++i){
						joint[i].out = joint[i].amplitude * (1 + cos(joint[i].phase));
						joint[i].out *= 180 / PI;
						CCR[i] = (uint16_t)(joint[i].out / STENG_RES) + 500;
    }
    return 0;
}
