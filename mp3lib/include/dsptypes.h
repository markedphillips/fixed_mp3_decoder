#ifndef __DSPTYPES_H
#define __DSPTYPES_H

#ifndef __QFIXED_MAX__
typedef short QFIXED;
#define __QFIXED_MAX__ __SHORT_MAX__
#define __QFIXED_MIN__ __SHORT_MIN__
#endif

#ifndef __QACC_MAX__
typedef long QACC;
#define __QACC_MAX__ __LONG_MAX__
#define __QACC_MIN__ __LONG_MIN__
#endif

typedef double DFLOAT;
typedef float FFLOAT;

typedef int boolean;

typedef struct {
  DFLOAT real;
  DFLOAT imag;
} DCMPLX;

typedef DCMPLX CMPLX;

typedef struct {
  float real;
  float imag;
} FCMPLX;

typedef struct {
  QFIXED real;
  QFIXED imag;
} QCMPLX;

typedef struct {
  QFIXED quotient;
  QFIXED remainder;
} IDIVRESULT;

typedef struct {
  DFLOAT x, y, z;
} DPOINT;

typedef struct {
  FFLOAT x, y, z;
} FPOINT;

typedef struct {
  QFIXED x, y, z;
} QPOINT;

typedef struct {
  DFLOAT r;
  DFLOAT theta;
} DPOLARCOORD;

typedef struct {
  FFLOAT r;
  FFLOAT theta;
} FPOLARCOORD;

typedef struct {
  DFLOAT x;
  DFLOAT y;
} DRECTCOORD;

typedef struct {
  FFLOAT x;
  FFLOAT y;
} FRECTCOORD;

/* Convolutional encoder info */
typedef struct {
  unsigned long  *cv;
  char  *shifter;
} ENCODER_INFO;

/* Viterbi decoder types */
typedef struct {
  int    prev_state;
  int    output;
} VITERBI_TABLE_ENTRY;

typedef struct {
  int prev_state;
  int cost;
  int input;
} VITERBI_NODE;

typedef struct {
  int depth;
  int weight;
  int seed;
  VITERBI_TABLE_ENTRY *vt;
  VITERBI_NODE *buffer;
  int *tie_buffer;
} VITERBI_DECODER_INFO;

/* Combination convolutional encoder / Viterbi decoder */
typedef struct {
  int n;
  int k;
  int v;
  int states;
  ENCODER_INFO encoder_info;
  VITERBI_DECODER_INFO decoder_info;
} ENCODER_DECODER;

/* Puncuture convolutional encoder / Viterbi decoder */
typedef struct {
  int p;
  int q;
  ENCODER_DECODER *encoder;
  unsigned long pbits;
} PUNCTURED_ENCODER_DECODER;

/* Masks for filter and filter-type structures */
#define DSP_FILTER_ALLOC_MASK   0x0001
#define DSP_BUFFER_ALLOC_MASK   0x0002
#define DSP_VBUFFER1_ALLOC_MASK 0x0004
#define DSP_VBUFFER2_ALLOC_MASK 0x0008
#define DSP_MATRIX_ALLOC_MASK   0x0010
#define DSP_TAPS1_ALLOC_MASK    0x0020

/* Filter states */
typedef struct {
  DFLOAT      *taps1;
  DFLOAT      *taps2;
  DFLOAT      *buffer;
  DFLOAT      *matrix;
  DFLOAT      *vbuffer1;
  DFLOAT      *vbuffer2;
  DFLOAT       val;
  DFLOAT       temp;
  DFLOAT       alpha;
  DFLOAT       beta;
  int          taps1_len;
  int          taps2_len;
  int          buflen;
  int          index;
  int          counter;
  int          decimation;
  int          interpolation;
  int          items_needed;
  unsigned int mask;
} DFILTER_STATE;

typedef struct {
  FFLOAT      *taps1;
  FFLOAT      *taps2;
  FFLOAT      *buffer;
  FFLOAT      *matrix;
  FFLOAT      *vbuffer1;
  FFLOAT      *vbuffer2;
  FFLOAT       val;
  FFLOAT       temp;
  FFLOAT       alpha;
  FFLOAT       beta;
  int          taps1_len;
  int          taps2_len;
  int          buflen;
  int          index;
  int          counter;
  int          decimation;
  int          interpolation;
  int          items_needed;
  unsigned int mask;
} FFILTER_STATE;

