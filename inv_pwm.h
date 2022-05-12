#ifndef INVPWM_H
#define INVPWM_H

typedef struct{
    int ch;							/* pwm ch */
    float cycle;					/* pwm cycle[μs] */
    float duty;						/* pwm duty[μs] */
} inv_pwm_config_t;

#define INV_PWM_OUTPUT_HIGH 1.0
#define INV_PWM_OUTPUT_LOW 0.0

typedef enum INV_PWM_OUTPUT_STATUS{
	INV_PWM_OUTPUT_STATUS_INIT,
	INV_PWM_OUTPUT_STATUS_ERROR_NULL,
	INV_PWM_OUTPUT_STATUS_ERROR_InvalidCh,
	INV_PWM_OUTPUT_STATUS_RUN
} INV_PWM_OUTPUT_STATUS_e;

extern void inv_pwm_init(inv_pwm_config_t* p);
extern float inv_pwm_main(
	int ch,							/* pwm ch */
	float dt						/* [μs] */
);
extern INV_PWM_OUTPUT_STATUS_e inv_pwm_getStatus(int ch);

#endif /* INVPWM_H */
