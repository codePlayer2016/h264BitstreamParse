// 
int findNalUnit(unsigned char *pBitstreamBuf,unsigned char *pNalBuf,int szNalBuf)
{
	int retVal=0;
	unsigned char *pBit=pBitstreamBuf;
	unsigned char *pNal=pNalBuf;

	int flag=1;
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
	}

	/*
	start_code_prefix_one_3bytes /* 等于 0x000001 
	*/
	if(pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=1)
	{
		retVal=-1;
		return (retVal);
	}
	// nal_unit( NumBytesInNALunit )
	
	
	while((pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=1) && (pBit[0]!=0 || pBit[1]!=0|| pBit[2]!=0 || pBit[3]!=1))
	{
		*pNal=*pBit;
		pNal++;
		pBit++;
	}
		
	pBitstreamBuf=pBit;
}