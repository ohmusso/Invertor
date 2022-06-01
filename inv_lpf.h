#ifndef INVLPF_H
#define INVLPF_H

typedef struct{
    float gain;						/* gain[%] */
    float buf;						/* buf */
} inv_lpf_config_t;

void inv_lpf_initialize( /* no null check. be carefull before calling */
	inv_lpf_config_t* p,
	float init,
	float gain
);

float inv_lpf_output( /* no null check. be carefull before calling */
	inv_lpf_config_t* p,
	float in
);

#endif /* INVLPF_H */
