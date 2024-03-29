#include <Tools.hpp> 

int			getMilliCount( void )		{
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int			getMilliSpan(int nTimeStart)	{
	int nSpan = getMilliCount() - nTimeStart;

	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}
