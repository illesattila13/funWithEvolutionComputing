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
		>> bar.ohlc[0] >> c
		>> bar.ohlc[1] >> c
		>> bar.ohlc[2] >> c
		>> bar.ohlc[3] >> c >> bar.vol)
	{
		
		series.push_back(bar);
	}
}

void TimeSeries::printData()
{
	list<Bar>::iterator it;
	for (it = series.begin(); it != series.end(); ++it)
	{
		cout << *it << endl;
	}
}

int TimeSeries::indCount = 0;

int TimeSeries::addInd(IndicatorBase * ind)
{
	ind->setId(indCount++);
	indicators.push_back(ind);
	return indCount;
}

void TimeSeries::calculateIndicators()
{
	for (IndicatorBase* inds : indicators)
	{
		inds->calculate(series);
	}
}

TimeSeries::~TimeSeries()
{
	for (IndicatorBase* inds : indicators)
	{
		delete inds;
	}
}
