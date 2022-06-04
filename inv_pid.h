#ifndef INVPID_H
#define INVPID_H

typedef struct{
    float kp;						/* Propostional */
    float ki;						/* Integral */
    float kd;						/* Defferential */
    float buf_i;					/* buf Integral */
    float buf_d;					/* buf Defferential */
} inv_pid_config_t;

void inv_pid_initialize( /* no null check. be carefull before calling */
	inv_pid_config_t* p,
	float kp,
	float ki,
	float kd,
	float init
);

float inv_pid_output( /* no null check. be carefull before calling */
	inv_pid_config_t* p,
	float in
);

#endif /* INVPID_H */
