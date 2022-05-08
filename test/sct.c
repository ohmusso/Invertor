#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../inv_common.h"
#include "../inv_sin.h"
#include "../inv_pwm.h"

//#define NO_ZTRANS

#define SIM_CYCLE_TIME (1.0*MICROSEC)
#define TEST_CYCLE (1000)
#define TEST_TIME (8000*MICROSEC)
#define PWM_CYCLE (20*MICROSEC)
#define PWM_DUTY_DEF (10*MICROSEC)
#define SIN_CYCLE (4000*MICROSEC)
#define ZTRANS_CYCLE (40*MICROSEC)

static inv_sin_ztrans_t work_ztrans = 
{
    SIN_CYCLE,						/* T[s] */
    ZTRANS_CYCLE,					/* Δt[s] */
	{ 0, 0, 0},						/* ztrans buffer. fixed-point number Q14. */
    0,								/* ztrans parameter. fixed-point number Q14. */
    0,								/* ztrans parameter. fixed-point number Q14. */
    0								/* ztrans parameter. fixed-point number Q14. */
};

static inv_pwm_config_t work_pwm[3] = 
{
	/* pwm ch, pwm cycle[μs], pwm duty[μs] */
	{ 0, PWM_CYCLE, PWM_DUTY_DEF},
	{ 1, PWM_CYCLE, PWM_DUTY_DEF},
	{ 2, PWM_CYCLE, PWM_DUTY_DEF}
};

static void test_ztrans(void);
static void test_pwm(void);
static void test_pwmsin(void);

int main(int argc, char** argv)
{
	if(strcmp(argv[1], "ztrans") == 0){
		test_ztrans();
	}
	else if(strcmp(argv[1], "pwm") == 0){
		test_pwm();
	}
	else if(strcmp(argv[1], "pwmsin") == 0){
		test_pwmsin();
	}
	else{
		printf("sct: invalid parameter");
	}
}
static void test_pwmsin(void)
{
	printf("initialize\n");
	inv_sin_ztarans_init(&work_ztrans);
	inv_pwm_init(&work_pwm[0]);

	printf("pwm sin results\n");
	printf("time\tresult\n");
	float time = 0.0;
	float time_ztrans = 0.0;
	float result = 0.0;
	float sin = 0.0;
	while(1){
		if(time_ztrans > ZTRANS_CYCLE){
			time_ztrans = 0.0f;
			inv_sin_ztrans(&work_ztrans);
			sin = fabs(((float)work_ztrans.buf[0]/TRANS_Q14));
//			printf("%f\t%f\n", time, sin);
		}

		work_pwm[0].duty = (sin*PWM_CYCLE);
		result = inv_pwm_main(0, SIM_CYCLE_TIME);

		printf("%f\t%f\n", time, result);

		time += SIM_CYCLE_TIME;
		time_ztrans += SIM_CYCLE_TIME;
		if(time > TEST_TIME){
			break;
		}
	}
}

static void test_pwm(void)
{
	printf("initialize\n");
	inv_pwm_init(&work_pwm[0]);

	printf("pwm results\n");
	printf("cnt\tresult\n");
	int cnt = 0;
	float result = 0.0;
	while(1){
		result = inv_pwm_main(0, SIM_CYCLE_TIME);
		printf("%d\t%f\n", cnt, result);

		cnt++;
		if(cnt > TEST_CYCLE){
			break;
		}
	}
}

static void test_ztrans(void)
{
	printf("initialize\n");
	inv_sin_ztarans_init(&work_ztrans);
	printf("cycle: %f\n", work_ztrans.cycle);
	printf("dt: %f\n", work_ztrans.dt);
	printf("buf[0]: %d\n", work_ztrans.buf[0]);
	printf("buf[1]: %d\n", work_ztrans.buf[1]);
	printf("buf[2]: %d\n", work_ztrans.buf[2]);
	printf("a1: %x\n", work_ztrans.a1);
	printf("a2: %x\n", work_ztrans.a2);
	printf("b1: %x\n", work_ztrans.b1);

	printf("ztarns results\n");
	printf("cnt\tresult\n");
	int cnt = 0;
	clock_t begin, end;
	float ret = 0.0;
	begin = clock();
	while(1){
#ifdef NO_ZTRANS
		ret = sin(2*_PI/work.cycle*work.dt*cnt);
#else
		inv_sin_ztrans(&work_ztrans);
		ret = ((float)work_ztrans.buf[0])/TRANS_Q14;
#endif /* NO_ZTRANS */
		printf("%d\t%f\n", cnt, ret);

		cnt++;
		if(cnt > TEST_CYCLE){
			break;
		}
	}
	end = clock();
	printf("calculation time(but include printf runnning time): %lf[s]", ((double)(end - begin) / CLOCKS_PER_SEC));
}
