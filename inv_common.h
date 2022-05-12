#ifndef INVCOMMON_H
#define INVCOMMON_H

#ifndef _PI
#define _PI 3.14159265f
#endif
#define TRANS_Q14 ((1<<14) - 1)			/* 16383 = 0x3FFF */
#define RESCALE_SHIFT_Q14 (14)			/* 16383 = 0x3FFF */
#define MICROSEC (1E-6)
#define FLOATING_ERROR (1E-7)

#endif /* INVCOMMON_H */
