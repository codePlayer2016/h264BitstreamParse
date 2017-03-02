
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nal.h"
/**
@b get the nal in the stream.
@p[in/out] pBitstreamBuf input stream.
@p[out] pNal Nal unite. 
@p[in/out] pBitSize the bit stream length.
*/

int findNalUnit(unsigned char **pBitstreamBuf,Nal_t *pNal,int *pBitSize)
{
	int retVal=0;

	int processedSize=0;
	//
	unsigned char *pBit=(unsigned char *)*pBitstreamBuf;
	unsigned char *pNalStart=NULL;
	unsigned char *pNalBufOut=pNal->pBuffer;
	int nalLen=0;
	int bitSize=*pBitSize;
	//*szNalBuf=0;

	// todo: erro check.
	/*
	while( next_bits( 24 ) != 0x000001 && next_bits( 32 ) != 0x00000001 )
	leading_zero_8bits //等于 0x00 
	*/

	while(1)
	{
		if((pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=1) && (pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=0 || pBit[3]!=1))
		{
			pBit++;
			processedSize++;
			if(processedSize+4>bitSize)
			{
				retVal=2;
				return(retVal);
			}
		}
		else
		{
			break;
		}

	}
	/*
	if( next_bits( 24 ) != 0x000001 )
	zero_byte /* equal to 0x00
	*/
	if((pBit[0]!=0 || pBit[1]!=0 || pBit[2]!=1))
	{
		pBit++;
		processedSize++;
	}
	else
	{
		pNal->prefixCodeLen=3;
		pBit+=3;
		processedSize+=3;
	}

	/*
	start_code_prefix_one_3bytes /* 等于 0x000001 
	*/
	if(pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=1)
	{
		retVal=-1;
		return (retVal);
	}
	else
	{
		pNal->prefixCodeLen=4;
		pBit+=3;
		processedSize+=3;
	}
	// nal_unit( NumBytesInNALunit )


	while((pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=1) && (pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=0 || pBit[3]!=1))
	{
		if(pNalStart==NULL)
		{
			pNalStart=pBit;
		}

		pBit++;
		processedSize++;
		nalLen++;

		if(processedSize+4>bitSize)
		{
			retVal=2;
			return(retVal);
		}
		//printf("pNal=%d\n",pBit[0]);
	}

	pNal->length=nalLen;
	memcpy(pNalBufOut,pNalStart,nalLen);
	retVal=1;

	//printf("szNalBuf=%d\n",*szNalBuf);
	//printf("%d,%d,%d,%d",pNalBuf[0],pNalBuf[1],pNalBuf[2],pNalBuf[3]);

	*pBitstreamBuf=pBit;
	*pBitSize=bitSize-processedSize;
	return (retVal);
}

/**
@function parse the nal
@input
@output
*/

int parseNalUnite(Nal_t *pNal)
{
	int retVal=0;

	unsigned char *pSrc=pNal->pBuffer;


	//memcpy(&nalHead,pSrc,1);
	pNal->forbiddenBit=(pSrc[0]&0x80)>>7;
	pNal->nalRefIdc=(pSrc[0]&0x60)>>5;
	pNal->nalType=(pSrc[0]&0x1f);
	pNal->pEbsp=pNal->pBuffer+1;
	pNal->ebspLen=pNal->length-1;

	printf("forbidden1Bit=%2x,nalRefIdc=%2x,nalType=%2x\n",pNal->forbiddenBit,pNal->nalRefIdc,pNal->nalType);
	
	return (retVal);
}

int ebspToRbsp(Nal_t *pNal)
{
	int retVal=0;
	
	unsigned char *pData=pNal->pBuffer;
	pNal->pRbsp=(unsigned char *)malloc(pNal->length);

	int i=0;
	int j=0;
	for(i=0;i<pNal->ebspLen-2;i++)
	{
		
		if((pData[i]==0x0)&&(pData[i+1]==0x0)&&(pData[i+2]==0x03))
		{
			pNal->pRbsp[j]=pData[i];
			pNal->pRbsp[j+1]=pData[i+1];
			pNal->pRbsp[j+2]=pData[i+3];
			j+=3;
			i+=3;
		}
		else
		{
			pNal->pRbsp[j]=pData[i];
			j++;
		}
	}

	while(pNal->pRbsp[j-1]==0)
	{
		j--;
	}
	pNal->rbspLen=j;

	return (retVal);
}
