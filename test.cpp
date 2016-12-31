#include <stdio.h>
#include <stdlib.h>
#include "nal.h"

unsigned char bitBuf[1024*1024*20];
unsigned char nalBuf[1024*1024];


int main()
{
  int retVal=0;
  
  // this is the correct the error place.	
  unsigned char *pBitSource=bitBuf;
  unsigned char *pNalBuf=nalBuf;
  int bitSize=0;
  int nalsize=0;


  int *szNalBuf=&nalsize;

  int freadsize=0;
  int index=0;

  // read the bitstream.
  FILE *fp=fopen("Q:/test.h264","rb");
  if(fp==NULL)
  {
	retVal=-1;
	return (retVal);
  }
  else
  {
	fseek(fp,0L,SEEK_END);
	bitSize=ftell(fp);
	fseek(fp,0L,SEEK_SET);
  }
  freadsize=fread(pBitSource,1,bitSize,fp);
  if(freadsize!=bitSize)
  {
	retVal=-1;
	return (retVal);
  }
  else
  {}
 
   while( findNalUnit((unsigned char **)&pBitSource,pNalBuf,szNalBuf,bitSize)==1)
   {
	 //printf("szNalBuf=%d\n",*szNalBuf);
	 for(index=0;index<(*szNalBuf);index++)
	 {
		printf("%02x ",pNalBuf[index]);
	 }
	 printf("\nszNalBuf=%d\n",(*szNalBuf));

   }


  // LeadingZero8BitsCount + startCode + nalu data + TrailingZero8Bits
  //TODO: get the first startcode
  //TODO: get the second startcode
  return(retVal);
}
