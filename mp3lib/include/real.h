/* (c) 1998-2018 Mark Phillips */

#ifndef REAL_H_
#define REAL_H_

#define REAL_FLOAT(x) ((Real)((x) * 32768.0))

// If defined, then real numbers are multiplied with with more bits of precision,
// but the process takes longer.
//#define PRECISE_REAL_MULT

#ifndef __thumb__

#ifdef PRECISE_REAL_MULT

inline Real mult_real(Real a, Real b)
{
	Real result;

	asm volatile (
		"ldr   r3,%1;"
		"ldr   r4,%2;"
		"smull r5,r6,r3,r4;"
		"mov   r5,r5,lsr #15;"
		"orr   r5,r5,r6,lsl #17;"
		"str   r5,%0;"
		: "=m"(result)
		: "m"(a),"m"(b)
		: "r3", "r4", "r5", "r6"
		);

	return result;
}

#define MULT_REAL(a,b) mult_real(a, b)
#define MULT_REAL2(a,b) mult_real(a, b)

#else	// PRECISE_REAL_MULT

#define MULT_REAL(a,b) ((a * b) >> 15)
#define MULT_REAL2(a,b) ((a * b) >> 15)

#endif	// PRECISE_REAL_MULT


#endif	// __thumb__

#endif	// REAL_H_
