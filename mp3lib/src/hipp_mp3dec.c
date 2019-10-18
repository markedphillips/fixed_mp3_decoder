
/* 
 * Mpeg Layer-1,2,3 audio decoder 
 * ------------------------------
 * copyright (c) 1995,1996,1997-2018 by Mark Phillips  All rights reserved.
 * See also 'README'
 *
 * slighlty optimized for machines without autoincrement/decrement.
 * The performance is highly compiler dependend. Maybe
 * the decode.c version for 'normal' processor may be faster
 * even for Intel processors.
 *
 * decoder optimized for fixed point processor 4143 MIPS
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mp3.h"
#include "mp3lib.h"

extern struct mpstr *gmp;

#include "real.h"

// If IO_CALC is defined, then the synth function maintains more precision during calculation.
#define IO_CALC
// If OPT_MAC is defined, then the synth function uses MAC instructions to improve the speed
// and precision of the calculations.
// This only works if IO_CALC is also defined.
#define OPT_MAC

#ifdef IO_CALC

#define WRITE_SAMPLE(samples,sum,clip) \
  if( sum>(32767<<15)) { *(samples) = 0x7fff;} \
  else if (sum < (-32768<<15)) { *(samples) = -0x8000; } \
  else { *(samples) = (short)(sum>>15); }

#else	// IO_CALC

#define WRITE_SAMPLE(samples,sum,clip) *(samples)=sum;

#endif	// IO_CALC

int synth_1to1_mono(Real *bandPtr,unsigned char *samples, int *pnt)
{
  short samples_tmp[64];
  short *tmp1 = samples_tmp;
  int i,ret;
  int pnt1 = 0;

  ret = synth_1to1(bandPtr,0,(unsigned char *) samples_tmp, &pnt1);
  samples += *pnt;

  for(i=0;i<32;i++) {
    *( (short *) samples) = *tmp1;
    samples += 2;
    tmp1 += 2;
  }
  *pnt += 64;

  return ret;
}

int synth_1to1 (Real *bandPtr,int channel,unsigned char *out, int *pnt)
{
  static const int step = 2;
  int bo;
  short *samples = (short *) (out + *pnt);
  struct u {
    short a1;
    short a2;
  };
  #define hi a2
  #define lo a1

  Real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;
  
  bo = gmp->synth_bo;

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = gmp->synth_buffs[0];
  }
  else {
    samples++;
    buf = gmp->synth_buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }

  gmp->synth_bo = bo;
  
  {
    register int j;
    Real *window = decwin + 16 - bo1;

    Real *bp = b0;
    for (j=16;j;j--,window+=0x20,samples+=step)
    {
      Real sum, sum1, sum2;

#ifndef IO_CALC

      struct u *up = (struct u *) window;

      sum1 = up->hi * (*bp);
      sum2 = (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);

      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);

#else	// IO_CALC

	Real* wp = window;

#ifdef OPT_MAC

	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1];"			// r3 = *window++
		"ldr r4, [r2];"			// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(wp),"m"(bp)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

	bp += 16;

#else	// OPT_MAC

	sum  = MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);

#endif	// IO_CALC

    }
    b0 = bp;

    {
      Real sum, sum1, sum2;

#ifndef IO_CALC

      struct u *up = (struct u *) window;
      sum1 = up->hi * (*bp);
      sum2 = (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);

      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);
      window-=0x20,samples+=step;

#else	// IO_CALC

#ifdef OPT_MAC

	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1];"		// r3 = window[0x0]
		"ldr r4, [r2];"		// r4 = b0[0x0]
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1, #8];"		// r3 = window[0x2]
		"ldr r4, [r2, #8];"		// r4 = b0[0x2]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #16];"	// r3 = window[0x4]
		"ldr r4, [r2, #16];"	// r4 = b0[0x4]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #24];"	// r3 = window[0x6]
		"ldr r4, [r2, #24];"	// r4 = b0[0x6]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #32];"	// r3 = window[0x8]
		"ldr r4, [r2, #32];"	// r4 = b0[0x8]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #40];"	// r3 = window[0xA]
		"ldr r4, [r2, #40];"	// r4 = b0[0xA]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #48];"	// r3 = window[0xC]
		"ldr r4, [r2, #48];"	// r4 = b0[0xC]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #56];"	// r3 = window[0xE]
		"ldr r4, [r2, #56];"	// r4 = b0[0xE]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(window),"m"(b0)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

#else	// OPT_MAC

	sum  = MULT_REAL(window[0x0], b0[0x0]);
	sum += MULT_REAL(window[0x2], b0[0x2]);
	sum += MULT_REAL(window[0x4], b0[0x4]);
	sum += MULT_REAL(window[0x6], b0[0x6]);
	sum += MULT_REAL(window[0x8], b0[0x8]);
	sum += MULT_REAL(window[0xA], b0[0xA]);
	sum += MULT_REAL(window[0xC], b0[0xC]);
	sum += MULT_REAL(window[0xE], b0[0xE]);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);

//      b0-=0x10,window-=0x20,samples += step;
    window -= 0x20,samples += step;
//	b0 -= 0x10;

#endif	// IO_CALC


    }
    window += bo1<<1;

    for (j=15;j;j--,b0-=0x10,window-=0x20,samples+=step)
    {
      Real sum, sum1, sum2;

      Real *bp = b0;

#ifndef IO_CALC

      struct u *up = (struct u *) window;

      --up;
      sum1 = -up->hi * (*bp);
      sum2 = (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
 
      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);

#else	// IO_CALC

	Real* wp = window;

#ifdef OPT_MAC

	--wp;
	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1];"			// r3 = *window--
		"ldr r4, [r2];"			// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"rsb r5, r5, #0;"		// r5 = -r5
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(wp),"m"(bp)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

#else	// OPT_MAC

	sum = MULT_REAL(-*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);


#endif	// IO_CALC


    }
  }
  *pnt += 128;

  return clip;
}

int synth_1to1_single (Real *bandPtr,int channel,unsigned char *out, int *pnt)
{
  int bo;
  short *samples = (short *) (out + *pnt);
  struct u {
    short a1;
    short a2;
  };
  #define hi a2
  #define lo a1

  Real *b0,(*buf)[0x110];
  int clip = 0; 
  int bo1;
  
  bo = gmp->synth_bo;

  if(!channel) {
    bo--;
    bo &= 0xf;
    buf = gmp->synth_buffs[0];
  }
  else {
    buf = gmp->synth_buffs[1];
  }

  if(bo & 0x1) {
    b0 = buf[0];
    bo1 = bo;
    dct64(buf[1]+((bo+1)&0xf),buf[0]+bo,bandPtr);
  }
  else {
    b0 = buf[1];
    bo1 = bo+1;
    dct64(buf[0]+bo,buf[1]+bo+1,bandPtr);
  }

  gmp->synth_bo = bo;
  
  {
    register int j;
    Real *window = decwin + 16 - bo1;

    Real *bp = b0;
    for (j=16;j;j--,window+=0x20,++samples)
    {
      Real sum, sum1, sum2;

#ifndef IO_CALC

      struct u *up = (struct u *) window;

      sum1 = up->hi * (*bp);
      sum2 = (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up++)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up++)->lo * (*bp++);

      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);

#else	// IO_CALC

	Real* wp = window;

#ifdef OPT_MAC

	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #4;"		// r3 = *window++
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1];"			// r3 = *window++
		"ldr r4, [r2];"			// r4 = *b0++
		"rsb r3, r3, #0;"		// r3 = -r3
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(wp),"m"(bp)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

	bp += 16;

#else	// OPT_MAC

	sum  = MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);
	sum += MULT_REAL(*wp++, *bp++);
	sum -= MULT_REAL(*wp++, *bp++);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);

#endif	// IO_CALC

    }
    b0 = bp;

    {
      Real sum, sum1, sum2;

#ifndef IO_CALC

      struct u *up = (struct u *) window;
      sum1 = up->hi * (*bp);
      sum2 = (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);
      up += 2;
      bp += 2;
      sum1 += up->hi * (*bp);
      sum2 += (unsigned)(up)->lo * (*bp);

      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);

      window-=0x20,++samples;

#else	// IO_CALC

#ifdef OPT_MAC

	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1];"		// r3 = window[0x0]
		"ldr r4, [r2];"		// r4 = b0[0x0]
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1, #8];"		// r3 = window[0x2]
		"ldr r4, [r2, #8];"		// r4 = b0[0x2]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #16];"	// r3 = window[0x4]
		"ldr r4, [r2, #16];"	// r4 = b0[0x4]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #24];"	// r3 = window[0x6]
		"ldr r4, [r2, #24];"	// r4 = b0[0x6]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #32];"	// r3 = window[0x8]
		"ldr r4, [r2, #32];"	// r4 = b0[0x8]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #40];"	// r3 = window[0xA]
		"ldr r4, [r2, #40];"	// r4 = b0[0xA]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #48];"	// r3 = window[0xC]
		"ldr r4, [r2, #48];"	// r4 = b0[0xC]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1, #56];"	// r3 = window[0xE]
		"ldr r4, [r2, #56];"	// r4 = b0[0xE]
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(window),"m"(b0)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

#else	// OPT_MAC

	sum  = MULT_REAL(window[0x0], b0[0x0]);
	sum += MULT_REAL(window[0x2], b0[0x2]);
	sum += MULT_REAL(window[0x4], b0[0x4]);
	sum += MULT_REAL(window[0x6], b0[0x6]);
	sum += MULT_REAL(window[0x8], b0[0x8]);
	sum += MULT_REAL(window[0xA], b0[0xA]);
	sum += MULT_REAL(window[0xC], b0[0xC]);
	sum += MULT_REAL(window[0xE], b0[0xE]);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);

//      b0-=0x10,window-=0x20,samples += step;
    window-=0x20,++samples;
	b0-=0x10;

#endif	// IO_CALC


    }
    window += bo1<<1;

    for (j=15;j;j--,b0-=0x10,window-=0x20,++samples)
    {
      Real sum, sum1, sum2;

      Real *bp = b0;

#ifndef IO_CALC

      struct u *up = (struct u *) window;

      --up;
      sum1 = -up->hi * (*bp);
      sum2 = (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
      sum1 -= up->hi * (*bp);
      sum2 -= (unsigned)(up--)->lo * (*bp++);
 
      sum1 += (sum2 >> 16);
      sum = sum1 >> 14;
      WRITE_SAMPLE(samples,sum,clip);

#else	// IO_CALC

	Real* wp = window;

#ifdef OPT_MAC

	--wp;
	asm volatile (
		"ldr r1, %1;"			// r1 = window
		"ldr r2, %2;"			// r2 = b0

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smull r5, r6, r3, r4;"	// r6r5 = r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1], #-4;"	// r3 = *window--
		"ldr r4, [r2], #4;"		// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"ldr r3, [r1];"			// r3 = *window--
		"ldr r4, [r2];"			// r4 = *b0++
		"smlal r5, r6, r3, r4;"	// r6r5 += r3 * r4

		"mov r5, r5, lsr #15;"	// r5 >>= 15
		"orr r5, r5, r6, lsl #17;"	// r5 = r5 | (r6 << 17)
		"rsb r5, r5, #0;"		// r5 = -r5
		"str r5, %0;"			// sum = r5
		: "=m"(sum)
		: "m"(wp),"m"(bp)
		: "r1", "r2", "r3", "r4", "r5", "r6"
		);

#else	// OPT_MAC

	sum = MULT_REAL(-*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);
	sum -= MULT_REAL(*(--wp), *bp++);

#endif	// OPT_MAC

	WRITE_SAMPLE(samples,sum,clip);


#endif	// IO_CALC

    }
  }
  *pnt += 64;

  return clip;
}

