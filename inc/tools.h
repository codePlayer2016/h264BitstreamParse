#ifndef __TOOLS_H__
#define __TOOLS_H__

#ifndef _WIN32
#define debug_printf(fmt,arg,...) \
printf("debug_info:<@ %s @ %s @ %s>"fmt,__FILE__, __FUNCTION__, __LINE__,##arg)
#endif

typedef struct BitData_t
{
	unsigned char *buffer;
	int bitCount;
	int byteCount;

} BitData_t;

/**
@b read bitLen bits to bitData from bitStream beginning bitStartPos, and the bitStream's length is bitStartPos.

@p[in] bitStream, the source bitStream.
@p[in] bitStreamLen, the source bitStream Length by byte.
@p[in] bitStartPos, the postion to be read.
@p[out] bitData, the destination bitStream.
@p[out] bitLen, the destination bitStream Length by bits 

@p[out] retVal, 0 successful or <0 failed.
*/
int getBits(unsigned char *bitStream,int bitStreamLen,int bitStartPos,unsigned char *bitData,int bitLen);


#endif