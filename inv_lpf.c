#include "inv_lpf.h"

void inv_lpf_initialize(
	inv_lpf_config_t* p,
	float init,
	float gain
){
	p->buf = init;
	p->gain = gain;
}

float inv_lpf_output(
	inv_lpf_config_t* p,
	float in
){
	p->buf = ((1-p->gain)*in)+(p->gain*p->buf);
	return p->buf;
}
