#include "Bar.h"

ostream & operator<<(ostream & os, Bar & b)
{
	os << b.t.y << "." << b.t.m << "." << b.t.d << " " << b.t.h << ':' << b.t.min << " - "
		<< setprecision(7) << b.ohlc[0] << " " << b.ohlc[1] << " " << b.ohlc[2] << " " << b.ohlc[3] << " " << b.vol;
	for (double indData : b.indDatas)
	{
		os << "| " << indData;
	}
	return os;
}
