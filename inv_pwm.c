#include <stdio.h>
#include "inv_common.h"
#include "inv_pwm.h"

#define INV_PWM_CH_NUM 3

typedef struct{
    float cur_cycle;				/* current duty */
    float cur_duty;					/* current duty */
    float cur_cnt;					/* current counter */
    float output;					/* output */
    INV_PWM_OUTPUT_STATUS_e status;	/* status */
    inv_pwm_config_t* config;		/* pointer to config */
} inv_pwm_output_t;

static inv_pwm_output_t inv_pwm_output[INV_PWM_CH_NUM];

static void inv_pwm_reset(int ch);
static void inv_pwm_inverse(int ch);

void inv_pwm_init(inv_pwm_config_t* p)
{
	inv_pwm_output[p->ch].status = INV_PWM_OUTPUT_STATUS_INIT;

	if(p == ((inv_pwm_config_t*)0)){
		/* null. nop */
		inv_pwm_output[p->ch].status = INV_PWM_OUTPUT_STATUS_ERROR_NULL;
	}
	else{
		if(p->ch >= INV_PWM_CH_NUM){
			/* invalid ch. nop */
			inv_pwm_output[p->ch].status = INV_PWM_OUTPUT_STATUS_ERROR_InvalidCh;
		}
		else{
			inv_pwm_output[p->ch].config = p;
			inv_pwm_reset(p->ch);
			inv_pwm_output[p->ch].status = INV_PWM_OUTPUT_STATUS_RUN;
		}
	}
}

float inv_pwm_main(
	int ch,
	float dt
)
{
	if(ch >= INV_PWM_CH_NUM){
		/* invalid ch. nop */
	}
	else{
		inv_pwm_output[ch].cur_cnt += dt;
		if(inv_pwm_output[ch].cur_cnt > inv_pwm_output[ch].cur_cycle){
			inv_pwm_reset(ch);
			inv_pwm_output[ch].cur_cnt += dt;
		}
		else{
			inv_pwm_inverse(ch);
		}
	}

#ifdef SCT_PWM_DEBUG
	printf("dt: %f\t", dt);
	printf("cur_cnt: %f\t", inv_pwm_output[ch].cur_cnt);
	printf("cur_duty: %f\t", inv_pwm_output[ch].cur_duty);
#endif

	return inv_pwm_output[ch].output;
}

INV_PWM_OUTPUT_STATUS_e inv_pwm_getStatus(int ch)
{
	INV_PWM_OUTPUT_STATUS_e ret = INV_PWM_OUTPUT_STATUS_ERROR_InvalidCh;
	if( ch >= INV_PWM_CH_NUM ){
		/* invalid ch. nop */
	}
	else{
		ret = inv_pwm_output[ch].status;
	}
	return ret;
}

static void inv_pwm_reset(int ch)
{
	inv_pwm_output[ch].cur_cycle = inv_pwm_output[ch].config->cycle + FLOATING_ERROR;
	inv_pwm_output[ch].cur_duty = inv_pwm_output[ch].config->duty + FLOATING_ERROR;
	inv_pwm_output[ch].cur_cnt = 0.0;
	inv_pwm_output[ch].output = INV_PWM_OUTPUT_HIGH;
}

static void inv_pwm_inverse(int ch)
{
	if(inv_pwm_output[ch].cur_cnt > inv_pwm_output[ch].cur_duty){
		inv_pwm_output[ch].output = INV_PWM_OUTPUT_LOW;
	}
	else{
		/*	nop	*/
	}
}
