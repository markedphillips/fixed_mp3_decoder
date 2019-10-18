/* (c) 1998-2018 Mark Phillips */

#ifndef __DSP_H__
#define __DSP_H__

#include <string.h>
#include <stdlib.h>
#include "dspansi.h"
#include "dspcnst.h"
#include "dsptypes.h"
#include "dspfns.h"

/* transforms */

#ifdef __cplusplus
extern "C" {
#endif

_VOID _EXFUN (dsp_dfft2, (DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_ffft2, (FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qfft2, (QCMPLX *, QCMPLX*, int, int, int));
_VOID _EXFUN (dsp_dfft2_t, (DCMPLX *, DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_ffft2_t, (FCMPLX *, FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qfft2_t, (QCMPLX *, QCMPLX*, QCMPLX *, int, int, int));

_VOID _EXFUN (dsp_dfft2f, (DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_ffft2f, (FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qfft2f, (QCMPLX *, QCMPLX*, int, int, int));
_VOID _EXFUN (dsp_dfft2f_t, (DCMPLX *, DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_ffft2f_t, (FCMPLX *, FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qfft2f_t, (QCMPLX *, QCMPLX*, QCMPLX *, int, int, int));

_VOID _EXFUN (dsp_dtwinfft2, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, int, int));
_VOID _EXFUN (dsp_ftwinfft2, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, int, int));
_VOID _EXFUN (dsp_qtwinfft2, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, int, int));
_VOID _EXFUN (dsp_dtwinfft2_t, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int, int));
_VOID _EXFUN (dsp_ftwinfft2_t, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int, int));
_VOID _EXFUN (dsp_qtwinfft2_t, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int, int));
_VOID _EXFUN (dsp_drfft2, (DFLOAT *, DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_frfft2, (FFLOAT *, FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qrfft2, (QFIXED *, QCMPLX *, QCMPLX *, int, int, int));
_VOID _EXFUN (dsp_drfft2_t, (DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX * , int, int, int));
_VOID _EXFUN (dsp_frfft2_t, (FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX * , int, int, int));
_VOID _EXFUN (dsp_qrfft2_t, (QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int, int, int));
_VOID _EXFUN (dsp_drfftn2, (DFLOAT *, DCMPLX *, DCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_frfftn2, (FFLOAT *, FCMPLX *, FCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_qrfftn2, (QFIXED *, QCMPLX *, QCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_drfftn2_t, (DFLOAT *, DCMPLX *, DCMPLX **, DCMPLX * , int *, int, int, int));
_VOID _EXFUN (dsp_frfftn2_t, (FFLOAT *, FCMPLX *, FCMPLX **, FCMPLX * , int *, int, int, int));
_VOID _EXFUN (dsp_qrfftn2_t, (QFIXED *, QCMPLX *, QCMPLX **, QCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_dfftn2, (DCMPLX *, DCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_ffftn2, (FCMPLX *, FCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_qfftn2, (QCMPLX *, QCMPLX *, int *, int, int, int));
_VOID _EXFUN (dsp_dfftn2_t, (DCMPLX *, DCMPLX *, DCMPLX **, int *, int, int, int));
_VOID _EXFUN (dsp_ffftn2_t, (FCMPLX *, FCMPLX *, FCMPLX **, int *, int, int, int));
_VOID _EXFUN (dsp_qfftn2_t, (QCMPLX *, QCMPLX *, QCMPLX **, int *, int, int, int));
_VOID _EXFUN (dsp_drowtfft2, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_frowtfft2, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qrowtfft2, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, int, int, int));
_VOID _EXFUN (dsp_drowtfft2_t, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_frowtfft2_t, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qrowtfft2_t, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int, int, int));
_VOID _EXFUN (dsp_drowfft2, (DCMPLX *, DCMPLX *, int, int, int, int));
_VOID _EXFUN (dsp_frowfft2, (FCMPLX *, FCMPLX *, int, int, int, int));
_VOID _EXFUN (dsp_qrowfft2, (QCMPLX *, QCMPLX *, int, int, int, int));
_VOID _EXFUN (dsp_drowfft2_t, (DCMPLX *, DCMPLX *, DCMPLX *, int, int, int, int));
_VOID _EXFUN (dsp_frowfft2_t, (FCMPLX *, FCMPLX *, FCMPLX *, int, int, int, int));
_VOID _EXFUN (dsp_qrowfft2_t, (QCMPLX *, QCMPLX *, QCMPLX *, int, int, int, int));

_VOID _EXFUN (dsp_dfht, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, int, int, int));
_VOID _EXFUN (dsp_ffht, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qfht, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, int, int, int));

/* convolution */

_VOID _EXFUN (dsp_drconv, (DFLOAT *, int, DFLOAT *, int, DFLOAT *));
_VOID _EXFUN (dsp_frconv, (FFLOAT *, int, FFLOAT *, int, FFLOAT *));
_VOID _EXFUN (dsp_qrconv, (QFIXED *, int, QFIXED *, int, QFIXED *));
_VOID _EXFUN (dsp_drconv2, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_frconv2, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qrconv2, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_drconv2_t, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_frconv2_t, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qrconv2_t, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_drconvn2, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int *, int));
_VOID _EXFUN (dsp_frconvn2, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int *, int));
_VOID _EXFUN (dsp_qrconvn2, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int *, int));
_VOID _EXFUN (dsp_drconvn2_t, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, 
                               DCMPLX **, int *, int));
_VOID _EXFUN (dsp_frconvn2_t, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, 
                               FCMPLX **, int *, int));
_VOID _EXFUN (dsp_qrconvn2_t, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, 
                               QCMPLX **, int *, int));

/* correlation */
_VOID _EXFUN (dsp_drxcorr, (DFLOAT *, int, DFLOAT *, int, DFLOAT *));
_VOID _EXFUN (dsp_frxcorr, (FFLOAT *, int, FFLOAT *, int, FFLOAT *));
_VOID _EXFUN (dsp_qrxcorr, (QFIXED *, int, QFIXED *, int, QFIXED *));
_VOID _EXFUN (dsp_drcorr2, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_frcorr2, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qrcorr2, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_drcorr2_t, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_frcorr2_t, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qrcorr2_t, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_dracorr2, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_fracorr2, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qracorr2, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_dracorr2_t, (DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int));
_VOID _EXFUN (dsp_fracorr2_t, (FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int));
_VOID _EXFUN (dsp_qracorr2_t, (QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int));
_VOID _EXFUN (dsp_drcorrn2, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, int *, int));
_VOID _EXFUN (dsp_frcorrn2, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, int *, int));
_VOID _EXFUN (dsp_qrcorrn2, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, int *, int));
_VOID _EXFUN (dsp_drcorrn2_t, (DFLOAT *, DFLOAT *, DFLOAT *, DCMPLX *, DCMPLX *, DCMPLX *, 
                               DCMPLX **, int *, int));
_VOID _EXFUN (dsp_frcorrn2_t, (FFLOAT *, FFLOAT *, FFLOAT *, FCMPLX *, FCMPLX *, FCMPLX *, 
                               FCMPLX **, int *, int));
_VOID _EXFUN (dsp_qrcorrn2_t, (QFIXED *, QFIXED *, QFIXED *, QCMPLX *, QCMPLX *, QCMPLX *, 
                               QCMPLX **, int *, int));

