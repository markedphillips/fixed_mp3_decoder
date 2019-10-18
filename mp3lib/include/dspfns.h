/* (c) 1998-2018 Mark Phillips */

#ifndef __DSPFNS_H__
#define __DSPFNS_H__

#ifdef FLOAT

/* types */
#define DFLOAT FFLOAT
#define DFILTER_STATE FFILTER_STATE
#define DBBA_STATE FBBA_STATE
#define DCHEQ_STATE FCHEQ_STATE
#define DNLMS_STATE FNLMS_STATE
#define DRLS_STATE FRLS_STATE
#define DCMPLX FCMPLX
#define DPOINT FPOINT
#define DPOLARCOORD FPOLARCOORD
#define DRECTCOORD FRECTCOORD

/*
#define sin sinf
#define cos cosf
*/

#define dsp_dabfir dsb_fabfir
#define dsp_dbbarap dsp_fbbarap
#define dsp_dbfir dsb_fbfir
#define dsp_dbiir dsb_fbiir
#define dsp_dcheqbinlms dsp_fcheqbinlms
#define dsp_dcheqrls dsp_fcheqrls
#define dsp_dfir dsp_ffir
#define dsp_dfirds dsp_ffirds
#define dsp_dfirlms dsp_ffirlms
#define dsp_dfirmr dsp_ffirmr
#define dsp_dfirnlms dsp_ffirnlms
#define dsp_dfirrls dsp_ffirrls
#define dsp_dfirus dsp_ffirus
#define dsp_diir dsp_fiir
#define dsp_dnbaslc dsp_fnbaslc
#define dsp_dfwt22d dsp_ffwt22d
#define dsp_dcsqrt dsp_fcsqrt
#define dsp_dpolar dsp_fpolar
#define dsp_drect dsp_frect
#define dsp_drotatex dsp_frotatex
#define dsp_drotatey dsp_frotatey
#define dsp_drotatez dsp_frotatez
#define dsp_dsbfir dsb_fsbfir
#define dsp_dscale dsp_fscale
#define dsp_dspqmath dsp_fspqmath
#define dsp_dtoq dsp_ftoq
#define dsp_dtranslt dsp_ftranslt
#define dsp_dmTmult dsp_fmTmult
#define dsp_dmTmultT dsp_fmTmultT
#define dsp_dmTvmult dsp_fmTvmult
#define dsp_dmdet dsp_fmdet
#define dsp_dminv dsp_fminv
#define dsp_dmmult dsp_fmmult
#define dsp_dmmultT dsp_fmmultT
#define dsp_dmsq2Tmult dsp_fmsq2Tmult
#define dsp_dmsq2mult dsp_fmsq2mult
#define dsp_dmsqTadd dsp_fmsqTadd
#define dsp_dmsqTcopy dsp_fmsqTcopy
#define dsp_dmsqTsub dsp_fmsqTsub
#define dsp_dmsqadd dsp_fmsqadd
#define dsp_dmsqcopy dsp_fmsqcopy
#define dsp_dmsqsub dsp_fmsqsub
#define dsp_dmvmult dsp_fmvmult
#define dsp_dnsolve dsp_fnsolve
#define dsp_dblackman dsp_fblackman
#define dsp_dfft2 dsp_ffft2
#define dsp_dfft2_t dsp_ffft2_t
#define dsp_dfft2f dsp_ffft2f
#define dsp_dfft2f_t dsp_ffft2f_t
#define dsp_dfftn2 dsp_ffftn2
#define dsp_dfftn2_t dsp_ffftn2_t
#define dsp_dfht_t dsp_ffht_t
#define dsp_dhamm dsp_fhamm
#define dsp_dhann dsp_fhann
#define dsp_dracorr2 dsp_fracorr2
#define dsp_dracorr2_t dsp_fracorr2_t
#define dsp_drconv dsp_frconv
#define dsp_drconv2 dsp_frconv2
#define dsp_drconv2_t dsp_frconv2_t
#define dsp_drconvn2 dsp_frconvn2
#define dsp_drconvn2_t dsp_frconvn2_t
#define dsp_drcorr2 dsp_frcorr2
#define dsp_drcorr2_t dsp_frcorr2_t
#define dsp_drcorrn2 dsp_frcorrn2
#define dsp_drcorrn2_t dsp_frcorrn2_t
#define dsp_drfft2 dsp_frfft2
#define dsp_drfft2_t dsp_frfft2_t
#define dsp_drfftn2 dsp_frfftn2
#define dsp_drfftn2_t dsp_frfftn2_t
#define dsp_drowfft2_t dsp_frowfft2_t
#define dsp_drowfft2 dsp_frowfft2
#define dsp_drxcorr dsp_frxcorr
#define dsp_dtwinfft2 dsp_ftwinfft2
#define dsp_dtwinfft2_t dsp_ftwinfft2_t
#define dsp_dwelch dsp_fwelch
#define dsp_dcswap dsp_fcswap
#define dsp_drswap dsp_frswap
#define dsp_dvcadd dsp_fvcadd
#define dsp_dvcbitr dsp_fvcbitr
#define dsp_dvcjgate dsp_fvcjgate
#define dsp_dvcjmult dsp_fvcjmult
#define dsp_dvcmagnsq dsp_fvcmagnsq
#define dsp_dvcmult dsp_fvcmult
#define dsp_dvcrmult dsp_fvcrmult
#define dsp_dvcsmult dsp_fvcsmult
#define dsp_dvcsplit dsp_fvcsplit
#define dsp_dvcsub dsp_fvcsub
#define dsp_dvdownsamp dsp_fvdownsamp
#define dsp_dvmTmult dsp_fvmTmult
#define dsp_dvmmult dsp_fvmmult
#define dsp_dvr2bitr dsp_fvr2bitr
#define dsp_dvradd dsp_fvradd
#define dsp_dvrbitr dsp_fvrbitr
#define dsp_dvrbitrn dsp_fvrbitrn
#define dsp_dvrdotp dsp_fvrdotp
#define dsp_dvrjoin dsp_fvrjoin
#define dsp_dvrmax dsp_fvrmax
#define dsp_dvrmin dsp_fvrmin
#define dsp_dvrmult dsp_fvrmult
#define dsp_dvrsadd dsp_fvrsadd
#define dsp_dvrsmult dsp_fvrsmult
#define dsp_dvrssub dsp_fvrssub
#define dsp_dvrsub dsp_fvrsub
#define dsp_dvupsamp dsp_fvupsamp

#endif /* FLOAT */

#endif /* __DSPFNS_H__ */