typedef struct {
  QACC         mu;
  QACC         magn_sq;
  QFIXED      *taps1;
  QFIXED      *taps2;
  QFIXED      *buffer;
  QFIXED      *matrix;
  QFIXED      *vbuffer1;
  QFIXED      *vbuffer2;
  QFIXED       val;
  QFIXED       temp;
  QFIXED       alpha;
  QFIXED       beta;
  int          taps1_len;
  int          taps2_len;
  int          buflen;
  int          index;
  int          counter;
  int          decimation;
  int          interpolation;
  int          items_needed;
  unsigned int mask;
} QFILTER_STATE;

/* Broadband array state structures */
typedef struct {
  DFLOAT       mu;
  DFLOAT      *weights;
  DFLOAT      *desired_taps;
  DFLOAT      *buffer;
  int          weights_len;
  int          num_sensors;
  int          num_desired_taps;
  int          buflen;
  int          index;
  int          counter;
  unsigned int mask;
} DBBA_STATE;

typedef struct {
  FFLOAT       mu;
  FFLOAT      *weights;
  FFLOAT      *desired_taps;
  FFLOAT      *buffer;
  int          weights_len;
  int          num_sensors;
  int          num_desired_taps;
  int          buflen;
  int          index;
  int          counter;
  unsigned int mask;
} FBBA_STATE;

typedef struct {
  QACC         mu;
  QFIXED      *weights;
  QFIXED      *desired_taps;
  QFIXED      *buffer;
  int          weights_len;
  int          num_sensors;
  int          num_desired_taps;
  int          buflen;
  int          index;
  int          counter;
  unsigned int mask;
} QBBA_STATE;

/* Channel equalization state structures */

typedef struct {
  DFLOAT        *desired_results;
  DFLOAT        *inputs;
  DFILTER_STATE *filter;
  int            desired_len;
  unsigned int   mask;
} DCHEQ_STATE;
  
typedef struct {
  FFLOAT        *desired_results;
  FFLOAT        *inputs;
  FFILTER_STATE *filter;
  int            desired_len;
  unsigned int   mask;
} FCHEQ_STATE;
  
typedef struct {
  QFIXED        *desired_results;
  QFIXED        *inputs;
  QFILTER_STATE *filter;
  int            desired_len;
  unsigned int   mask;
} QCHEQ_STATE;

/*
 * The following is the definition of the state structure
 * used by the G.721/G.723 encoder and decoder to preserve their internal
 * state between successive calls.  The meanings of the majority
 * of the state structure fields are explained in detail in the
 * CCITT Recommendation G.721.  The field names are essentially indentical
 * to variable names in the bit level description of the coding algorithm
 * included in this Recommendation.
 */
typedef struct g72x_state {
  long yl;	/* Locked or steady state step size multiplier. */
  short yu;	/* Unlocked or non-steady state step size multiplier. */
  short dms;	/* Short term energy estimate. */
  short dml;	/* Long term energy estimate. */
  short ap;	/* Linear weighting coefficient of 'yl' and 'yu'. */
  
  short a[2];	/* Coefficients of pole portion of prediction filter. */
  short b[6];	/* Coefficients of zero portion of prediction filter. */
  short pk[2];	/*
		 * Signs of previous two samples of a partially
		 * reconstructed signal.
		 */
  short dq[6];	/*
		 * Previous 6 samples of the quantized difference
		 * signal represented in an internal floating point
		 * format.
		 */
  short sr[2];	/*
		 * Previous 2 samples of the quantized difference
		 * signal represented in an internal floating point
		 * format.
		 */
  char td;	/* delayed tone detect, new in 1988 version */
} G72X_STATE;

/* Image Processing */

typedef enum { IMAGE_BW, IMAGE_HSI, IMAGE_RGB, IMAGE_RGBA, IMAGE_BGR, IMAGE_BGRA, 
	       IMAGE_CMY, IMAGE_CMYK, IMAGE_HSV, IMAGE_YUV, IMAGE_YIQ } IMAGE_FORMAT;
#define MAX_IMAGE_FORMAT (IMAGE_YIQ + 1)
typedef enum { IMAGE_BIT8, IMAGE_BIT16, IMAGE_FLOAT, IMAGE_DOUBLE } IMAGE_PIXEL_TYPE;
typedef enum { BORDER_DEFAULT, BORDER_NONE, BORDER_CONSTANT, 
	       BORDER_MIRROR, BORDER_REPEAT } IMAGE_BORDER_TYPE;
