#include <stdio.h>
#include "inv_rungeKuttaFlt.h"

/* 4 degree Runge–Kutta method */

void inv_rkflt_initialize( /* no null check. be carefull before calling */
	inv_rkflt_config_t* p,
	float init,
	float h,
	float dt
){
	p->buf = init;
	p->h = h;
	p->dt = dt;
}

float inv_rkflt_output( /* no null check. be carefull before calling */
	inv_rkflt_config_t* p,
	float in
){
	float k1, k2, k3, k4;

	k1 = p->h*((in - p->buf)/p->dt);
	k2 = p->h*(in - (p->buf + (k1/2))/p->dt);
	k3 = p->h*(in - (p->buf + (k2/2))/p->dt);
	k4 = p->h*(in - (p->buf + k3)/p->dt);
	p->buf = p->buf + ((k1 + (2*k2) + (2*k3) + k4)/6); 
/*
	printf("k1: %f\n", k1);
	printf("k2: %f\n", k2);
	printf("k3: %f\n", k3);
	printf("k4: %f\n", k4);
	printf("out: %f\n", p->buf);
*/
	return p->buf;
}
