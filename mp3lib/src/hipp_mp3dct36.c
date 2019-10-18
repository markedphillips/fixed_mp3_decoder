/*
 DCT insipired by Jeff Tsay's DCT from the maplay package
 this is an optimized version with manual unroll.

 References:
 [1] S. Winograd: "On Computing the Discrete Fourier Transform",
     Mathematics of Computation, Volume 32, Number 141, January 1978,
     Pages 175-199

//.. (c) 1998-2018 Mark Phillips Copyright 

*/

#include "mp3.h"

#define QMSHIFT 18

Real tfcos36[9] = {
  0x000201f5,  0x00021210,  0x000234ee,  0x00027109,  0x0002d414,  0x00037ca5,  0x0004bb7f,  0x0007ba37,  0x0016f28a,
};

Real COS9[9] = {
  0x00040000,  0x0003f071,  0x0003c23f,  0x000376cf,  0x0003106e,  0x00029237,  0x00020000,  0x00015e3b,  0x0000b1d1,
};

void dct36(Real *inbuf,Real *o1,Real *o2,Real *wintab,Real *tsbuf)
{
  {
    register Real *in = inbuf;

    in[17]+=in[16]; in[16]+=in[15]; in[15]+=in[14];
    in[14]+=in[13]; in[13]+=in[12]; in[12]+=in[11];
    in[11]+=in[10]; in[10]+=in[9];  in[9] +=in[8];
    in[8] +=in[7];  in[7] +=in[6];  in[6] +=in[5];
    in[5] +=in[4];  in[4] +=in[3];  in[3] +=in[2];
    in[2] +=in[1];  in[1] +=in[0];

    in[17]+=in[15]; in[15]+=in[13]; in[13]+=in[11]; in[11]+=in[9];
    in[9] +=in[7];  in[7] +=in[5];  in[5] +=in[3];  in[3] +=in[1];


  {

#define MACRO0(v) { \
    Real tmp; \
    out2[9+(v)] = ((tmp = sum0 + sum1) * (long long)w[27+(v)]) >> QMSHIFT; \
    out2[8-(v)] = ((long long)tmp * w[26-(v)]) >> QMSHIFT;  } \
    sum0 -= sum1; \
    ts[SBLIMIT*(8-(v))] = out1[8-(v)] + (long)(((long long)sum0 * w[8-(v)]) >> QMSHIFT); \
    ts[SBLIMIT*(9+(v))] = out1[9+(v)] + (long)(((long long)sum0 * w[9+(v)]) >> QMSHIFT); 
#define MACRO1(v) { \
	Real sum0,sum1; \
    sum0 = tmp1a + tmp2a; \
	sum1 = ((tmp1b + tmp2b) * (long long)tfcos36[(v)]) >> QMSHIFT; \
	MACRO0(v); }
#define MACRO2(v) { \
    Real sum0,sum1; \
    sum0 = tmp2a - tmp1a; \
    sum1 = ((tmp2b - tmp1b) * (long long)tfcos36[(v)]) >> QMSHIFT; \
	MACRO0(v); }

    register const Real *c = COS9;
    register Real *out2 = o2;
	register Real *w = wintab;
	register Real *out1 = o1;
	register Real *ts = tsbuf;

    Real ta33,ta66,tb33,tb66;

    ta33 = ((long long)in[2*3+0] * c[3]) >> QMSHIFT;
    ta66 = ((long long)in[2*6+0] * c[6]) >> QMSHIFT;
    tb33 = ((long long)in[2*3+1] * c[3]) >> QMSHIFT;
    tb66 = ((long long)in[2*6+1] * c[6]) >> QMSHIFT;

    { 
      Real tmp1a,tmp2a,tmp1b,tmp2b;
      tmp1a =             (long)((((long long)in[2*1+0] * c[1]) + ((long long)in[2*5+0] * c[5]) + ((long long)in[2*7+0] * c[7])) >> QMSHIFT) + ta33;
      tmp1b =             (long)((((long long)in[2*1+1] * c[1]) + ((long long)in[2*5+1] * c[5]) + ((long long)in[2*7+1] * c[7])) >> QMSHIFT) + tb33;
      tmp2a = in[2*0+0] + (long)((((long long)in[2*2+0] * c[2]) + ((long long)in[2*4+0] * c[4]) + ((long long)in[2*8+0] * c[8])) >> QMSHIFT) + ta66;
      tmp2b = in[2*0+1] + (long)((((long long)in[2*2+1] * c[2]) + ((long long)in[2*4+1] * c[4]) + ((long long)in[2*8+1] * c[8])) >> QMSHIFT) + tb66;

      MACRO1(0);
      MACRO2(8);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
      tmp1a = (( in[2*1+0] - in[2*5+0] - in[2*7+0] ) * (long long)c[3]) >> QMSHIFT;
      tmp1b = (( in[2*1+1] - in[2*5+1] - in[2*7+1] ) * (long long)c[3]) >> QMSHIFT;
      tmp2a = (long)((( in[2*2+0] - in[2*4+0] - in[2*8+0] ) * (long long)c[6]) >> QMSHIFT) - in[2*6+0] + in[2*0+0];
      tmp2b = (long)((( in[2*2+1] - in[2*4+1] - in[2*8+1] ) * (long long)c[6]) >> QMSHIFT) - in[2*6+1] + in[2*0+1];

      MACRO1(1);
      MACRO2(7);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
      tmp1a =             (long)((((long long)in[2*1+0] * c[5]) + ((long long)-in[2*5+0] * c[7]) + ((long long)in[2*7+0] * c[1])) >> QMSHIFT) - ta33;
      tmp1b =             (long)((((long long)in[2*1+1] * c[5]) + ((long long)-in[2*5+1] * c[7]) + ((long long)in[2*7+1] * c[1])) >> QMSHIFT) - tb33;
      tmp2a = in[2*0+0] + (long)((((long long)-in[2*2+0] * c[8]) + ((long long)-in[2*4+0] * c[2]) + ((long long)in[2*8+0] * c[4])) >> QMSHIFT) + ta66;
      tmp2b = in[2*0+1] + (long)((((long long)-in[2*2+1] * c[8]) + ((long long)-in[2*4+1] * c[2]) + ((long long)in[2*8+1] * c[4])) >> QMSHIFT) + tb66;

      MACRO1(2);
      MACRO2(6);
    }

    {
      Real tmp1a,tmp2a,tmp1b,tmp2b;
      tmp1a =             (long)((((long long)in[2*1+0] * c[7]) + ((long long)in[2*5+0] * c[1]) + ((long long)-in[2*7+0] * c[5])) >> QMSHIFT) - ta33;
      tmp1b =             (long)((((long long)in[2*1+1] * c[7]) + ((long long)in[2*5+1] * c[1]) + ((long long)-in[2*7+1] * c[5])) >> QMSHIFT) - tb33;
      tmp2a = in[2*0+0] + (long)((((long long)-in[2*2+0] * c[4])  + ((long long)in[2*4+0] * c[8]) + ((long long)-in[2*8+0] * c[2])) >> QMSHIFT) + ta66;
      tmp2b = in[2*0+1] + (long)((((long long)-in[2*2+1] * c[4])  + ((long long)in[2*4+1] * c[8]) + ((long long)-in[2*8+1] * c[2])) >> QMSHIFT) + tb66;

      MACRO1(3);
      MACRO2(5);
    }

	{
		Real sum0,sum1;
    	sum0 =  in[2*0+0] - in[2*2+0] + in[2*4+0] - in[2*6+0] + in[2*8+0];
    	sum1 = ((in[2*0+1] - in[2*2+1] + in[2*4+1] - in[2*6+1] + in[2*8+1] ) * (long long)tfcos36[4]) >> QMSHIFT;
		MACRO0(4);
	}
  }

  }
}
