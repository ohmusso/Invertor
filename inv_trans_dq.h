#ifndef INVTRANSDQ_H
#define INVTRANSDQ_H

typedef struct{
    float d;						/* d */
    float q;						/* q */
} inv_dq_t;

extern inv_dq_t inv_trans_dq(
	float a, 
	float b,
	float rad
);

#endif /* INVTRANSDQ_H */
