/* (c) 1998-2018 Mark Phillips */
#include "hipp_dsp.h"

struct framebuf {
	struct buf *buf;
	long pos;
	struct mp3frame *next;
	struct mp3frame *prev;
};

void ExitMP3(struct mpstr *mp);
