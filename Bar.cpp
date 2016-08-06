#include "Bar.h"

ostream & operator<<(ostream & os, Bar & b)
{
	os << b.t.y << "." << b.t.m << "." << b.t.d << " " << b.t.h << ':' << b.t.min << " - "
		<< setprecision(7) << b.open << " " << b.high << " " << b.low << " " << b.close << " " << b.vol;
	return os;
}
