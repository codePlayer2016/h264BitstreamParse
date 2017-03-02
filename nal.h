#ifndef __NAL_H__
#define __NAL_H__


typedef struct Nal_t
{
	int prefixCodeLen;
	int forbiddenBit;
	int nalRefIdc;
	int nalType;
	int length;
	int ebspLen;
	int rbspLen;
	int sodbLen;
	unsigned char *pBuffer;
	unsigned char *pEbsp;
	unsigned char *pRbsp;
	//unsigned char *pSodb;
} Nal_t;

int findNalUnit(unsigned char **pBitstreamBuf,Nal_t *pNal,int *pBitSize);
int parseNalUnite(Nal_t *pNal);
int ebspToRbsp(Nal_t *pNal);

#endif