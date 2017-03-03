#include <stdio.h>
#include "tools.h"

/**
@b read bitLen bits to bitData from bitStream beginning bitStartPos, and the bitStream's length is bitStartPos.

@p[in] bitStream, the source bitStream.
@p[in] bitStreamLen, the source bitStream Length by byte.
@p[in] bitStartPos, the postion to be read.
@p[out] bitData, the destination bitStream.
@p[out] bitLen, the destination bitStream Length by bits 

@p[out] retVal, 0 successful or <0 failed.
*/
/**
	unsigned char bitStream[5]={0x23,0x45,0x12,0x67,0x89};
*/
int getBits(unsigned char *bitStream,int bitStreamLen,int bitStartPos,unsigned char *bitData,int bitLen)
{
	int retVal=0;

	int byteOffset = bitStartPos/8 ;
	int bitOffsetInByte=(7-bitStartPos%8);
	int loopCount=bitLen;

	unsigned int value=0;

	unsigned int bitMask;
	unsigned int bitVal=0;

	// assert(bitLen<32)
	if(bitLen>32)
	{
		printf("in %s the bitLen>32\n",__FUNCTION__);
		retVal=-1;
		return (retVal);
	}
	//bitVal=(bitStream[byteOffset]&bitMask)>>bitOffsetInByte;

	//理解偏移的含义，从0开始，才叫偏移。
	while(loopCount--)
	{
		if(byteOffset>bitStreamLen)
		{
			retVal=-2;
			return (retVal);
		}
		else
		{}

		// value<<1 is error.
		value<<=1;

		bitMask=0x1<<bitOffsetInByte;
		bitVal=( bitStream[byteOffset] & bitMask ) >> bitOffsetInByte;
		value|=bitVal;



		bitOffsetInByte--;
		if(bitOffsetInByte<0)
		{
			bitOffsetInByte=7;
			byteOffset++;
		}


	}
	
	*bitData=value;

	return (retVal);
	
}