/* filters */
DFLOAT _EXFUN (dsp_dfir, (DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffir, (FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfir, (QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_diir, (DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_fiir, (FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qiir, (QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dfirds, (DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirds, (FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfirds, (QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dfirus, (DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirus, (FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfirus, (QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dfirmr, (DFLOAT *, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirmr, (FFLOAT *, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfirmr, (QFIXED *, QFILTER_STATE *));
_VOID  _EXFUN (dsp_dabfir, (DFLOAT *, DFLOAT *, int, DFILTER_STATE *));
_VOID  _EXFUN (dsp_fabfir, (FFLOAT *, FFLOAT *, int, FFILTER_STATE *));
_VOID  _EXFUN (dsp_qabfir, (QFIXED *, QFIXED *, int, QFILTER_STATE *));
_VOID  _EXFUN (dsp_dbfir, (DFLOAT *, DFLOAT *, int, DFILTER_STATE *));
_VOID  _EXFUN (dsp_fbfir, (FFLOAT *, FFLOAT *, int, FFILTER_STATE *));
_VOID  _EXFUN (dsp_qbfir, (QFIXED *, QFIXED *, int, QFILTER_STATE *));
_VOID  _EXFUN (dsp_dbiir, (DFLOAT *, DFLOAT *, int, DFILTER_STATE *));
_VOID  _EXFUN (dsp_fbiir, (FFLOAT *, FFLOAT *, int, FFILTER_STATE *));
_VOID  _EXFUN (dsp_qbiir, (QFIXED *, QFIXED *, int, QFILTER_STATE *));
_VOID  _EXFUN (dsp_dsbfir, (DFLOAT *, DFLOAT *, int, DFILTER_STATE *));
_VOID  _EXFUN (dsp_fsbfir, (FFLOAT *, FFLOAT *, int, FFILTER_STATE *));
_VOID  _EXFUN (dsp_qsbfir, (QFIXED *, QFIXED *, int, QFILTER_STATE *));

/* adaptive filters */
DFLOAT _EXFUN (dsp_dfirlms, (DFLOAT, DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirlms, (FFLOAT, FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfirlms, (QFIXED, QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dfirnlms, (DFLOAT, DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirnlms, (FFLOAT, FFLOAT, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qfirnlms, (QFIXED, QFIXED, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dfirrls, (DFLOAT, DFLOAT, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_ffirrls, (FFLOAT, FFLOAT, FFILTER_STATE *));

/* narrowband/broadband array routines */
DFLOAT _EXFUN (dsp_dnbaslc, (DFLOAT *, DFILTER_STATE *));
FFLOAT _EXFUN (dsp_fnbaslc, (FFLOAT *, FFILTER_STATE *));
QFIXED _EXFUN (dsp_qnbaslc, (QFIXED *, QFILTER_STATE *));
DFLOAT _EXFUN (dsp_dbbarap, (DFLOAT *, DBBA_STATE *));
FFLOAT _EXFUN (dsp_fbbarap, (FFLOAT *, FBBA_STATE *));
QFIXED _EXFUN (dsp_qbbarap, (QFIXED *, QBBA_STATE *));

/* channel equalization */
_VOID _EXFUN (dsp_dcheqbinlms, (int, DCHEQ_STATE *));
_VOID _EXFUN (dsp_fcheqbinlms, (int, FCHEQ_STATE *));
_VOID _EXFUN (dsp_qcheqbinlms, (int, QCHEQ_STATE *));
int _EXFUN (dsp_dcheqrls, (int, DCHEQ_STATE *));
int _EXFUN (dsp_fcheqrls, (int, FCHEQ_STATE *));

/* vector/matrix operations */
_VOID _EXFUN (dsp_dmsqadd, (DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqadd, (FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqadd, (QFIXED *, QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsqcopy, (DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqcopy, (FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqcopy, (QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsqsub, (DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqsub,  (FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqsub, (QFIXED *, QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsq2mult, (DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsq2mult, (FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsq2mult, (QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsqTadd, (DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqTadd, (FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqTadd, (QFIXED *, QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsqTcopy, (DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqTcopy, (FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqTcopy, (QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsqTsub, (DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsqTsub,  (FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsqTsub, (QFIXED *, QFIXED *, QFIXED *, int, int));
_VOID _EXFUN (dsp_dmsq2Tmult, (DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, DFLOAT *, int, int));
_VOID _EXFUN (dsp_fmsq2Tmult, (FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, FFLOAT *, int, int));
_VOID _EXFUN (dsp_qmsq2Tmult, (QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, QFIXED *, int, int));
int _EXFUN (dsp_dmmult, (DFLOAT *, int, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fmmult, (FFLOAT *, int, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qmmult, (QFIXED *, int, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dmvmult, (DFLOAT *, int, int, DFLOAT *, int, DFLOAT *));
int _EXFUN (dsp_fmvmult, (FFLOAT *, int, int, FFLOAT *, int, FFLOAT *));
int _EXFUN (dsp_qmvmult, (QFIXED *, int, int, QFIXED *, int, QFIXED *));
int _EXFUN (dsp_dmTvmult, (DFLOAT *, int, int, DFLOAT *, int, DFLOAT *));
int _EXFUN (dsp_fmTvmult, (FFLOAT *, int, int, FFLOAT *, int, FFLOAT *));
int _EXFUN (dsp_qmTvmult, (QFIXED *, int, int, QFIXED *, int, QFIXED *));
DFLOAT _EXFUN (dsp_dvcnorm1, (DCMPLX *, DCMPLX *, int));
FFLOAT _EXFUN (dsp_fvcnorm1, (FCMPLX *, FCMPLX *, int));
QFIXED _EXFUN (dsp_qvcnorm1, (QCMPLX *, QCMPLX *, int));
int _EXFUN (dsp_dvmmult, (DFLOAT *, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fvmmult, (FFLOAT *, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qvmmult, (QFIXED *, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dvmTmult, (DFLOAT *, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fvmTmult, (FFLOAT *, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qvmTmult, (QFIXED *, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dmTmult, (DFLOAT *, int, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fmTmult, (FFLOAT *, int, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qmTmult, (QFIXED *, int, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dmTmultT, (DFLOAT *, int, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fmTmultT, (FFLOAT *, int, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qmTmultT, (QFIXED *, int, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dmmultT, (DFLOAT *, int, int, DFLOAT *, int, int, DFLOAT *));
int _EXFUN (dsp_fmmultT, (FFLOAT *, int, int, FFLOAT *, int, int, FFLOAT *));
int _EXFUN (dsp_qmmultT, (QFIXED *, int, int, QFIXED *, int, int, QFIXED *));
int _EXFUN (dsp_dmsqmult, (DFLOAT *, int, DFLOAT *, int, DFLOAT *, int));
int _EXFUN (dsp_fmsqmult, (FFLOAT *, int, FFLOAT *, int, FFLOAT *, int));
int _EXFUN (dsp_qmsqmult, (QFIXED *, int, QFIXED *, int, QFIXED *, int));
int _EXFUN (dsp_dmsqTmult, (DFLOAT *, int, DFLOAT *, int, DFLOAT *, int));
int _EXFUN (dsp_fmsqTmult, (FFLOAT *, int, FFLOAT *, int, FFLOAT *, int));
int _EXFUN (dsp_qmsqTmult, (QFIXED *, int, QFIXED *, int, QFIXED *, int));
int _EXFUN (dsp_dminv, (DFLOAT *, int, DFLOAT *, DFLOAT *));
int _EXFUN (dsp_fminv, (FFLOAT *, int, FFLOAT *, FFLOAT *));
int _EXFUN (dsp_dnsolve, (int, DFLOAT *));
int _EXFUN (dsp_fnsolve, (int, FFLOAT *));
DFLOAT _EXFUN (dsp_dmdet, (DFLOAT *, int));
FFLOAT _EXFUN (dsp_fmdet, (FFLOAT *, int));

/* encoding / decoding */
_VOID  _EXFUN (dsp_econvenc, (char *, char *, int, ENCODER_DECODER *));
_VOID  _EXFUN (dsp_epconvenc, (char *, char *, int, PUNCTURED_ENCODER_DECODER *));
_VOID  _EXFUN (dsp_eviterbi, (char *, char *, int, ENCODER_DECODER *));
_VOID  _EXFUN (dsp_epviterbi, (char *, char *, int, PUNCTURED_ENCODER_DECODER *));
int    _EXFUN (dsp_evitinit, (ENCODER_DECODER *, int, int, int, VITERBI_TABLE_ENTRY *,
			      VITERBI_NODE *, int, int, int, int));
_VOID  _EXFUN (dsp_efrspcoder, (char *, char *));
char   _EXFUN (dsp_epack, (char *));
_VOID  _EXFUN (dsp_eunpack, (char, char *));

/* compression/decompression */

#define	DSP_AUDIO_ENCODING_ULAW	  (1)	/* ISDN u-law */
#define	DSP_AUDIO_ENCODING_ALAW	  (2)	/* ISDN A-law */
#define	DSP_AUDIO_ENCODING_LINEAR (3)	/* PCM 2's-complement (0-center) */

_VOID _EXFUN (dsp_balaw2lin, (unsigned char *, short *, int));
_VOID _EXFUN (dsp_blin2alaw, (short *, unsigned char *, int));
_VOID _EXFUN (dsp_bulaw2lin, (unsigned char *, short *, int));
_VOID _EXFUN (dsp_blin2ulaw, (short *, unsigned char *, int));
_VOID _EXFUN (dsp_balaw2ulaw, (unsigned char *, unsigned char *, int));
_VOID _EXFUN (dsp_bulaw2alaw, (unsigned char *, unsigned char *, int));
short _EXFUN (dsp_alaw2lin, (unsigned char));
short _EXFUN (dsp_ulaw2lin, (unsigned char));
unsigned char _EXFUN (dsp_lin2alaw, (int));
unsigned char _EXFUN (dsp_lin2ulaw, (int));
unsigned char _EXFUN (dsp_alaw2ulaw, (unsigned char));
unsigned char _EXFUN (dsp_ulaw2alaw, (unsigned char));
_VOID _EXFUN (dsp_g72x_init_stat, (G72X_STATE *));
int   _EXFUN (dsp_g721_encoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g721_decoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_16_encoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_16_decoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_24_encoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_24_decoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_40_encoder, (int, int, G72X_STATE *));
int   _EXFUN (dsp_g723_40_decoder, (int, int, G72X_STATE *));

/* image */
_VOID  _EXFUN (dsp_dfwt22d, (DFLOAT *, DFLOAT *, int));
_VOID  _EXFUN (dsp_ffwt22d, (FFLOAT *, FFLOAT *, int));
_VOID  _EXFUN (dsp_qfwt22d, (QFIXED *, QFIXED *, int));

_VOID  _EXFUN (dsp_bhisteq, (IMAGE_BIT8_HISTOGRAM *, IMAGE_BIT8_MAP **, int));
int    _EXFUN (dsp_bhsi2rgb, (const IMAGE *, IMAGE *));
int    _EXFUN (dsp_bimgavg, (const IMAGE *, IMAGE *, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgcont, (const IMAGE *, IMAGE *, unsigned char, unsigned char, 
                              unsigned char, unsigned char, 
                              unsigned int, unsigned int));
int    _EXFUN (dsp_bimgedge, (const IMAGE *, IMAGE *, IMAGE_EDGE_DETECT_TYPE,
                              unsigned int, unsigned int));
int    _EXFUN (dsp_bimggamma, (const IMAGE *, IMAGE *, IMAGE_BIT8_MAP *,
                               unsigned int, unsigned int, double));
int    _EXFUN (dsp_bimghbf, (const IMAGE *, IMAGE *, unsigned int, unsigned int, unsigned int));
int    _EXFUN (dsp_bimgheq, (const IMAGE *, IMAGE *, unsigned int, unsigned int));
int    _EXFUN (dsp_bimgheql, (const IMAGE *, IMAGE *, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimghist, (const IMAGE *, IMAGE_BIT8_HISTOGRAM *, unsigned int, unsigned int));
int    _EXFUN (dsp_bimghpf, (const IMAGE *, IMAGE *, unsigned int, unsigned int));
int    _EXFUN (dsp_bimgmap, (const IMAGE *, IMAGE *, IMAGE_BIT8_MAP *, 
                             unsigned int, unsigned int));
int    _EXFUN (dsp_bimgmap2, (const IMAGE *, IMAGE *, IMAGE_BIT8_MAP **, 
                             unsigned int, unsigned int));
int    _EXFUN (dsp_bimgmask, (const IMAGE *, IMAGE *, IMAGE_MASK *, 
                              unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgmask2, (const IMAGE *, IMAGE *, IMAGE_MASK *, int, 
                               IMAGE_MASK_COMBINE_TYPE, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgmax, (const IMAGE *, IMAGE *, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgmedn, (const IMAGE *, IMAGE *, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgmin, (const IMAGE *, IMAGE *, unsigned int, unsigned int, int));
int    _EXFUN (dsp_bimgneg, (const IMAGE *, IMAGE *, unsigned int, unsigned int));
int    _EXFUN (dsp_bmapgamma, (IMAGE_BIT8_MAP *, double));
int    _EXFUN (dsp_brgb2cmy, (const IMAGE *, IMAGE *));
int    _EXFUN (dsp_brgb2cmyk, (const IMAGE *, IMAGE *));
int    _EXFUN (dsp_brgb2hsi, (const IMAGE *, IMAGE *));

int    _EXFUN (dsp_imaskadd, (IMAGE_MASK *, IMAGE_MASK *, int));
int    _EXFUN (dsp_imaskinit, (IMAGE_MASK *, int *, int, int));
_VOID  _EXFUN (dsp_imaskterm, (IMAGE_MASK *));
int    _EXFUN (dsp_imgcopy, (const IMAGE *, IMAGE *));
int    _EXFUN (dsp_imginit, (IMAGE *, IMAGE_FORMAT, IMAGE_PIXEL_TYPE, int, int, 
			     IMAGE_BORDER_TYPE, void *, void *));
_VOID  _EXFUN (dsp_imgterm, (IMAGE *));
int    _EXFUN (dsp_imgsubcpy, (const IMAGE *, IMAGE *));
int    _EXFUN (dsp_imgsubinit, (IMAGE *, int, int, int, int));

/* math */

DFLOAT _EXFUN (dsp_atan, (DFLOAT));
DFLOAT _EXFUN (dsp_sqrt, (DFLOAT));
DFLOAT _EXFUN (dsp_cos, (DFLOAT));
DFLOAT _EXFUN (dsp_sin, (DFLOAT));
_VOID  _EXFUN (dsp_dcsqrt, (DCMPLX, DCMPLX *));
QFIXED _EXFUN (dsp_qsqrt, (QFIXED));

/* type conversion routines */
double _EXFUN (dsp_qtod, (QFIXED));
QFIXED _EXFUN (dsp_dtoq, (double));

/* divide routines */
QFIXED _EXFUN (dsp_qdiv, (QFIXED, QFIXED));
QACC   _EXFUN (dsp_qdivl, (QFIXED, QFIXED));
QFIXED _EXFUN (dsp_qaccdiv, (QACC, QACC));
_VOID  _EXFUN (dsp_intdiv, (IDIVRESULT *, short, short));

/* trig functions */
QFIXED _EXFUN (dsp_qcos, (QFIXED));
QFIXED _EXFUN (dsp_qsin, (QFIXED));
QFIXED _EXFUN (dsp_qcosine, (QFIXED));
QFIXED _EXFUN (dsp_qsine, (QFIXED));

/* twiddle generator */
_VOID _EXFUN (dsp_qtwiddle, (QCMPLX *, int, int, int));
_VOID _EXFUN (dsp_qtwtable, (QCMPLX *, int, int));

/* windowing functions */
_VOID _EXFUN (dsp_dhamm, (DFLOAT *, DFLOAT *, int));
_VOID _EXFUN (dsp_dhann, (DFLOAT *, DFLOAT *, int));
_VOID _EXFUN (dsp_dblackman, (DFLOAT *, DFLOAT *, int));
_VOID _EXFUN (dsp_dwelch, (DFLOAT *, DFLOAT *, int));
_VOID _EXFUN (dsp_fhamm, (FFLOAT *, FFLOAT *, int));
_VOID _EXFUN (dsp_fhann, (FFLOAT *, FFLOAT *, int));
_VOID _EXFUN (dsp_fblackman, (FFLOAT *, FFLOAT *, int));
_VOID _EXFUN (dsp_fwelch, (FFLOAT *, FFLOAT *, int));
_VOID _EXFUN (dsp_qhamm, (QFIXED data[], QFIXED out[], int len));
_VOID _EXFUN (dsp_qhann, (QFIXED *data, QFIXED *out, int len));
_VOID _EXFUN (dsp_qblackman, (QFIXED data[], QFIXED out[], int len));
_VOID _EXFUN (dsp_qwelch, (QFIXED *data, QFIXED *out, int len));

/* coordinate transformations */
_VOID _EXFUN (dsp_drotatex, (DPOINT, DPOINT *, DFLOAT));
_VOID _EXFUN (dsp_drotatey, (DPOINT, DPOINT *, DFLOAT));
_VOID _EXFUN (dsp_drotatez, (DPOINT, DPOINT *, DFLOAT));
_VOID _EXFUN (dsp_frotatex, (FPOINT, FPOINT *, FFLOAT));
_VOID _EXFUN (dsp_frotatey, (FPOINT, FPOINT *, FFLOAT));
_VOID _EXFUN (dsp_frotatez, (FPOINT, FPOINT *, FFLOAT));
_VOID _EXFUN (dsp_qrotatex, (QPOINT, QPOINT *, QFIXED));
_VOID _EXFUN (dsp_qrotatey, (QPOINT, QPOINT *, QFIXED));
_VOID _EXFUN (dsp_qrotatez, (QPOINT, QPOINT *, QFIXED));
_VOID _EXFUN (dsp_dscale, (DPOINT, DPOINT *, DFLOAT));
_VOID _EXFUN (dsp_fscale, (FPOINT, FPOINT *, FFLOAT));
_VOID _EXFUN (dsp_qscale, (QPOINT, QPOINT *, int, int));
_VOID _EXFUN (dsp_dtranslt, (DPOINT, DPOINT *, DFLOAT, DFLOAT, DFLOAT));
_VOID _EXFUN (dsp_ftranslt, (FPOINT, FPOINT *, FFLOAT, FFLOAT, FFLOAT));
_VOID _EXFUN (dsp_qtranslt, (QPOINT, QPOINT *, QFIXED, QFIXED, QFIXED));
_VOID _EXFUN (dsp_dpolar, (DRECTCOORD, DPOLARCOORD *));
_VOID _EXFUN (dsp_drect, (DPOLARCOORD, DRECTCOORD *));
_VOID _EXFUN (dsp_fpolar, (FRECTCOORD, FPOLARCOORD *));
_VOID _EXFUN (dsp_frect, (FPOLARCOORD, FRECTCOORD *));

/* MPEG2 */
_VOID _EXFUN (dsp_mChkHdrs, (int, int));
_VOID _EXFUN (dsp_mClrVerifHdrs, (void));
_VOID _EXFUN (dsp_mDecMPEG1IntBlk, (int, int [], global_var *));
_VOID _EXFUN (dsp_mDecMPEG1NonIntBlk, (int, global_var *));
_VOID _EXFUN (dsp_mDecMPEG2IntBlk, (int, int [], global_var *));
_VOID _EXFUN (dsp_mDecMPEG2NonIntBlk, (int, global_var *));
_VOID _EXFUN (dsp_mDecPict, (int, int, global_var *));
_VOID _EXFUN (dsp_Dual_Prime_Arithmetic, (int [][2], int *, int, int, global_var
 *));
_VOID _EXFUN (dsp_mError, (char *));
_VOID _EXFUN (dsp_mFillBfr, (global_var *));
_VOID _EXFUN (dsp_mFlushBfr, (int, global_var *));
_VOID _EXFUN (dsp_mFlushBfr32, (global_var *));
_VOID _EXFUN (dsp_mFormPred, (int, int, MotionInfo *, global_var *));
_VOID _EXFUN (dsp_mFrmReord, (int, int, global_var *));
int _EXFUN (dsp_mGetChromaDCdctDiff, (global_var *));
int _EXFUN (dsp_mGetCodedBlkPtrn, (global_var *));
int _EXFUN (dsp_mGetHdr, (global_var *));
int _EXFUN (dsp_mGetLumaDCdctDiff, (global_var *));
int _EXFUN (dsp_GetMacrBlkAddrInc, (global_var *G));
int _EXFUN (dsp_mGetMacroblockType, (global_var *));
int _EXFUN (dsp_mGetMotionCode, (global_var *));
_VOID _EXFUN (dsp_mInitBfr, (global_var *));
_VOID _EXFUN (dsp_Initialize_Reference_IDCT, (void));
_VOID _EXFUN (dsp_Initialize_sFast_IDCT, (void));
_VOID _EXFUN (dsp_mInitG, (global_var *));
_VOID _EXFUN (dsp_mMarkerBit, (char *, global_var *));
_VOID _EXFUN (dsp_mMotionVect, (int *, int *r, int, int, int, int, int, global_var *));
_VOID _EXFUN (dsp_mMotionVects, (int [2][2][2], int [2], int [2][2], int, int,
 int, int, int, int, int, global_var *));
_VOID _EXFUN (dsp_NxtPckt, (global_var *));
_VOID _EXFUN (dsp_mNxtStCode, (global_var *));
_VOID _EXFUN (dsp_mOutLastFrmSeq, (int, global_var *));
_VOID _EXFUN (dsp_mPrintBits, (int, int, int));
_VOID _EXFUN (dsp_Reference_IDCT, (short *));
_VOID _EXFUN (dsp_sFast_IDCT, (short *));
int _EXFUN (dsp_mSliceHdr, (global_var *));
_VOID _EXFUN (dsp_mSpatPred, (global_var *));
_VOID _EXFUN (dsp_mSubFrmBfr, (int, int, global_var *));

/* MPEG audio */

_VOID _EXFUN (dsp_III_antialias, (double **, gr_info_s *));

int _EXFUN (dsp_III_get_scale_factors_1, (int *, gr_info_s *));
int _EXFUN (dsp_III_get_scale_factors_2, (int *, gr_info_s *, int));
_VOID _EXFUN (dsp_audio_capabilities, (audio_info_struct *));
int _EXFUN (dsp_audio_close, (audio_info_struct *));
_VOID _EXFUN (dsp_audio_flush, (int, audio_info_struct *));
_VOID _EXFUN (dsp_audio_info_struct_init, (audio_info_struct *));
int _EXFUN (dsp_audio_open, (audio_info_struct *ai));
int _EXFUN (dsp_get_songlen, (struct frame *, int));
_VOID _EXFUN (dsp_print_stat, (struct frame *, int, long, audio_info_struct *));
int _EXFUN (dsp_read_frame, (struct frame *));
_VOID _EXFUN (dsp_III_get_side_info_1, (III_sideinfo *,int, int, long, int));
_VOID _EXFUN (dsp_III_get_side_info_2, (III_sideinfo *, int, int, long, int));

/* MP3 audio */

typedef	struct	tagHippMPEGBitstream   tHippMPEGBitstream ;
typedef	tHippMPEGBitstream            *ptHippMPEGBitstream ;

struct tagHippMPEGBitstream
{
	char			*bufptr;
	unsigned int	bytesleft;
};


int _EXFUN (dsp_InitMP3, (struct mpstr *));
int _EXFUN (dsp_SynchMP3, (tHippMPEGBitstream *));
int _EXFUN (dsp_DecodeHeader, (struct mpstr *, tHippMPEGBitstream *, unsigned long *, unsigned long *, unsigned long *));
int _EXFUN (dsp_DecodeMP3, (struct mpstr *, tHippMPEGBitstream *, unsigned char *, unsigned char *, int, int *));
void _EXFUN (dsp_ExitMP3, (struct mpstr *));

extern int change_equalizer_setting(bool bEQOn, float fPreamp, float* fBands, int nBands);


/* macros */
#define dsp_vbrindex(vector, index, brtable) ( (vector)[brtable[index]] )

/* builtin functions */

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_eencoderinit)
/* initialize convolutional encoder */
static inline
_VOID
_DEFUN (dsp_eencoderinit, (encoder, n, k, m, cv, shifter),
        ENCODER_DECODER *encoder   _AND
        int              n         _AND
        int              k         _AND
        int              m         _AND
        long            *cv        _AND
        char            *shifter)
{
  encoder->n = n;
  encoder->k = k;
  encoder->v = m + 1;
  encoder->encoder_info.cv = (long unsigned int*)cv;
  encoder->encoder_info.shifter = shifter;
  memset (shifter, 0x00, m * k); 
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirinit)
/* initialize double FIR filter state */
static inline
int
_DEFUN (dsp_dfirinit, (fir_state, coeffs, len, buffer, buflen),
        DFILTER_STATE *fir_state _AND
        DFLOAT        *coeffs    _AND
        int            len       _AND
        DFLOAT        *buffer    _AND
        int            buflen)
{
  int min_len;

  fir_state->taps1 = coeffs;
  fir_state->taps1_len = len;
  min_len = 2 * len;
  fir_state->index = 0;
  fir_state->counter = 0;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  fir_state->mask = 0;
  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(DFLOAT));
      fir_state->buffer = buffer;
    }
  else
    {
      fir_state->buffer = (DFLOAT *)calloc (min_len, sizeof(DFLOAT));
      fir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
 
  return fir_state->buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirinit)
/* initialize float FIR filter state */
static inline
int
_DEFUN (dsp_ffirinit, (fir_state, coeffs, len, buffer, buflen),
        FFILTER_STATE  *fir_state _AND
        FFLOAT         *coeffs    _AND
        int             len       _AND
        FFLOAT         *buffer    _AND
        int             buflen)
{
  int min_len;

  fir_state->taps1 = coeffs;
  fir_state->taps1_len = len;
  min_len = 2 * len;
  fir_state->index = 0;
  fir_state->counter = 0;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  fir_state->mask = 0;
  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(FFLOAT));
      fir_state->buffer = buffer;
    }
  else
    {
      fir_state->buffer = (FFLOAT *)calloc (min_len, sizeof(FFLOAT));
      fir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
 
  return fir_state->buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirinit)
/* initialize FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirinit, (fir_state, coeffs, len, buffer, buflen),
        QFILTER_STATE *fir_state  _AND
        QFIXED        *coeffs     _AND
        int            len        _AND
        QFIXED        *buffer     _AND
        int            buflen)
{
  int min_len;

  fir_state->taps1 = coeffs;
  fir_state->taps1_len = len;
  min_len = 2 * len;
  fir_state->index = 0;
  fir_state->counter = 0;
  fir_state->mask = 0;
  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(QFIXED));
      fir_state->buffer = buffer;
    }
  else
    {
      fir_state->buffer = (QFIXED *)calloc (min_len, sizeof(QFIXED));
      fir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
 
  return fir_state->buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_diirinit)
/* initialize DFLOAT IIR filter state */
static inline
int
_DEFUN (dsp_diirinit, (iir_state, a_coeffs, a_len, b_coeffs, b_len, buffer, buflen),
        DFILTER_STATE *iir_state  _AND
        DFLOAT        *a_coeffs   _AND
        int            a_len      _AND
        DFLOAT        *b_coeffs   _AND
        int            b_len      _AND
        DFLOAT        *buffer     _AND
        int            buflen)
{
  int min_len;
  iir_state->taps1 = a_coeffs;
  iir_state->taps1_len = a_len;
  iir_state->taps2 = b_coeffs;
  iir_state->taps2_len = b_len;
  iir_state->mask = 0;

  /* calculate required size of double buffer */
  min_len = (a_len > b_len ? a_len << 1 : b_len << 1);

  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(DFLOAT));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
    }
  else
    {
      buffer = (DFLOAT *)calloc (min_len, sizeof(DFLOAT));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
      iir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }

  iir_state->index = 0;

  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fiirinit)
/* initialize float IIR filter state */
static inline
int
_DEFUN (dsp_fiirinit, (iir_state, a_coeffs, a_len, b_coeffs, b_len, buffer, buflen),
        FFILTER_STATE  *iir_state  _AND
        FFLOAT         *a_coeffs   _AND
        int             a_len      _AND
        FFLOAT         *b_coeffs   _AND
        int             b_len      _AND
        FFLOAT         *buffer     _AND
        int             buflen)
{
  int min_len;
  iir_state->taps1 = a_coeffs;
  iir_state->taps1_len = a_len;
  iir_state->taps2 = b_coeffs;
  iir_state->taps2_len = b_len;
  iir_state->mask = 0;

  /* calculate required size of double buffer */
  min_len = a_len > b_len ? a_len << 1 : b_len << 1;

  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(FFLOAT));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
    }
  else
    {
      buffer = (FFLOAT *)calloc (min_len, sizeof(FFLOAT));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
      iir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }

  iir_state->index = 0;

  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qiirinit)
/* initialize IIR qfilter state */
static inline
int
_DEFUN (dsp_qiirinit, (iir_state, a_coeffs, a_len, b_coeffs, b_len, buffer, buflen),
        QFILTER_STATE *iir_state  _AND
        QFIXED        *a_coeffs   _AND
        int            a_len      _AND
        QFIXED        *b_coeffs   _AND
        int            b_len      _AND
        QFIXED        *buffer     _AND
        int            buflen)
{
  int min_len;
  iir_state->taps1 = a_coeffs;
  iir_state->taps1_len = a_len;
  iir_state->taps2 = b_coeffs;
  iir_state->taps2_len = b_len; 
  iir_state->mask = 0;

  /* calculate required size of double buffer */
  min_len = a_len > b_len ? a_len << 1 : b_len << 1;
  
  if (buffer != NULL && buflen >= min_len)
    {
      memset (buffer, 0, min_len * sizeof(QFIXED));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
    }
  else
    {
      buffer = (QFIXED *)calloc (min_len, sizeof(QFIXED));
      iir_state->buffer = buffer;
      /* we only store half the size to avoid future calculations */
      iir_state->buflen = min_len >> 1;
      iir_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }

  iir_state->index = 0;

  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirlmsinit)
/* initialize Adaptive DFLOAT FIR filter state */
static inline
int
_DEFUN (dsp_dfirlmsinit, (fir_state, coeffs, len, buffer, buflen, beta),
        DFILTER_STATE *fir_state _AND
        DFLOAT        *coeffs    _AND
        int            len       _AND
        DFLOAT        *buffer    _AND
        int            buflen    _AND
        DFLOAT         beta)
{
  fir_state->beta = beta;
  return dsp_dfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirlmsinit)
/* initialize Adaptive float FIR filter state */
static inline
int
_DEFUN (dsp_ffirlmsinit, (fir_state, coeffs, len, buffer, buflen, beta),
        FFILTER_STATE  *fir_state _AND
        FFLOAT         *coeffs    _AND
        int             len       _AND
        FFLOAT         *buffer    _AND
	int             buflen    _AND
        FFLOAT          beta)
{
  fir_state->beta = beta;  
  return dsp_ffirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirlmsinit)
/* initialize Adaptive FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirlmsinit, (fir_state, coeffs, len, buffer, buflen, beta),
        QFILTER_STATE *fir_state  _AND
        QFIXED        *coeffs     _AND
        int            len        _AND
        QFIXED        *buffer     _AND
	int            buflen     _AND
        QFIXED         beta)
{
  fir_state->beta = beta;
  return dsp_qfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirnlmsinit)
/* initialize Adaptive DFLOAT FIR filter state */
static inline
int
_DEFUN (dsp_dfirnlmsinit, (nlms_state, coeffs, len, buffer, buflen, mu),
        DFILTER_STATE *nlms_state _AND
        DFLOAT        *coeffs     _AND
        int            len        _AND
        DFLOAT        *buffer     _AND
	int            buflen     _AND
        DFLOAT         mu)
{
  nlms_state->alpha = mu;
  nlms_state->temp = 0;
  return dsp_dfirinit (nlms_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirnlmsinit)
/* initialize Adaptive float FIR filter state */
static inline
int
_DEFUN (dsp_ffirnlmsinit, (nlms_state, coeffs, len, buffer, buflen, mu),
        FFILTER_STATE  *nlms_state _AND
        FFLOAT         *coeffs     _AND
        int             len        _AND
        FFLOAT         *buffer     _AND
	int             buflen     _AND
        FFLOAT          mu)
{
  nlms_state->alpha = mu;
  nlms_state->temp = 0;
  return dsp_ffirinit (nlms_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirnlmsinit)
/* initialize Adaptive FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirnlmsinit, (nlms_state, coeffs, len, buffer, buflen, mu),
        QFILTER_STATE *nlms_state _AND
        QFIXED        *coeffs     _AND
        int            len        _AND
        QFIXED        *buffer     _AND
	int            buflen     _AND
        QACC           mu)
{
  nlms_state->mu = mu;
  nlms_state->magn_sq = 0;
  return dsp_qfirinit (nlms_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirrlsinit)
/* initialize Adaptive DFLOAT RLS FIR filter state */
static inline
int
_DEFUN (dsp_dfirrlsinit, (rls_state, coeffs, len, buffer, buflen, vbuffer1,
                      vbuffer2, matrix, delta, gamma),
        DFILTER_STATE *rls_state _AND
        DFLOAT        *coeffs     _AND
        int            len        _AND
        DFLOAT        *buffer     _AND
        int            buflen     _AND
        DFLOAT        *vbuffer1   _AND
        DFLOAT        *vbuffer2   _AND
        DFLOAT        *matrix     _AND
        DFLOAT         delta      _AND
        DFLOAT         gamma)
{
  int i, rc;
  DFLOAT temp;
  DFLOAT *tmpbuf1 = NULL;
  DFLOAT *tmpbuf2 = NULL;
  DFLOAT *tmpbuf3 = NULL;
  DFLOAT *matrix_ptr;
  unsigned int mask;

  if (delta <= 0 || gamma <= 0)
    return 0;

  /* check if buffers need allocating */
  mask = 0;
  if (vbuffer1 == NULL)
    {
      tmpbuf1 = (DFLOAT*) malloc (len * sizeof(DFLOAT));
      vbuffer1 = tmpbuf1;
      mask |= DSP_VBUFFER1_ALLOC_MASK;
    }
  if (vbuffer2 == NULL)
    {
      tmpbuf2 = (DFLOAT*) malloc (len * sizeof(DFLOAT));
      vbuffer2 = tmpbuf2;
      mask |= DSP_VBUFFER1_ALLOC_MASK;
    }
  if (matrix == NULL)
    {
      tmpbuf3 = (DFLOAT*) malloc (len * len * sizeof(DFLOAT));
      matrix = tmpbuf3;
      mask |= DSP_MATRIX_ALLOC_MASK;
    }

  if (vbuffer1 == NULL || vbuffer2 == NULL || matrix == NULL)
    {
      free (tmpbuf1);
      free (tmpbuf2);
      free (tmpbuf3);
      return 0;
    }
  
  rls_state->vbuffer1 = vbuffer1;
  rls_state->vbuffer2 = vbuffer2;
  rls_state->matrix = matrix;
  rls_state->alpha = 1.0 / delta;

  /* initialize matrix to (1 / gamma) * Identity_matrix */
  temp = 1.0 / gamma;
  matrix_ptr = matrix;
  *matrix_ptr++ = temp;
  for (i = 0; i < len - 1; ++i) 
    {
      memset (matrix_ptr, 0, len * sizeof(DFLOAT));
      matrix_ptr += len;
      *matrix_ptr++ = temp;
    }

  rc = dsp_dfirinit (rls_state, coeffs, len, buffer, buflen);
  rls_state->mask |= mask;
  return rc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirrlsinit)
/* initialize Adaptive FFLOAT RLS FIR filter state */
static inline
int
_DEFUN (dsp_ffirrlsinit, (rls_state, coeffs, len, buffer, buflen, vbuffer1,
                      vbuffer2, matrix, delta, gamma),
        FFILTER_STATE *rls_state _AND
        FFLOAT        *coeffs     _AND
        int            len        _AND
        FFLOAT        *buffer     _AND
        int            buflen     _AND
        FFLOAT        *vbuffer1   _AND
        FFLOAT        *vbuffer2   _AND
        FFLOAT        *matrix     _AND
        FFLOAT         delta      _AND
        FFLOAT         gamma)
{
  int i, rc;
  FFLOAT temp;
  FFLOAT *matrix_ptr;
  FFLOAT *tmpbuf1 = NULL;
  FFLOAT *tmpbuf2 = NULL;
  FFLOAT *tmpbuf3 = NULL;
  unsigned int mask;

  if (delta <= 0 || gamma <= 0)
    return 0;

  /* check if buffers need allocating */
  mask = 0;
  if (vbuffer1 == NULL)
    {
      tmpbuf1 = (FFLOAT*) malloc (len * sizeof(FFLOAT));
      vbuffer1 = tmpbuf1;
      mask |= DSP_VBUFFER1_ALLOC_MASK;
    }
  if (vbuffer2 == NULL)
    {
      tmpbuf2 = (FFLOAT*) malloc (len * sizeof(FFLOAT));
      vbuffer2 = tmpbuf2;
      mask |= DSP_VBUFFER2_ALLOC_MASK;
    }
  if (matrix == NULL)
    {
      tmpbuf3 = (FFLOAT*) malloc (len * len * sizeof(FFLOAT));
      matrix = tmpbuf3;
      mask |= DSP_MATRIX_ALLOC_MASK;
    }

  if (vbuffer1 == NULL || vbuffer2 == NULL || matrix == NULL)
    {
      free (tmpbuf1);
      free (tmpbuf2);
      free (tmpbuf3);
      return 0;
    }
  
  rls_state->vbuffer1 = vbuffer1;
  rls_state->vbuffer2 = vbuffer2;
  rls_state->matrix = matrix;
  rls_state->alpha = 1.0 / delta;

  /* initialize matrix to (1 / gamma) * Identity_matrix */
  temp = 1.0 / gamma;
  matrix_ptr = matrix;
  *matrix_ptr++ = temp;
  for (i = 0; i < len - 1; ++i) 
    {
      memset (matrix_ptr, 0, len * sizeof(FFLOAT));
      matrix_ptr += len;
      *matrix_ptr++ = temp;
    }

  rc = dsp_ffirinit (rls_state, coeffs, len, buffer, buflen);
  rls_state->mask |= mask;
  return rc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dslcinit)
/* initialize DFLOAT narrowband array sidelobe canceller state */
static inline
int
_DEFUN (dsp_dslcinit, (slc_state, coeffs, coeff_buffer, len, buffer, buflen, alpha, beta),
        DFILTER_STATE *slc_state    _AND
        DFLOAT        *coeffs       _AND
	DFLOAT        *coeff_buffer _AND
        int            len          _AND
        DFLOAT        *buffer       _AND
	DFLOAT         buflen       _AND
        DFLOAT         alpha        _AND
        DFLOAT         beta)
{
  unsigned int mask = 0;
  int rc;

  slc_state->taps2 = coeffs;
  if (coeff_buffer == NULL)
    {
      coeff_buffer = (DFLOAT*) malloc (sizeof(DFLOAT) * len);
      if (coeff_buffer == NULL)
        return 0;
      mask |= DSP_TAPS1_ALLOC_MASK;
    }
  memcpy (coeff_buffer, coeffs, sizeof(DFLOAT) * len);
  slc_state->alpha = alpha;
  slc_state->beta = beta;
  rc = dsp_dfirinit (slc_state, coeff_buffer, len, buffer, buflen);
  slc_state->mask |= mask;
  return rc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fslcinit)
/* initialize FFLOAT narrowband array sidelobe canceller state */
static inline
int
_DEFUN (dsp_fslcinit, (slc_state, coeffs, coeff_buffer, len, buffer, buflen, alpha, beta),
        FFILTER_STATE *slc_state    _AND
        FFLOAT        *coeffs       _AND
	FFLOAT        *coeff_buffer _AND
        int            len          _AND
        FFLOAT        *buffer       _AND
	int            buflen       _AND
        FFLOAT         alpha        _AND
        FFLOAT         beta)
{
  int rc;
  unsigned int mask = 0;

  slc_state->taps2 = coeffs;
  if (coeff_buffer == NULL)
    {
      coeff_buffer = (FFLOAT*) malloc (sizeof(FFLOAT) * len);
      if (coeff_buffer == NULL)
        return 0;
      mask |= DSP_TAPS1_ALLOC_MASK;
    }
  memcpy (coeff_buffer, coeffs, sizeof(FFLOAT) * len);
  slc_state->alpha = alpha;
  slc_state->beta = beta;
  rc = dsp_ffirinit (slc_state, coeff_buffer, len, buffer, buflen);
  slc_state->mask |= mask;
  return rc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qslcinit)
/* initialize QFIXED narrowband array sidelobe canceller state */
static inline
int
_DEFUN (dsp_qslcinit, (slc_state, coeffs, coeff_buffer, len, buffer, buflen, alpha, beta),
        QFILTER_STATE *slc_state    _AND
        QFIXED        *coeffs       _AND
	QFIXED        *coeff_buffer _AND
        int            len          _AND
        QFIXED        *buffer       _AND
	int            buflen       _AND
        QFIXED         alpha        _AND
        QFIXED         beta)
{
  int rc;
  unsigned int mask = 0;

  slc_state->taps2 = coeffs;
  if (coeff_buffer == NULL)
    {
      coeff_buffer = (QFIXED*) malloc (sizeof(QFIXED) * len);
      if (coeff_buffer == NULL)
        return 0;
      mask |= DSP_TAPS1_ALLOC_MASK;
    }
  memcpy (coeff_buffer, coeffs, sizeof(QFIXED) * len);
  slc_state->alpha = alpha;
  slc_state->beta = beta;
  rc = dsp_qfirinit (slc_state, coeff_buffer, len, buffer, buflen);
  slc_state->mask |= mask;
  return rc;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dcheqbinlmsinit)
/* initialize DFLOAT channel equalizer that uses BINLMS algorithm */
static inline
int
_DEFUN (dsp_dcheqbinlmsinit, (cheq_state, fir_filter, coeffs, len,
			  buffer, buflen, desired_results, 
                          desired_results_len, inputs, mu),
        DCHEQ_STATE      *cheq_state          _AND
	DFILTER_STATE   **fir_filter          _AND
	DFLOAT           *coeffs              _AND
	int               len                 _AND
	DFLOAT           *buffer              _AND
	int               buflen              _AND
        DFLOAT           *desired_results     _AND
        int               desired_results_len _AND
        DFLOAT           *inputs              _AND
        DFLOAT            mu)
{
  cheq_state->desired_results = desired_results;
  cheq_state->desired_len = desired_results_len;
  cheq_state->inputs = inputs;
  cheq_state->mask = 0;
  if (*fir_filter == NULL)
    {
      *fir_filter = (DFILTER_STATE *) malloc (sizeof(DFILTER_STATE));
      if (*fir_filter == NULL)
        return 0;
      cheq_state->mask |= DSP_FILTER_ALLOC_MASK;
    }

  cheq_state->filter = *fir_filter;
  dsp_dfirinit (*fir_filter, coeffs, len, buffer, buflen);
  (*fir_filter)->alpha = mu;

  return 1;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fcheqbinlmsinit)
/* initialize FFLOAT channel equalizer that uses BINLMS algorithm */
static inline
int
_DEFUN (dsp_fcheqbinlmsinit, (cheq_state, fir_filter, coeffs, len,
			  buffer, buflen, desired_results, 
                          desired_results_len, inputs, mu),
        FCHEQ_STATE      *cheq_state          _AND
	FFILTER_STATE   **fir_filter          _AND
	FFLOAT           *coeffs              _AND
	int               len                 _AND
	FFLOAT           *buffer              _AND
	int               buflen              _AND
        FFLOAT           *desired_results     _AND
        int               desired_results_len _AND
        FFLOAT           *inputs              _AND
        FFLOAT            mu)
{
  cheq_state->desired_results = desired_results;
  cheq_state->desired_len = desired_results_len;
  cheq_state->inputs = inputs;
  cheq_state->mask = 0;
  if (*fir_filter == NULL)
    {
      *fir_filter = (FFILTER_STATE *) malloc (sizeof(FFILTER_STATE));
      if (*fir_filter == NULL)
        return 0;
      cheq_state->mask |= DSP_FILTER_ALLOC_MASK;
    }

  cheq_state->filter = *fir_filter;
  dsp_ffirinit (*fir_filter, coeffs, len, buffer, buflen);
  (*fir_filter)->alpha = mu;

  return 1;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcheqbinlmsinit)
/* initialize QFIXED channel equalizer that uses BINLMS algorithm */
static inline
int
_DEFUN (dsp_qcheqbinlmsinit, (cheq_state, fir_filter, coeffs, len,
			  buffer, buflen, desired_results, 
                          desired_results_len, inputs, mu),
        QCHEQ_STATE      *cheq_state          _AND
	QFILTER_STATE   **fir_filter          _AND
	QFIXED           *coeffs              _AND
	int               len                 _AND
	QFIXED           *buffer              _AND
	int               buflen              _AND
        QFIXED           *desired_results     _AND
        int               desired_results_len _AND
        QFIXED           *inputs              _AND
        QACC              mu)
{
  cheq_state->desired_results = desired_results;
  cheq_state->desired_len = desired_results_len;
  cheq_state->inputs = inputs;
  cheq_state->mask = 0;
  if (*fir_filter == NULL)
    {
      *fir_filter = (QFILTER_STATE *) malloc (sizeof(QFILTER_STATE));
      if (*fir_filter == NULL)
        return 0;
      cheq_state->mask |= DSP_FILTER_ALLOC_MASK;
    }

  cheq_state->filter = *fir_filter;
  dsp_qfirinit (*fir_filter, coeffs, len, buffer, buflen);
  (*fir_filter)->mu = mu;

  return 1;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dcheqrlsinit)
/* initialize DFLOAT channel equalizer that uses RLS algorithm */
static inline
int
_DEFUN (dsp_dcheqrlsinit, (cheq_state, fir_filter, coeffs, len, buffer, buflen,
		       vbuffer1, vbuffer2, matrix, delta, gamma,
		       desired_results, desired_results_len, inputs),
        DCHEQ_STATE      *cheq_state          _AND
	DFILTER_STATE   **fir_filter          _AND
	DFLOAT           *coeffs              _AND
        int               len                 _AND
	DFLOAT           *buffer              _AND
	int               buflen              _AND
        DFLOAT           *vbuffer1            _AND
        DFLOAT           *vbuffer2            _AND
        DFLOAT           *matrix              _AND
        DFLOAT            delta               _AND
        DFLOAT            gamma               _AND
        DFLOAT           *desired_results     _AND
        int               desired_results_len _AND
        DFLOAT           *inputs)
{
  cheq_state->desired_results = desired_results;
  cheq_state->desired_len = desired_results_len;
  cheq_state->inputs = inputs;

  if (*fir_filter == NULL)
    {
      *fir_filter = (DFILTER_STATE *) malloc (sizeof(DFILTER_STATE));
      if (*fir_filter == NULL)
        return 0;
      cheq_state->mask |= DSP_FILTER_ALLOC_MASK;
    }

  cheq_state->filter = *fir_filter;

  return dsp_dfirrlsinit (*fir_filter, coeffs, len, buffer, buflen, vbuffer1,
                      vbuffer2, matrix, delta, gamma);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fcheqrlsinit)
/* initialize FFLOAT channel equalizer that uses RLS algorithm */
static inline
int
_DEFUN (dsp_fcheqrlsinit, (cheq_state, fir_filter, coeffs, len, buffer, buflen,
		       vbuffer1, vbuffer2, matrix, delta, gamma,
		       desired_results, desired_results_len, inputs),
        FCHEQ_STATE      *cheq_state          _AND
	FFILTER_STATE   **fir_filter          _AND
	FFLOAT           *coeffs              _AND
        int               len                 _AND
	FFLOAT           *buffer              _AND
	int               buflen              _AND
        FFLOAT           *vbuffer1            _AND
        FFLOAT           *vbuffer2            _AND
        FFLOAT           *matrix              _AND
        FFLOAT            delta               _AND
        FFLOAT            gamma               _AND
        FFLOAT           *desired_results     _AND
        int               desired_results_len _AND
        FFLOAT           *inputs)
{
  cheq_state->desired_results = desired_results;
  cheq_state->desired_len = desired_results_len;
  cheq_state->inputs = inputs;

  if (*fir_filter == NULL)
    {
      *fir_filter = (FFILTER_STATE *) malloc (sizeof(FFILTER_STATE));
      if (*fir_filter == NULL)
        return 0;
      cheq_state->mask |= DSP_FILTER_ALLOC_MASK;
    }

  cheq_state->filter = *fir_filter;

  return dsp_ffirrlsinit (*fir_filter, coeffs, len, buffer, buflen, vbuffer1,
                      vbuffer2, matrix, delta, gamma);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dbbarapinit)
/* initialize DFLOAT broadband array RAP processor */
static inline
int
_DEFUN (dsp_dbbarapinit, (bba_state, num_sensors, desired_taps, desired_taps_len, 
                      weights, buffer, buflen, mu),
        DBBA_STATE    *bba_state        _AND
        int            num_sensors      _AND
        DFLOAT        *desired_taps     _AND
	int            desired_taps_len _AND
        DFLOAT        *weights          _AND
        DFLOAT        *buffer           _AND
	int            buflen           _AND
        DFLOAT         mu)
{
  int num_weights;

  bba_state->weights = weights;
  num_weights = desired_taps_len * num_sensors;
  bba_state->weights_len = num_weights;
  bba_state->mask = 0;
  if (buffer == NULL)
    {
      buffer = (DFLOAT*) calloc (num_weights, sizeof(DFLOAT));
      buflen = num_weights;
      bba_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
  bba_state->buffer = buffer;
  bba_state->buflen = buflen - (buflen % num_sensors);
  bba_state->desired_taps = desired_taps;
  bba_state->num_sensors = num_sensors;
  bba_state->num_desired_taps = desired_taps_len;
  bba_state->mu = mu;
  bba_state->index = 0;
  bba_state->counter = 0;
  
  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fbbarapinit)
/* initialize FFLOAT broadband array RAP processor */
static inline
int
_DEFUN (dsp_fbbarapinit, (bba_state, num_sensors, desired_taps, desired_taps_len, 
                      weights, buffer, buflen, mu),
        FBBA_STATE    *bba_state        _AND
        int            num_sensors      _AND
        FFLOAT        *desired_taps     _AND
	int            desired_taps_len _AND
        FFLOAT        *weights          _AND
        FFLOAT        *buffer           _AND
	int            buflen           _AND
        FFLOAT         mu)
{
  int num_weights;

  bba_state->weights = weights;
  num_weights = desired_taps_len * num_sensors;
  bba_state->weights_len = num_weights;
  bba_state->mask = 0;
  if (buffer == NULL)
    {
      buffer = (FFLOAT*) calloc (num_weights, sizeof(FFLOAT));
      buflen = num_weights;
      bba_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
  bba_state->buffer = buffer;
  bba_state->buflen = buflen - (buflen % num_sensors);
  bba_state->desired_taps = desired_taps;
  bba_state->num_sensors = num_sensors;
  bba_state->num_desired_taps = desired_taps_len;
  bba_state->mu = mu;
  bba_state->index = 0;
  bba_state->counter = 0;

  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qbbarapinit)
/* initialize QFIXED broadband array RAP processor */
static inline
int
_DEFUN (dsp_qbbarapinit, (bba_state, num_sensors, desired_taps, desired_taps_len, 
                      weights, buffer, buflen, mu),
        QBBA_STATE    *bba_state        _AND
        int            num_sensors      _AND
        QFIXED        *desired_taps     _AND
	int            desired_taps_len _AND
        QFIXED        *weights          _AND
        QFIXED        *buffer           _AND
	int            buflen           _AND
        QFIXED         mu)
{
  int num_weights;

  bba_state->weights = weights;
  num_weights = desired_taps_len * num_sensors;
  bba_state->weights_len = num_weights;
  bba_state->mask = 0;
  if (buffer == NULL)
    {
      buffer = (QFIXED*) calloc (num_weights, sizeof(QFIXED));
      buflen = num_weights;
      bba_state->mask |= DSP_BUFFER_ALLOC_MASK;
    }
  bba_state->buffer = buffer;
  bba_state->buflen = buflen - (buflen % num_sensors);
  bba_state->desired_taps = desired_taps;
  bba_state->num_sensors = num_sensors;
  bba_state->num_desired_taps = desired_taps_len;
  bba_state->mu = mu;
  bba_state->index = 0;
  bba_state->counter = 0;

  return buffer != NULL;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirdsinit)
/* initialize downsampling DFLOAT FIR filter state */
static inline
int
_DEFUN (dsp_dfirdsinit, (fir_state, coeffs, len, buffer, buflen, decimation),
        DFILTER_STATE *fir_state _AND
        DFLOAT        *coeffs    _AND
        int            len       _AND
        DFLOAT        *buffer    _AND
        int            buflen    _AND
        int            decimation)
{
  fir_state->decimation = decimation;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_dfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirdsinit)
/* initialize downsampling float FIR filter state */
static inline
int
_DEFUN (dsp_ffirdsinit, (fir_state, coeffs, len, buffer, buflen, decimation),
        FFILTER_STATE  *fir_state _AND
        FFLOAT         *coeffs    _AND
        int             len       _AND
        FFLOAT         *buffer    _AND
        int             buflen    _AND
        int             decimation)
 {
  fir_state->decimation = decimation;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_ffirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirdsinit)
/* initialize downsampling FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirdsinit, (fir_state, coeffs, len, buffer, buflen, decimation),
        QFILTER_STATE *fir_state _AND
        QFIXED        *coeffs    _AND
        int            len       _AND
        QFIXED        *buffer    _AND
        int            buflen    _AND
        int            decimation)
{
  fir_state->decimation = decimation;
  fir_state->val = 0;
  fir_state->temp = 0;
  return dsp_qfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirusinit)
/* initialize upsampling DFLOAT FIR filter state */
static inline
int
_DEFUN (dsp_dfirusinit, (fir_state, coeffs, len, buffer, buflen, interpolation),
        DFILTER_STATE *fir_state _AND
        DFLOAT        *coeffs    _AND
        int            len       _AND
        DFLOAT        *buffer    _AND
        int            buflen    _AND
        int            interpolation)
{
  fir_state->interpolation = interpolation;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_dfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirusinit)
/* initialize upsampling float FIR filter state */
static inline
int
_DEFUN (dsp_ffirusinit, (fir_state, coeffs, len, buffer, buflen, interpolation),
        FFILTER_STATE  *fir_state _AND
        FFLOAT         *coeffs    _AND
        int             len       _AND
        FFLOAT         *buffer    _AND
        int             buflen    _AND
        int             interpolation)
{
  fir_state->interpolation = interpolation;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_ffirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirusinit)
/* initialize upsampling FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirusinit, (fir_state, coeffs, len, buffer, buflen, interpolation),
        QFILTER_STATE *fir_state _AND
        QFIXED        *coeffs    _AND
        int            len       _AND
        QFIXED        *buffer    _AND
        int            buflen    _AND
        int            interpolation)
{
  fir_state->interpolation = interpolation;
  fir_state->val = 0;
  fir_state->temp = 0;
  return dsp_qfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfirmrinit)
/* initialize multi-rate DFLOAT FIR filter state */
static inline
int
_DEFUN (dsp_dfirmrinit, (fir_state, coeffs, len, buffer, buflen, interpolation, decimation),
        DFILTER_STATE *fir_state     _AND
        DFLOAT        *coeffs        _AND
        int            len           _AND
        DFLOAT        *buffer        _AND
        int            buflen        _AND
        int            interpolation _AND
        int            decimation)
{
  fir_state->interpolation = interpolation;
  fir_state->decimation = decimation;
  fir_state->items_needed = 1;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_dfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffirmrinit)
/* initialize multi-rate float FIR filter state */
static inline
int
_DEFUN (dsp_ffirmrinit, (fir_state, coeffs, len, buffer, buflen, interpolation, decimation),
        FFILTER_STATE  *fir_state     _AND
        FFLOAT         *coeffs        _AND
        int             len           _AND
        FFLOAT         *buffer        _AND
        int             buflen        _AND
        int             interpolation _AND
        int             decimation)
{
  fir_state->interpolation = interpolation;
  fir_state->decimation = decimation;
  fir_state->items_needed = 1;
  fir_state->val = 0.0;
  fir_state->temp = 0.0;
  return dsp_ffirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfirmrinit)
/* initialize multi-rate FIR qfilter state */
static inline
int
_DEFUN (dsp_qfirmrinit, (fir_state, coeffs, len, buffer, buflen, interpolation, decimation),
        QFILTER_STATE *fir_state     _AND
        QFIXED        *coeffs        _AND
        int            len           _AND
        QFIXED        *buffer        _AND
        int            buflen        _AND
        int            interpolation _AND
        int            decimation)
{
  fir_state->interpolation = interpolation;
  fir_state->decimation = decimation;
  fir_state->items_needed = 1;
  fir_state->val = 0;
  fir_state->temp = 0;
  return dsp_qfirinit (fir_state, coeffs, len, buffer, buflen);
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dfilterterm)
/* terminate DFLOAT filter state */
static inline
_VOID
_DEFUN (dsp_dfilterterm, (filter_state),
	DFILTER_STATE *filter_state)
{
  if (filter_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (filter_state->buffer);
      filter_state->buffer = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER1_ALLOC_MASK)
    {
      free (filter_state->vbuffer1);
      filter_state->vbuffer1 = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER2_ALLOC_MASK)
    {
      free (filter_state->vbuffer2);
      filter_state->vbuffer2 = NULL;
    }

  if (filter_state->mask & DSP_MATRIX_ALLOC_MASK)
    {
      free (filter_state->matrix);
      filter_state->matrix = NULL;
    }

  if (filter_state->mask & DSP_TAPS1_ALLOC_MASK)
    {
      free (filter_state->taps1);
      filter_state->taps1 = NULL;
    }

  filter_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_ffilterterm)
/* terminate FFLOAT filter state */
static inline
_VOID
_DEFUN (dsp_ffilterterm, (filter_state),
	FFILTER_STATE *filter_state)
{
  if (filter_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (filter_state->buffer);
      filter_state->buffer = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER1_ALLOC_MASK)
    {
      free (filter_state->vbuffer1);
      filter_state->vbuffer1 = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER2_ALLOC_MASK)
    {
      free (filter_state->vbuffer2);
      filter_state->vbuffer2 = NULL;
    }

  if (filter_state->mask & DSP_MATRIX_ALLOC_MASK)
    {
      free (filter_state->matrix);
      filter_state->matrix = NULL;
    }

  if (filter_state->mask & DSP_TAPS1_ALLOC_MASK)
    {
      free (filter_state->taps1);
      filter_state->taps1 = NULL;
    }

  filter_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qfilterterm)
/* terminate QFIXED filter state */
static inline
_VOID
_DEFUN (dsp_qfilterterm, (filter_state),
	QFILTER_STATE *filter_state)
{
  if (filter_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (filter_state->buffer);
      filter_state->buffer = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER1_ALLOC_MASK)
    {
      free (filter_state->vbuffer1);
      filter_state->vbuffer1 = NULL;
    }

  if (filter_state->mask & DSP_VBUFFER2_ALLOC_MASK)
    {
      free (filter_state->vbuffer2);
      filter_state->vbuffer2 = NULL;
    }

  if (filter_state->mask & DSP_MATRIX_ALLOC_MASK)
    {
      free (filter_state->matrix);
      filter_state->matrix = NULL;
    }

  if (filter_state->mask & DSP_TAPS1_ALLOC_MASK)
    {
      free (filter_state->taps1);
      filter_state->taps1 = NULL;
    }

  filter_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dcheqterm)
/* terminate DFLOAT channel equalizer state */
static inline
_VOID
_DEFUN (dsp_dcheqterm, (cheq_state),
	DCHEQ_STATE *cheq_state)
{
  dsp_dfilterterm (cheq_state->filter);
  if (cheq_state->mask & DSP_FILTER_ALLOC_MASK)
    {
      free (cheq_state->filter);
      cheq_state->filter = NULL;
    }
  cheq_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fcheqterm)
/* terminate FFLOAT channel equalizer state */
static inline
_VOID
_DEFUN (dsp_fcheqterm, (cheq_state),
	FCHEQ_STATE *cheq_state)
{
  dsp_ffilterterm (cheq_state->filter);
  if (cheq_state->mask & DSP_FILTER_ALLOC_MASK)
    {
      free (cheq_state->filter);
      cheq_state->filter = NULL;
    }
  cheq_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qcheqterm)
/* terminate QFIXED channel equalizer state */
static inline
_VOID
_DEFUN (dsp_qcheqterm, (cheq_state),
	QCHEQ_STATE *cheq_state)
{
  dsp_qfilterterm (cheq_state->filter);
  if (cheq_state->mask & DSP_FILTER_ALLOC_MASK)
    {
      free (cheq_state->filter);
      cheq_state->filter = NULL;
    }
  cheq_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_dbbaterm)
/* terminate DFLOAT broadband array processor state */
static inline
_VOID
_DEFUN (dsp_dbbaterm, (bba_state),
	DBBA_STATE *bba_state)
{
  if (bba_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (bba_state->buffer);
      bba_state->buffer = NULL;
    }
  bba_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_fbbaterm)
/* terminate FFLOAT broadband array processor state */
static inline
_VOID
_DEFUN (dsp_fbbaterm, (bba_state),
	FBBA_STATE *bba_state)
{
  if (bba_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (bba_state->buffer);
      bba_state->buffer = NULL;
    }
  bba_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_qbbaterm)
/* terminate QFIXED broadband array processor state */
static inline
_VOID
_DEFUN (dsp_qbbaterm, (bba_state),
	QBBA_STATE *bba_state)
{
  if (bba_state->mask & DSP_BUFFER_ALLOC_MASK)
    {
      free (bba_state->buffer);
      bba_state->buffer = NULL;
    }
  bba_state->mask = 0;
}
#endif

#if !defined(FINE_GRAINED_LIBRARIES) || defined(D_dsp_brgbinit)
static inline
int
_DEFUN (dsp_brgbinit, (image, rows, cols, border_type, pixels),
	IMAGE               *image       _AND
        int                  rows        _AND
        int                  cols        _AND
	IMAGE_BORDER_TYPE    border_type _AND
        void                *pixels)
{
  return dsp_imginit (image, IMAGE_RGB, IMAGE_BIT8, rows, cols, border_type, NULL, pixels);
}
#endif

#ifdef __cplusplus
};  // extern "C"
#endif


#endif /* #ifndef __DSP_H__ */
