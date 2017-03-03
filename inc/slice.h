#ifndef __SLICE_H__
#define __SLICE_H__

#include "nal.h"

typedef struct Sps_t
{
} Sps_t;

typedef struct Pps_t
{
} Pps_t;

int parseSPS(Nal_t *pNal,Sps_t *pSps);
int parsePPS(Nal_t *pNal,Pps_t *pPps);


#endif
