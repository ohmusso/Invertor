#include "inv_pid.h"

void inv_pid_initialize( /* no null check. be carefull before calling */
	inv_pid_config_t* p,
	float kp,
	float ki,
	float kd,
	float init
){
	p->kp = kp;
	p->ki = ki;
	p->kd = kd;
	p->buf_i = init;
	p->buf_d = init;
}

float inv_pid_output(
	inv_pid_config_t* p,
	float in
){
	float ret;

	/* p */
	ret = in * p->kp;
	/* i */
	p->buf_i += (in * p->ki);
	ret += p->buf_i;
	/* d */
#ifdef INV_PID_D_ON
	float out_d;
	ret += (in - p->buf_d) * p->kd;
	p->buf_d = in;
#endif

	return ret;
}
