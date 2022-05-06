#include <math.h>
#include "inv_sin.h"

void inv_sin_ztarans_init(inv_sin_ztrans_t* p)
{
	if( p == (inv_sin_ztrans_t*)(0U) ){
		/* nop */
	}
	else{
		p->a1 = (short)((2*cos(2*_PI/p->cycle*p->dt))*TRANS_Q14);
		p->a2 = (short)(0xC000);	/*	-1 on Q14	*/
		p->b1 = (short)(sin(2*_PI/p->cycle*p->dt)*TRANS_Q14);
		p->buf[0] = 0;
		p->buf[1] = p->b1;
		p->buf[2] = 0;
	}
}

void inv_sin_ztrans(inv_sin_ztrans_t* p)
{
	p->buf[0] = ((p->a1*p->buf[1])>>RESCALE_SHIFT_Q14)+((p->a2*p->buf[2])>>RESCALE_SHIFT_Q14);
	p->buf[2] = p->buf[1];
	p->buf[1] = p->buf[0];
}
