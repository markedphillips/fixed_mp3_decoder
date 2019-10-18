/* (c) 1998-2018 Mark Phillips */

#ifndef __DSPCNST_H
#define __DSPCNST_H

#include "dsptypes.h"

#ifndef NO_FLOAT
#define __PI        3.14159265358979323846
#define __DOUBLE_PI 6.28318530717958647692
#define __SQRT_2    1.4142135623730950488

#endif /* NO_FLOAT */

#ifndef NO_Q_ROUNDING
#define Q_FLOAT_ROUND  16384
#define Q_SHIFT1_ROUND 1
#define Q_SHIFT2_ROUND 2
#else /* NO_Q_ROUNDING */
#define Q_FLOAT_ROUND  0
#define Q_SHIFT1_ROUND 0
#define Q_SHIFT2_ROUND 0
#endif /* NO_Q_ROUNDING */

#define Q_MULT_SHIFT 15
#define Q_OVERFLOW   32768
#define Q_MIN (-32768)
#define Q_MAX (32767) 

#define Q_BITS 16

#if __QACC_MAX__ > 2147483647
#ifndef __QACC_EXTRA_BYTE__
#define __QACC_EXTRA_BYTE__  1
#endif
#endif

/* valid states for multi-rate FIR filters */
#define DSP_NEED_ITEM       0
#define DSP_NO_ITEM_NEEDED  1

/* Viterbi maximum to identify impossible paths */
#define DSP_VT_MAX   9999

#endif /* no __DSPCNST_H */


