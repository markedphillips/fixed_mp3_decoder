/* (c) 1998-2018 Mark Phillips */

#ifndef __DSP_QMATH__
#define __DSP_QMATH__

#include "hipp_dsp.h"
#include <stddef.h>

/* table of rounding values when right shift qfloat values */
extern const QFIXED Q_SHIFT_ROUND[16];

/* error code to indicate manual saturation has occurred */
extern int *dsp_qerror;

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcheck)
/* Validate a qfloat result. */
static inline
QFIXED
_DEFUN (dsp_qcheck, (qval),
        QACC     qval)
{
#if !defined(Q_SATURATION)
  if (qval >= Q_OVERFLOW)
    {
      *dsp_qerror = Q_MAX;
      return Q_MAX;
    } 
  else if (qval < Q_MIN)
    {
      *dsp_qerror = Q_MIN;
      return Q_MIN;
    }
  else
    return qval;
#endif /* Q_SATURATION not defined */
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcheckov)
/* Validate a qfloat result has not overflowed. */
static inline
QFIXED
_DEFUN (dsp_qcheckov, (qval),
        QACC     qval)
{
#if !defined(Q_SATURATION)
  if (qval >= Q_OVERFLOW)
    {
      *dsp_qerror = Q_MAX;
      return Q_MAX;
    }
  else
    return qval;
#endif /* Q_SATURATION not defined */
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qchecknov)
/* Validate a qfloat result has not negatively overflowed. */
static inline
QFIXED
_DEFUN (dsp_qchecknov, (qval),
        QACC     qval)
{
#if !defined(Q_SATURATION)
  if (qval < Q_MIN)
    {
      *dsp_qerror = Q_MIN;
      return Q_MIN;
    }
  else
    return qval;
#endif /* Q_SATURATION not defined */
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qoverflow)
/* Return saturated value based on sign and set error flag. */
static inline
QFIXED
_DEFUN (dsp_qoverflow, (sign),
        int  sign)
{
  if (sign < 0)
    {
      *dsp_qerror = Q_MIN;
      return Q_MIN;
    }
  else
    {
      *dsp_qerror = Q_MAX;
      return Q_MAX;
    }
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qinttoq)
/* Return QACC equivalent of an integer. */
static inline
QACC
_DEFUN (dsp_qinttoq, (input),
        int  input)
{
  QACC result = input << Q_MULT_SHIFT;
  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfixed)
/* Transfer QACC value to QFIXED value. */
static inline
QFIXED
_DEFUN (dsp_qfixed, (acc),
	QACC  acc)
{
  return (QFIXED)acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qacc)
/* Transfer QFIXED value to QACC value. */
static inline
QACC
_DEFUN (dsp_qacc, (value),
	QFIXED value)
{
  QACC acc = value;
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccneg)
/* Negate accumulator value. */
static inline
QACC
_DEFUN (dsp_qaccneg, (value),
	QACC acc)
{
  acc = -acc;
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qshiftmr)
/* Shift and round result of multiplication. */
static inline
QACC
_DEFUN (dsp_qshiftmr, (in),
        QACC   in)
{
  QACC result = (in + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;

  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmacshift)
/* Shift and round result of multiply and accumulate. */
static inline
QACC
_DEFUN (dsp_qmacshift, (in),
        QACC   in)
{
#ifdef __QACC_EXTRA_BYTE__
  in = (in + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;
#endif
  return in;
}
#endif

#define dsp_qaccshift dsp_qmacshift

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaddshift)
/* Add two values then shift the result. */
static inline
QFIXED
_DEFUN (dsp_qaddshift, (in_1, in_2, shift),
        QACC   in_1 _AND
        QACC   in_2 _AND
        int    shift)
{
#ifndef NO_Q_ROUNDING 
  QFIXED result = (in_1 + in_2 + Q_SHIFT_ROUND[shift]) >> shift;
#else /* NO_Q_ROUNDING */
  QFIXED result = (in_1 + in_2) >> shift;
#endif
  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaddshift1)
/* Add two values then shift the result right by 1. */
static inline
QFIXED
_DEFUN (dsp_qaddshift1, (in_1, in_2),
        QFIXED   in_1 _AND
        QFIXED   in_2)
{
#ifndef NO_Q_ROUNDING 
  QFIXED result = (in_1 + in_2 + Q_SHIFT1_ROUND) >> 1;
#else /* NO_Q_ROUNDING */
  QFIXED result = (in_1 + in_2) >> 1;
#endif
  return result;
}
#endif

#define qaddshift2(in_1, in_2) (qaddshift (in_1, in_2, 2))

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qsubshift)
/* Subtract two values then shift the result. */
static inline
QFIXED
_DEFUN (dsp_qsubshift, (in_1, in_2, shift),
        QACC   in_1 _AND
        QACC   in_2 _AND
        int    shift)
{
#ifndef NO_Q_ROUNDING 
  QFIXED result = dsp_qcheckov ((in_1 - in_2 + Q_SHIFT_ROUND[shift]) >> shift);  
#else /* NO_Q_ROUNDING */
  QFIXED result = (in_1 - in_2) >> shift;
#endif
  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qsubshift1)
