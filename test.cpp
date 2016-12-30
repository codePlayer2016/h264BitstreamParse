#include <stdio.h>
#include <stdlib.h>
#include "nal.h"

unsigned char bitBuf[1024*1024*20];
unsigned char nalBuf[1024*1024];


int main()
{
  int retVal=0;
  int bitSize=0;
  int nalsize=0;

  int freadsize=0;

  unsigned char *pNalBuf=nalBuf;
  int *szNalBuf=&nalsize;
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

  freadsize=fread(bitBuf,1,bitSize,fp);
  if(freadsize!=bitSize)
  {
	retVal=-1;
	return (retVal);
  }
  else
  {}
  findNalUnit(bitBuf,pNalBuf,szNalBuf);


  // LeadingZero8BitsCount + startCode + nalu data + TrailingZero8Bits
  //TODO: get the first startcode
  //TODO: get the second startcode
  return(retVal);
}