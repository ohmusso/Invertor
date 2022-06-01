#ifndef INVTRANSAB_H
#define INVTRANSAB_H

typedef struct{
    float a;						/* α */
    float b;						/* β */
} inv_ab_t;

extern inv_ab_t inv_trans_ab(
	float u, 
	float v,
	float w
);

#endif /* INVTRANSAB_H */
