#include <stdio.h>
#include <math.h>
#include <time.h>
#include "../inv_sin.h"

//#define NO_ZTRANS

static inv_sin_ztrans_t work = 
{
    4000.0*MICROSEC,				/* T[s] */
    40.0*MICROSEC,					/* Δt[s] */
	{ 0, 0, 0},						/* ztrans buffer. fixed-point number Q14. */
    0,								/* ztrans parameter. fixed-point number Q14. */
    0,								/* ztrans parameter. fixed-point number Q14. */
    0								/* ztrans parameter. fixed-point number Q14. */
}; 

#define TEST_CYCLE 1000

int main(){

	printf("initialize\n");
	inv_sin_ztarans_init(&work);
	printf("cycle: %f\n", work.cycle);
	printf("dt: %f\n", work.dt);
	printf("buf[0]: %d\n", work.buf[0]);
	printf("buf[1]: %d\n", work.buf[1]);
	printf("buf[2]: %d\n", work.buf[2]);
	printf("a1: %x\n", work.a1);
	printf("a2: %x\n", work.a2);
	printf("b1: %x\n", work.b1);

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
		inv_sin_ztrans(&work);
		ret = ((float)work.buf[0])/TRANS_Q14;
#endif /* NO_ZTRANS */
		printf("%d\t%f\n", cnt, ret);

		cnt++;
		if(cnt > TEST_CYCLE){
			break;
		}
	}
	end = clock();
//	printf("calculation time: %lf[s]", ((double)(end - begin) / CLOCKS_PER_SEC));
}