typedef enum { MASK_COMBINE_DEFAULT, MASK_COMBINE_ADD, MASK_COMBINE_ABS, MASK_COMBINE_MAGNITUDE, 
	       MASK_COMBINE_POWER } IMAGE_MASK_COMBINE_TYPE;
typedef enum { EDGE_DEFAULT, EDGE_ROBERTS, EDGE_PREWITT, EDGE_SOBEL } IMAGE_EDGE_DETECT_TYPE;

typedef struct image {
  int               init_code;  /* identifies valid image */
  IMAGE_FORMAT      format;     /* format of image */
  IMAGE_PIXEL_TYPE  pixel_type; /* data type of each pixel */
  IMAGE_BORDER_TYPE border_type;/* type of border for convolving at edges */
  union {                       /* border_constant if border_type is BORDER_CONSTANT */
    unsigned char   byte_val;
    unsigned short  short_val;
    float           float_val;
    double          double_val;
  }                 border_constant; 
  int               rows;       /* number of total rows */
  int               cols;       /* number of total cols */
  int               size;       /* size in bytes of image */
  int               sub_index;  /* index of start of subimage */
  int               sub_rows;   /* number of subimage rows */
  int               sub_cols;   /* number of subimage cols */
  int               sub_stride; /* byte distance between end of subimage row and next row */
  int               sub_size;   /* size of subimage in bytes */
  int               pixel_size; /* size of pixel in bytes */
  int               buffer_size;/* size of work buffer */
  int               pixels_allocated; /* did library allocate pixels array */
  unsigned char    *buffer;     /* work buffer */
  unsigned char    *pixels;     /* pointer to pixel data */
} IMAGE;
   
typedef struct image_bit8_histogram {
  unsigned long     sum_total;         /* sum total of all pixels */
  unsigned long     pixel_totals[256]; /* individual totals for each value of pixel */
} IMAGE_BIT8_HISTOGRAM;

typedef unsigned char IMAGE_BIT8_MAP[256];

typedef struct image_mask {
  int               mask_len;    /* total length of total mask */
  int               scaling;     /* scale factor to divide result by */
  int              *mask_values; /* signed byte mask */
} IMAGE_MASK;

/* MPEG2 */

#define ERROR (-1)

#define PICTURE_START_CODE      0x100
#define SLICE_START_CODE_MIN    0x101
#define SLICE_START_CODE_MAX    0x1AF
#define USER_DATA_START_CODE    0x1B2
#define SEQUENCE_HEADER_CODE    0x1B3
#define SEQUENCE_ERROR_CODE     0x1B4
#define EXTENSION_START_CODE    0x1B5
#define SEQUENCE_END_CODE       0x1B7
#define GROUP_START_CODE        0x1B8
#define SYSTEM_START_CODE_MIN   0x1B9
#define SYSTEM_START_CODE_MAX   0x1FF

#define ISO_END_CODE            0x1B9
#define PACK_START_CODE         0x1BA
#define SYSTEM_START_CODE       0x1BB

#define VIDEO_ELEMENTARY_STREAM 0x1e0

/* scalable_mode */
#define SC_NONE 0
#define SC_DP   1
#define SC_SPAT 2
#define SC_SNR  3
#define SC_TEMP 4

/* picture coding type */
#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3
#define D_TYPE 4

/* picture structure */
#define TOP_FIELD     1
#define BOTTOM_FIELD  2
#define FRAME_PICTURE 3

/* macroblock type */
#define MACROBLOCK_INTRA                        1
#define MACROBLOCK_PATTERN                      2
#define MACROBLOCK_MOTION_BACKWARD              4
#define MACROBLOCK_MOTION_FORWARD               8
#define MACROBLOCK_QUANT                        16
#define SPATIAL_TEMPORAL_WEIGHT_CODE_FLAG       32
#define PERMITTED_SPATIAL_TEMPORAL_WEIGHT_CLASS 64

/* motion_type */
#define MC_FIELD 1
#define MC_FRAME 2
#define MC_16X8  2
#define MC_DMV   3

/* mv_format */
#define MV_FIELD 0
#define MV_FRAME 1

/* chroma_format */
#define CHROMA420 1
#define CHROMA422 2
#define CHROMA444 3

/* extension start code IDs */