/* Subtract two values then shift the result right by 1. */
static inline
QFIXED
_DEFUN (dsp_qsubshift1, (in_1, in_2),
        QFIXED   in_1 _AND
        QFIXED   in_2)
{
#ifndef NO_Q_ROUNDING 
  QFIXED result = dsp_qcheckov ((in_1 - in_2 + Q_SHIFT1_ROUND) >> 1);
#else /* NO_Q_ROUNDING */
  QFIXED result = (in_1 - in_2) >> 1;
#endif
  return result;
}
#endif

#define dsp_qsubshift2(in_1, in_2) (dsp_qsubshift (in_1, in_2, 2))

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmult2add)
/* Multiply two pairs of qfloat values and add results. */
static inline
QFIXED
_DEFUN (dsp_qmult2add, (in_1, in_2, in_3, in_4),
        QFIXED in_1 _AND
        QFIXED in_2 _AND
        QFIXED in_3 _AND
        QFIXED in_4)
{
  QFIXED result;
  QACC temp = (in_1 * in_2 + in_3 * in_4 + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;
  result = dsp_qcheck(temp);

  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmult2sub)
/* Multiply two pairs of qfloat values and subtract results. */
static inline
QFIXED
_DEFUN (dsp_qmult2sub, (in_1, in_2, in_3, in_4),
        QFIXED in_1 _AND
        QFIXED in_2 _AND
        QFIXED in_3 _AND
        QFIXED in_4)
{
  QFIXED result;
  QACC temp = (in_1 * in_2 - in_3 * in_4 + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;
  result = dsp_qcheck (temp);

  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmult)
/* Multiply a qfloat by another qfloat. */
static inline
QFIXED
_DEFUN (dsp_qmult, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = (in_1 * in_2 + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;
  temp = dsp_qcheckov(temp);

  return (QFIXED)temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmultacc)
/* Multiply an accumulator by another accumulator. */
static inline
QACC
_DEFUN (dsp_qmultacc, (in_1, in_2),
        QACC in_1 _AND  
        QACC in_2)
{
  QACC temp = (in_1 * in_2 + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;

  return temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcmult)
/* Multiply two qcmplx values together. */
static inline
_VOID
_DEFUN (dsp_qcmult, (in_1, in_2, out),
        QCMPLX  in_1 _AND  
        QCMPLX  in_2 _AND
        QCMPLX *out)
{
  QACC rtemp, itemp;
  rtemp = dsp_qmult2sub (in_1.real, in_2.real, in_1.imag, in_2.imag);
  itemp = dsp_qmult2add (in_1.real, in_2.imag, in_1.imag, in_2.real);

  (*out).real = rtemp;
  (*out).imag = itemp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcjmult)
/* Multiply a qcmplx value by a qcmplx conjugate value. */
static inline
_VOID
_DEFUN (dsp_qcjmult, (in_1, in_2, out),
        QCMPLX  in_1 _AND  
        QCMPLX  in_2 _AND
        QCMPLX *out)
{
  QACC rtemp, itemp;
  rtemp = dsp_qmult2add (in_1.real, in_2.real, in_1.imag, in_2.imag);
  itemp = dsp_qmult2sub (in_1.imag, in_2.real, in_2.imag, in_1.real);

  (*out).real = rtemp;
  (*out).imag = itemp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcrmult)
/* Multiply a qcomplex value by a qfloat value. */
static inline
_VOID
_DEFUN (dsp_qcrmult, (in_1, in_2, out),
        QCMPLX  in_1 _AND  
        QFIXED  in_2 _AND
        QCMPLX *out)
{
  QACC rtemp, itemp;
  rtemp = dsp_qmult (in_1.real, in_2);
  itemp = dsp_qmult (in_1.imag, in_2);

  (*out).real = rtemp;
  (*out).imag = itemp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmultnc)
/* Multiply a qfloat by another qfloat but do not check result. */
static inline
QACC
_DEFUN (dsp_qmultnc, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = (in_1 * in_2 + Q_FLOAT_ROUND) >> Q_MULT_SHIFT;

  return temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmultns)
/* Multiply a qfloat by another qfloat and place unshifted result in accumulator. */
static inline
QACC
_DEFUN (dsp_qmultns, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = in_1 * in_2;

  return temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qmac)
/* Multiply and accumulate. */
static inline
QACC
_DEFUN (dsp_qmac, (in_1, in_2, sum),
        QFIXED   in_1   _AND
	QFIXED   in_2   _AND
	QACC     sum)
{
#ifndef __QACC_EXTRA_BYTE__
  sum += dsp_qmultnc (in_1, in_2);
#else
  sum += dsp_qmultns (in_1, in_2);
#endif
  return sum;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfmultf)
/* Multiply QFIXED by QFIXED and place in accumulator. */
static inline
QACC
_DEFUN (dsp_qfmultf, (in_1, in_2),
        QFIXED   in_1   _AND
	QFIXED   in_2)
{
  QACC sum;
#ifndef __QACC_EXTRA_BYTE__
  sum = dsp_qmultnc (in_1, in_2);
#else
  sum = dsp_qmultns (in_1, in_2);
#endif
  return sum;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccmultf)
/* Multiply the accumulator by a QFIXED. */
static inline
QACC
_DEFUN (dsp_qaccmultf, (acc, val),
        QACC   acc   _AND
        QFIXED val)
{
  acc *= val;
#ifndef __QACC_EXTRA_BYTE__
  acc = dsp_qshiftmr (acc);
#endif
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccmultfws)
/* Multiply the accumulator by a QFIXED and always shift result. */
static inline
QACC
_DEFUN (dsp_qaccmultfws, (acc, val),
        QACC   acc   _AND
        QFIXED val)
{
  acc *= val;
  acc = dsp_qshiftmr (acc);
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccmacf)
/* Multiply and accumulate where one input is accumulator and other is fixed-point value. */
static inline
QACC
_DEFUN (dsp_qaccmacf, (in_1, in_2, sum),
        QACC     in_1   _AND
	QFIXED   in_2   _AND
	QACC     sum)
{
  sum += dsp_qaccmultf (in_1, in_2);
  return sum;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccdouble)
/* Double accumulator value. */
static inline
QACC
_DEFUN (dsp_qaccdouble, (acc),
        QACC     acc)
{
  acc <<= 1;
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qsub)
/* Subtract a qfloat from another qfloat. */
static inline
QFIXED
_DEFUN (dsp_qsub, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = in_1 - in_2;
  QFIXED result = dsp_qcheck (temp);
  return result;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qsubnc)
/* Subtract a qfloat from another qfloat without checking and place result in accumulator. */
static inline
QACC
_DEFUN (dsp_qsubnc, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = in_1 - in_2;
  return temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccsubf)
/* Subtract a qfloat from the accumulator. */
static inline
QACC
_DEFUN (dsp_qaccsubf, (acc, val),
        QACC   acc   _AND
        QFIXED val)
{
  acc -= val;
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccsub)
/* Subtract one accumulator value from another. */
static inline
QACC
_DEFUN (dsp_qaccsub, (acc1, acc2),
        QACC   acc1   _AND
        QACC   acc2)
{
  acc1 -= acc2;
  return acc1;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qsubov)
/* Subtract a qfloat from another qfloat, only checking for overflow. */
static inline
QFIXED
_DEFUN (dsp_qsubov, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = in_1 - in_2;
  temp = dsp_qcheckov(temp);

  return (QFIXED)temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcsub)
/* Subtract two qcomplex numbers. */
static inline
_VOID
_DEFUN (dsp_qcsub, (in_1, in_2, out),
        QCMPLX  in_1  _AND
        QCMPLX  in_2  _AND
        QCMPLX *out)
{
  QACC rtemp, itemp;
  rtemp = dsp_qsub (in_1.real, in_2.real);
  itemp = dsp_qsub (in_1.imag, in_2.imag);
  (*out).real = rtemp;
  (*out).imag = itemp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qadd)
/* Add a qfloat to another qfloat. */
static inline
QFIXED
_DEFUN (dsp_qadd, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = (in_1 + in_2);
  temp = dsp_qcheck (temp);

  return (QFIXED)temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaddnc)
/* Add a qfloat to another qfloat without checking and place result in accumulator. */
static inline
QACC
_DEFUN (dsp_qaddnc, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = (in_1 + in_2);
  return temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccaddf)
/* Add a qfloat to another qfloat without checking and place result in accumulator. */
static inline
QACC
_DEFUN (dsp_qaccaddf, (acc, val),
        QACC   acc   _AND
        QFIXED val)
{
  acc += val;
  return acc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaccadd)
/* Add two accumulator values. */
static inline
QACC
_DEFUN (dsp_qaccadd, (acc1, acc2),
        QACC   acc1   _AND
        QACC   acc2)
{
  acc1 += acc2;
  return acc1;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qaddov)
/* Add a qfloat to another qfloat, only checking for overflow. */
static inline
QFIXED
_DEFUN (dsp_qaddov, (in_1, in_2),
        QFIXED in_1 _AND  
        QFIXED in_2)
{
  QACC temp = in_1 + in_2;
  temp = dsp_qcheckov(temp);

  return (QFIXED)temp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcadd)
/* Add two qcomplex numbers together. */
static inline
_VOID
_DEFUN (dsp_qcadd, (in_1, in_2, out),
        QCMPLX  in_1  _AND
        QCMPLX  in_2  _AND
        QCMPLX *out)
{
  QACC rtemp, itemp;
  rtemp = dsp_qadd (in_1.real, in_2.real);
  itemp = dsp_qadd (in_1.imag, in_2.imag);
  (*out).real = rtemp;
  (*out).imag = itemp;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcdiv)
/* Divide a qcomplex number by a qcomplex number. */
static inline
_VOID
_DEFUN (dsp_qcdiv, (in_1, in_2, out),
        QCMPLX   in_1 _AND
        QCMPLX   in_2 _AND
        QCMPLX  *out)
{
  QACC magnitude, rtemp, itemp;
  magnitude = dsp_qmult2add (in_2.real, in_2.real, in_2.imag, in_2.imag);
  rtemp = dsp_qmult2add (in_1.real, in_2.real, in_1.imag, in_2.imag);  
  itemp = dsp_qmult2sub (in_1.real, in_2.imag, in_1.imag, in_2.real);
  (*out).real = dsp_qdiv (rtemp, magnitude);
  (*out).imag = dsp_qdiv (itemp, magnitude);
}
#endif
 

#endif /* __DSP_QMATH__ */










