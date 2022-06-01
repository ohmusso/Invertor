#ifndef INVRUNGEKUTTAFLT_H
#define INVRUNGEKUTTAFLT_H

/* 4 degree Runge–Kutta method */

typedef struct{
    float dt;						/* dt[μs] */
    float h;						/* h[μs] */
    float buf;						/* buf */
} inv_rkflt_config_t;

extern void inv_rkflt_initialize( /* no null check. be carefull before calling */
	inv_rkflt_config_t* p,
	float init,
	float h,
	float dt
);

extern float inv_rkflt_output( /* no null check. be carefull before calling */
	inv_rkflt_config_t* p,
	float in
);

#endif /* INVRUNGEKUTTAFLT_H */
