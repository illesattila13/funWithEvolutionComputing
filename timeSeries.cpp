#include "timeSeries.h"
#include <fstream>


using namespace std;

void TimeSeries::readFromFile(const char * filename)
{
	ifstream ifile(filename);
	Bar bar;
	char c;
	while (ifile >> bar.t.y >> c
		>> bar.t.m >> c
		>> bar.t.d >> c
		>> bar.t.h >> c
		>> bar.t.min >> c
		>> bar.open >> c
		>> bar.high >> c
		>> bar.low >> c
		>> bar.close >> c >> bar.vol)
	{
		/*ifile >> bar.t.y >> c
			>> bar.t.m >> c
			>> bar.t.d >> c
			>> bar.t.h >> c
			>> bar.t.min >> c
			>> bar.open >> c
			>> bar.high >> c
			>> bar.low >> c
			>> bar.close >> c >> c;*/
		series.push_back(bar);
	}
}
