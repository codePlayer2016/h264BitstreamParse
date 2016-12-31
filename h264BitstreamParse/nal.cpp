
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNalUnit(unsigned char **pBitstreamBuf,unsigned char *pNalBuf,int *szNalBuf,int bitSize)
{
	int retVal=0;
	int flag=1;
	int processedSize=0;
	//
	unsigned char *pBit=(unsigned char *)*pBitstreamBuf;
	unsigned char *pNalStart=NULL;
	unsigned char *pNalBufOut=pNalBuf;
	*szNalBuf=0;

	// todo: erro check.
	/*
	while( next_bits( 24 ) != 0x000001 && next_bits( 32 ) != 0x00000001 )
	leading_zero_8bits //等于 0x00 
	*/

	while(flag)
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
			flag=0;
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
		pBit+=3;
		processedSize++;
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
		(*szNalBuf)++;

		if(processedSize+4>bitSize)
		{
			retVal=2;
			return(retVal);
		}
		//printf("pNal=%d\n",pBit[0]);
	}
	memcpy(pNalBufOut,pNalStart,*szNalBuf);
	retVal=1;

	//printf("szNalBuf=%d\n",*szNalBuf);
	//printf("%d,%d,%d,%d",pNalBuf[0],pNalBuf[1],pNalBuf[2],pNalBuf[3]);

	*pBitstreamBuf=pBit;
	return (retVal);
}