#define SEQUENCE_EXTENSION_ID                    1
#define SEQUENCE_DISPLAY_EXTENSION_ID            2
#define QUANT_MATRIX_EXTENSION_ID                3
#define COPYRIGHT_EXTENSION_ID                   4
#define SEQUENCE_SCALABLE_EXTENSION_ID           5
#define PICTURE_DISPLAY_EXTENSION_ID             7
#define PICTURE_CODING_EXTENSION_ID              8
#define PICTURE_SPATIAL_SCALABLE_EXTENSION_ID    9
#define PICTURE_TEMPORAL_SCALABLE_EXTENSION_ID  10

#define ZIG_ZAG                                  0

#define PROFILE_422                             (128+5)
#define MAIN_LEVEL                              8

/* Layers: used by Verbose_Flag, Verifier_Flag, Stats_Flag, and Trace_Flag */
#define NO_LAYER                                0
#define SEQUENCE_LAYER                          1
#define PICTURE_LAYER                           2
#define SLICE_LAYER                             3    
#define MACROBLOCK_LAYER                        4    
#define BLOCK_LAYER                             5
#define EVENT_LAYER                             6
#define ALL_LAYERS                              7

#define FILENAME_LENGTH                       256

#define MB_WEIGHT                  32
#define MB_CLASS4                  64

/* MPEG structures and defines */

/* output types (Output_Type) */
#define T_YUV   0
#define T_SIF   1
#define T_TGA   2
#define T_PPM   3
#define T_X11   4
#define T_X11HIQ 5

/* main MPEG2 structure */

