// (c) 1998-2018 Mark Phillips 

#include        <stdio.h>
#include        <string.h>
#include        <signal.h>
#include	<setjmp.h>

#include        <math.h>

#include "hipp_dsp.h"

# define M_PI       3.14159265358979323846
# define M_SQRT2	1.41421356237309504880
//# define REAL_IS_QFLOAT
# define REAL_IS_LONG
# define NEW_DCT9

# define random rand
# define srandom srand

#ifndef REAL_IS_QFLOAT
#ifdef REAL_IS_LONG
#  define Real long
#elif defined REAL_IS_FLOAT
#  define Real float
#elif defined(REAL_IS_LONG_DOUBLE)
#  define Real long double
#else
#  define Real double
#endif
#else
#define Real QACC
#endif

#define mp3_exit(n) { longjmp(mp3jbuf, MP3_EXIT); }

#ifdef __GNUC__
#define INLINE inline
#else
#define INLINE
#endif

/* AUDIOBUFSIZE = n*64 with n=1,2,3 ...  */
#define		AUDIOBUFSIZE		16384

#define         FALSE                   0
#define         TRUE                    1

#define         MPG_MD_STEREO           0
#define         MPG_MD_JOINT_STEREO     1
#define         MPG_MD_DUAL_CHANNEL     2
#define         MPG_MD_MONO             3


/* Pre Shift fo 16 to 8 bit converter table */
#define AUSHIFT (3)

struct parameter {
	int quiet;	/* shut up! */
	int tryresync;  /* resync stream after error */
	int verbose;    /* verbose level */
	int checkrange;
};

extern unsigned int   mp3_get1bit(void);
extern unsigned int   mp3_getbits(int);
extern unsigned int   mp3_getbits_fast(int);
extern int set_pointer(long);

extern unsigned char *wordpointer;
extern int bitindex;

extern void make_decode_tables(long scaleval);
extern int do_layer3(struct mp3frame *fr,unsigned char *, unsigned char *, int *);
extern int decode_header(struct mp3frame *fr,unsigned long newhead);
extern int decode_header_fast(struct mp3frame *fr,unsigned long newhead);

struct III_sideinfo
{
  unsigned main_data_begin;
  unsigned private_bits;
  struct {
    gr_info_s gr[2];
  } ch[2];
};

extern int synth_1to1 (Real *,int,unsigned char *, int *);
extern int synth_1to1_single (Real *, int, unsigned char *, int *);
extern int synth_1to1_8bit (Real *,int,unsigned char *,int *);
extern int synth_1to1_mono (Real *,unsigned char *, int *);
extern int synth_1to1_mono2stereo (Real *,unsigned char *,int *);
extern int synth_1to1_8bit_mono (Real *,unsigned char *,int *);
extern int synth_1to1_8bit_mono2stereo (Real *,unsigned char *,int *);

extern int synth_2to1 (Real *,int,unsigned char *,int *);
extern int synth_2to1_8bit (Real *,int,unsigned char *,int *);
extern int synth_2to1_mono (Real *,unsigned char *,int *);
extern int synth_2to1_mono2stereo (Real *,unsigned char *,int *);
extern int synth_2to1_8bit_mono (Real *,unsigned char *,int *);
extern int synth_2to1_8bit_mono2stereo (Real *,unsigned char *,int *);

extern int synth_4to1 (Real *,int,unsigned char *,int *);
extern int synth_4to1_8bit (Real *,int,unsigned char *,int *);
extern int synth_4to1_mono (Real *,unsigned char *,int *);
extern int synth_4to1_mono2stereo (Real *,unsigned char *,int *);
extern int synth_4to1_8bit_mono (Real *,unsigned char *,int *);
extern int synth_4to1_8bit_mono2stereo (Real *,unsigned char *,int *);

extern int synth_ntom (Real *,int,unsigned char *,int *);
extern int synth_ntom_8bit (Real *,int,unsigned char *,int *);
extern int synth_ntom_mono (Real *,unsigned char *,int *);
extern int synth_ntom_mono2stereo (Real *,unsigned char *,int *);
extern int synth_ntom_8bit_mono (Real *,unsigned char *,int *);
extern int synth_ntom_8bit_mono2stereo (Real *,unsigned char *,int *);

extern void rewindNbits(int bits);
extern int  hsstell(void);
extern int get_songlen(struct mp3frame *fr,int no);

extern void init_layer3(int);
extern void init_layer2(void);
extern void make_decode_tables(long scale);
extern void make_conv16to8_table(int);
extern void dct64(Real *,Real *,Real *);

extern void synth_ntom_set_step(long,long);

extern unsigned char *conv16to8;
extern long freqs[9];
extern Real muls[27][64];
extern Real decwin[512+32];
extern Real *pnts[5];

extern struct parameter param;

extern jmp_buf mp3jbuf;
