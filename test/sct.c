#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../inv_common.h"
#include "../inv_sin.h"
#include "../inv_pwm.h"
#include "../inv_lpf.h"
#include "../inv_rungeKuttaFlt.h"
#include "../inv_trans_ab.h"
#include "../inv_trans_dq.h"
#include "../inv_pid.h"

//#define NO_ZTRANS

#define SIM_CYCLE_TIME (1.0*MICROSEC)
#define TEST_CYCLE (1000)
#define TEST_TIME (8000*MICROSEC)
#define PWM_CYCLE (20*MICROSEC)
#define PWM_DUTY_DEF (10*MICROSEC)
#define SIN_CYCLE (4000*MICROSEC)
#define ZTRANS_CYCLE (40*MICROSEC)
#define FLT_CYCLE (40*MICROSEC)

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

static inv_lpf_config_t work_lpf[1] = 
{
	/* gain, buf */
	{ 0.99, 0.0}
};

static inv_rkflt_config_t work_fkflt[1] =
{
	/* dt[μs], h[μs], buf */
	{FLT_CYCLE, FLT_CYCLE, 0.0f}
};

static inv_pid_config_t work_pid[1] = 
{
	/* Propostional, Integral, Defferential, buf Integral, buf Defferential */
	{ 0.8, 0.25, 0.5, 0.0, 0.0}
};

static void test_ztrans(void);
static void test_pwm(void);
static void test_pwmsin(void);
static void test_rkflt(void);
static void test_transab(void);
static void test_transdq(void);
static void test_pid(void);

static float noise(
	float time, 
	float power, 
	float f
);

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
	else if(strcmp(argv[1], "rkflt") == 0){
		test_rkflt();
	}
	else if(strcmp(argv[1], "transab") == 0){
		test_transab();
	}
	else if(strcmp(argv[1], "transdq") == 0){
		test_transdq();
	}
	else if(strcmp(argv[1], "pid") == 0){
		test_pid();
	}
	else{
		printf("sct: invalid parameter");
	}
}

static void test_pid(void)
{
	float out = 0.0;
	float ref = 1.0;
	float fb = 1.0;
	float time = 0.0;
	float error = 0.0;

	printf("pid\n");
	printf("cycle: %f\n", SIM_CYCLE_TIME);
	printf("kp: %f\n", work_pid[0].kp);
	printf("ki: %f\n", work_pid[0].ki);
	printf("kd: %f\n", work_pid[0].kd);
	printf("init: %f\n", work_pid[0].buf_d);
	printf("system: lpf\n");
	printf("start reference: %f\n", ref);
	printf("feedback gain: %f\n", fb);
	printf("time\tref\terror\toutput\n");

	while(1){
		error = ref - out;
		out = inv_pid_output(&work_pid[0], error);
		out = inv_lpf_output(&work_lpf[0], out);
		printf("%f\t%f\t%f\t%f\n", time, ref, error, out);

		time += SIM_CYCLE_TIME;
		if(time > (TEST_TIME/4.0)){
			break;
		}
	}
}

static void test_transdq(void)
{
	inv_dq_t ret;
	float a = 0.0;
	float b = 0.0;
	float rad = 0.0;
	float th = _PI/4.0;
	float time = 0.0;
	float r = 1.0;
	float f = (1.0/SIN_CYCLE);

	printf("trans dq\n");
	printf("dq coordinate rotational speed: 2pift\n");
	printf("(a,b): rcos(2pift+th), rsin(2pift+th)\n");
	printf("r: %f\n", r);
	printf("f: %f\n", f);
	printf("th: %f\n", th);
	printf("a\tb\trad\tth\td\tq\n");

	while(1){
		rad = 2*_PI*f*time;
		a =  r*cos(rad+th);
		b =  r*sin(rad+th);
		ret = inv_trans_dq(a, b, rad);
		printf("%f\t%f\t%f\t%f\t%f\t%f\n", a, b, rad, th, ret.d, ret.q);

		time += SIM_CYCLE_TIME;
		if(time > (TEST_TIME/4.0)){
			break;
		}
	}
}

static void test_transab(void)
{
	inv_ab_t ret;
	float u = 0.0;
	float v = 0.0;
	float w = 0.0;

	printf("trans ab\n");

	printf("u\tv\tw\ta\tb\n");

	ret = inv_trans_ab(u, v, w);
	printf("%f\t%f\t%f\t%f\t%f\n", u, v, w, ret.a, ret.b);

	u = 1.0; v = 1.0; w = 1.0;
	ret = inv_trans_ab(u, v, w);
	printf("%f\t%f\t%f\t%f\t%f\n", u, v, w, ret.a, ret.b);

	u = 1.0; v = 2.0; w = 1.0;
	ret = inv_trans_ab(u, v, w);
	printf("%f\t%f\t%f\t%f\t%f\n", u, v, w, ret.a, ret.b);

	u = 1.0; v = 1.0; w = 2.0;
	ret = inv_trans_ab(u, v, w);
	printf("%f\t%f\t%f\t%f\t%f\n", u, v, w, ret.a, ret.b);
}

static void test_rkflt(void)
{
	float time = 0.0;
	float time_flt = 0.0;
	float result = 0.0;
	float f = (1.0/SIN_CYCLE);
	float nf = (f*3.0);
	float np = 0.1;

	printf("runge kutta filter initialize\n");
	printf("initialize done\n");

	printf("init: %f\n", work_fkflt[0].buf);
	printf("h: %f[us]\n", work_fkflt[0].h/MICROSEC);
	printf("dt: %f[us]\n", work_fkflt[0].dt/MICROSEC);
	printf("input sin: %f[Hz]\n", f);
	printf("noise freq: %f[Hz]\n", nf);
	printf("noise power: %f\n", np);
	printf("runge kutta filter results\n");
	printf("time\tresult\n");

//	result = inv_rkflt_output(&work_fkflt[0], 1.0);
//	printf("%f\t%f\n", time, result);

	while(1){
		result = sin(2*_PI*f*time);
		result += noise(time, np, nf);

		if(time_flt > FLT_CYCLE){
			time_flt = 0.0f;
			result = inv_rkflt_output(&work_fkflt[0], result);
			printf("%f\t%f\n", time, result);
		}

		time_flt += SIM_CYCLE_TIME;
		time += SIM_CYCLE_TIME;
		if(time > TEST_TIME){
			break;
		}
	}
}

static void test_pwmsin(void)
{
	printf("initialize\n");
	inv_sin_ztarans_init(&work_ztrans);
	inv_pwm_init(&work_pwm[0]);

	printf("initialize done\n");
	printf("sim cycle: %f[s]\n", SIM_CYCLE_TIME);
	printf("sin: %f[Hz]\n", (1/work_ztrans.cycle));
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
		result = inv_lpf_output(&work_lpf[0], result);

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

static float noise(
	float time, 
	float power, 
	float f
){
	return (sin(2*_PI*f*time)*power);
}