typedef struct {

  char Version[30];

  char Author[50];

  /* zig-zag and alternate scan patterns */
  unsigned char scan[2][64];

  /* default intra quantization matrix */
  unsigned char default_intra_quantizer_matrix[64];

  /* non-linear quantization coefficient table */
  unsigned char Non_Linear_quantizer_scale[32];

  /* color space conversion coefficients
   * for YCbCr -> RGB mapping
   *
   * entries are {crv,cbu,cgu,cgv}
   *
   * crv=(255/224)*65536*(1-cr)/0.5
   * cbu=(255/224)*65536*(1-cb)/0.5
   * cgu=(255/224)*65536*(cb/cg)*(1-cb)/0.5
   * cgv=(255/224)*65536*(cr/cg)*(1-cr)/0.5
   *
   * where Y=cr*R+cg*G+cb*B (cr+cg+cb=1)
   */

  /* ISO/IEC 13818-2 section 6.3.6 sequence_display_extension() */

  int Inverse_Table_6_9[8][4];

  /* decoder operation control variables */
  int Output_Type;
  int hiQdither;

  /* decoder operation control flags */
  int Quiet_Flag;
  int Trace_Flag;
  int Fault_Flag;
  int Verbose_Flag;
  int Two_Streams;
  int Spatial_Flag;
  int Reference_IDCT_Flag;
  int Frame_Store_Flag;
  int System_Stream_Flag;
  int Display_Progressive_Flag;
  int Ersatz_Flag;
  int Big_Picture_Flag;
  int Verify_Flag;
  int Stats_Flag;
  int User_Data_Flag;
  int Main_Bitstream_Flag;

  /* filenames */
  char *Output_Picture_Filename;
  char *Substitute_Picture_Filename;
  char *Main_Bitstream_Filename; 
  char *Enhancement_Layer_Bitstream_Filename; 

  /* buffers for multiuse purposes */
  char Error_Text[256];
  unsigned char *Clip;

  /* pointers to generic picture buffers */
  unsigned char *backward_reference_frame[3];
  unsigned char *forward_reference_frame[3];

  unsigned char *auxframe[3];
  unsigned char *current_frame[3];
  unsigned char *substitute_frame[3];

  /* pointers to scalability picture buffers */
  unsigned char *llframe0[3];
  unsigned char *llframe1[3];

  short *lltmp;
  char *Lower_Layer_Picture_Filename;

  /* non-normative variables derived from normative elements */
  int Coded_Picture_Width;
  int Coded_Picture_Height;
  int Chroma_Width;
  int Chroma_Height;
  int block_count;
  int Second_Field;
  int profile, level;

  /* normative derived variables (as per ISO/IEC 13818-2) */
  int horizontal_size;
  int vertical_size;
  int mb_width;
  int mb_height;
  double bit_rate;
  double frame_rate; 

  /* headers */

  /* ISO/IEC 13818-2 section 6.2.2.1:  sequence_header() */
  int aspect_ratio_information;
  int frame_rate_code; 
  int bit_rate_value; 
  int vbv_buffer_size;
  int constrained_parameters_flag;

  /* ISO/IEC 13818-2 section 6.2.2.3:  sequence_extension() */
  int profile_and_level_indication;
  int progressive_sequence;
  int chroma_format;
  int low_delay;
  int frame_rate_extension_n;
  int frame_rate_extension_d;

  /* ISO/IEC 13818-2 section 6.2.2.4:  sequence_display_extension() */
  int video_format;  
  int color_description;
  int color_primaries;
  int transfer_characteristics;
  int matrix_coefficients;
  int display_horizontal_size;
  int display_vertical_size;

  /* ISO/IEC 13818-2 section 6.2.3: picture_header() */
  int temporal_reference;
  int picture_coding_type;
  int vbv_delay;
  int full_pel_forward_vector;
  int forward_f_code;
  int full_pel_backward_vector;
  int backward_f_code;

  /* ISO/IEC 13818-2 section 6.2.3.1: picture_coding_extension() header */
  int f_code[2][2];
  int intra_dc_precision;
  int picture_structure;
  int top_field_first;
  int frame_pred_frame_dct;
  int concealment_motion_vectors;

  int intra_vlc_format;

  int repeat_first_field;

  int chroma_420_type;
  int progressive_frame;
  int composite_display_flag;
  int v_axis;
  int field_sequence;
  int sub_carrier;
  int burst_amplitude;
  int sub_carrier_phase;

  /* ISO/IEC 13818-2 section 6.2.3.3: picture_display_extension() header */
  int frame_center_horizontal_offset[3];
  int frame_center_vertical_offset[3];

  /* ISO/IEC 13818-2 section 6.2.2.5: sequence_scalable_extension() header */
  int layer_id;
  int lower_layer_prediction_horizontal_size;
  int lower_layer_prediction_vertical_size;
  int horizontal_subsampling_factor_m;
  int horizontal_subsampling_factor_n;
  int vertical_subsampling_factor_m;
  int vertical_subsampling_factor_n;


  /* ISO/IEC 13818-2  6.2.3.5: picture_spatial_scalable_extension() header */
  int lower_layer_temporal_reference;
  int lower_layer_horizontal_offset;
  int lower_layer_vertical_offset;
  int spatial_temporal_weight_code_table_index;
  int lower_layer_progressive_frame;
  int lower_layer_deinterlaced_field_select;

  /* ISO/IEC 13818-2 section 6.2.3.6: copyright_extension() header */
  int copyright_flag;
  int copyright_identifier;
  int original_or_copy;
  int copyright_number_1;
  int copyright_number_2;
  int copyright_number_3;

  /* ISO/IEC 13818-2 section 6.2.2.6: group_of_pictures_header()  */
  int drop_flag;
  int hour;
  int minute;
  int sec;
  int frame;
  int closed_gop;
  int broken_link;

  /* layer specific variables (needed for SNR and DP scalability) */
  struct layer_data {
    /* bit input */
    int Infile;
    unsigned char Rdbfr[2048];
    unsigned char *Rdptr;
    unsigned char Inbfr[16];
    /* from mpeg2play */
    unsigned int Bfr;
    unsigned char *Rdmax;
    int Incnt;
    int Bitcnt;
    /* sequence header and quant_matrix_extension() */
    int intra_quantizer_matrix[64];
    int non_intra_quantizer_matrix[64];
    int chroma_intra_quantizer_matrix[64];
    int chroma_non_intra_quantizer_matrix[64];
  
    int load_intra_quantizer_matrix;
    int load_non_intra_quantizer_matrix;
    int load_chroma_intra_quantizer_matrix;
    int load_chroma_non_intra_quantizer_matrix;

    int MPEG2_Flag;
    /* sequence scalable extension */
    int scalable_mode;
    /* picture coding extension */
    int q_scale_type;
    int alternate_scan;
    /* picture spatial scalable extension */
    int pict_scal;
    /* slice/macroblock */
    int priority_breakpoint;
    int quantizer_scale;
    int intra_slice;
    short block[12][64];
  } base, enhan, *ld;

  #ifdef VERIFY
  int verify_sequence_header;
  int verify_group_of_pictures_header;
  int verify_picture_header;
  int verify_slice_header;
  int verify_sequence_extension;
  int verify_sequence_display_extension;
  int verify_quant_matrix_extension;
  int verify_sequence_scalable_extension;
  int verify_picture_display_extension;
  int verify_picture_coding_extension;
  int verify_picture_spatial_scalable_extension;
  int verify_picture_temporal_scalable_extension;
  int verify_copyright_extension;
  #endif /* VERIFY */

  int Decode_Layer;

  int global_MBA;
  int global_pic;
  int True_Framenum;

} global_var;

