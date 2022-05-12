#ifndef INVSIN_H
#define INVSIN_H

/*+-------------------------------------------------------------------------+*/
/*| calculate sin(ωt) by used ztrans. 										|*/
/*|-------------------------------------------------------------------------|*/
/*| ■ Discrete-time															|*/
/*| input            : x(kΔt)        = δ(kΔt) 								|*/
/*| transfer function: f(kΔt)/x(kΔt) = sin(ωkΔt)							|*/
/*| output           : f(kΔt)        = sin(ωkΔt)							|*/
/*|-------------------------------------------------------------------------|*/
/*| ■ ztrans																|*/
/*| input            : X(z)          = 1	 								|*/
/*| transfer function: F(z)/X(z)     = F(z)/1 = F(z)						|*/
/*| output           : F(z)          = zsin(ωΔt)/(z-(2zcos(ωΔt))+1)			|*/
/*|                                  = 2cos(ωΔt)F(z)z^-1-F(z)z^-2+sin(ωΔt)X(z)z^-1	|*/
/*|-------------------------------------------------------------------------|*/
/*| ■ inverse ztrans														|*/
/*| output           : y(kΔt)        = a1f((k-1)Δt)+a2f((k-2)Δt)+b1x((k-1)Δt)	|*/
/*|                                  = a1f((k-1)Δt)+a2f((k-2)Δt) (k>1)		|*/
/*| a1               : 2cos(ωΔt)											|*/
/*| a2               : -1													|*/
/*| b1               : sin(ωΔt)												|*/
/*|-------------------------------------------------------------------------|*/
/*| k     : 0, 1, 2, ..., n. Software tick.									|*/
/*| kΔt   : Discrete-time. Software tick time for ztrans timing.			|*/
/*| δ(kΔt): Impulse. Software seems to input implse.						|*/
/*+-------------------------------------------------------------------------+*/
typedef struct{
    float cycle;					/* T[μs] */
    float dt;						/* Δt[μs] */
    short buf[3];					/* ztrans buffer. fixed-point number Q14. */
    short a1;						/* ztrans parameter. fixed-point number Q14. */
    short a2;						/* ztrans parameter. fixed-point number Q14. */
    short b1;						/* ztrans parameter. fixed-point number Q14. */
} inv_sin_ztrans_t;

extern void inv_sin_ztarans_init();
extern void inv_sin_ztrans(inv_sin_ztrans_t* p);

#endif /* INVSIN_H */