typedef struct {
  int MBA;
  int macroblock_type;
  int motion_type;
  int PMV[2][2][2];
  int motion_vertical_field_select[2][2];
  int dmvector[2];
  int stwtype;
  int dct_type;
} MotionInfo;

/* MPEG Audio */

typedef struct {
      int scfsi;
      unsigned part2_3_length;
      unsigned big_values;
      unsigned scalefac_compress;
      unsigned block_type;
      unsigned mixed_block_flag;
      unsigned table_select[3];
      unsigned subblock_gain[3];
      unsigned maxband[3];
      unsigned maxbandl;
      unsigned maxb;
      unsigned region1start;
      unsigned region2start;
      unsigned preflag;
      unsigned scalefac_scale;
      unsigned count1table_select;
// hack for MP3 demo
      QACC *full_gain[3];
      QACC *pow2gain;
} gr_info_s;

typedef struct {
  short bits;
  short d;
} al_table;

typedef struct {
#ifdef AUDIO_USES_FD
//  int fn; /* filenumber */
#endif
#ifdef SGI
  ALconfig config;
  ALport port;
#endif
  long rate;
  long gain;
  int output;
#ifdef ALSA
  void *handle;
  snd_pcm_format_t alsa_format;
#endif
  char *device;
  int channels;
  int format;
  int private1;
  void *private2;
}  audio_info_struct;

struct frame {
    al_table *alloc;
// hack for MP3 demo
    int (*synth)(QACC *,int,unsigned char *,int *);
    int (*synth_mono)(QACC *,unsigned char *,int *);
    int stereo;
    int jsbound;
    int single;
    int II_sblimit;
    int down_sample_sblimit;
    int lsf;
    int mpeg25;
    int down_sample;
    int header_change;
    int lay;
    int (*do_layer)(struct frame *fr,int,audio_info_struct *);
    int error_protection;
    int bitrate_index;
    int sampling_frequency;
    int padding;
    int extension;
    int mode;
    int mode_ext;
    int copyright;
    int original;
    int emphasis;
    int framesize; /* computed framesize */
};

typedef struct {
  unsigned main_data_begin;
  unsigned private_bits;
  struct {
    gr_info_s gr[2];
  } ch[2];
}  III_sideinfo;


/* MP3 audio structures */

#define MP3_ERR -1
#define MP3_OK  0
#define MP3_NEED_MORE 1
#define MP3_EXIT 2
#define MP3_BUFFER_FULL 3

#define MAXFRAMESIZE 1792
#define         SBLIMIT                 32
#define         SSLIMIT                 18

struct buf {
  unsigned char *pnt;
  long size;
  long pos;
  struct buf *next;
  struct buf *prev;
};

struct mp3frame {
  int stereo;
  int jsbound;
  int single;
  int lsf;
  int mpeg25;
  int header_change;
  int lay;
  int error_protection;
  int bitrate_index;
  int sampling_frequency;
  int padding;
  int extension;
  int mode;
  int mode_ext;
  int copyright;
  int original;
  int emphasis;
  int framesize; /* computed framesize */
};

struct mpstr {
  int bsize;
  int framesize;
  int fsizeold;
  struct mp3frame fr;
  unsigned char bsspace[2][MAXFRAMESIZE+512]; /* MAXFRAMESIZE */
// hack for MP3 demo
//  Real hybrid_block[2][2][SBLIMIT*SSLIMIT];
  long hybrid_block[2][2][SBLIMIT*SSLIMIT];
  int hybrid_blc[2];
  unsigned long header;
  int bsnum;
//  Real synth_buffs[2][2][0x110];
  long synth_buffs[2][2][0x110];
  int  synth_bo;
  int iHeaderBytes;		// Number of bytes currently in the header.
  int iValidBytes;		// Number of valid bytes in the buffer.
};

#endif // #ifndef __DSP_TYPES_H
