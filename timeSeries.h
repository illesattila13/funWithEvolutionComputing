#pragma once
#include <list>
#include "Bar.h"
#include <iostream>
#include "IndicatorBase.h"
#include <vector>
#include "PriceEnums.h"

using namespace std;

//ez az oszt�ly egy t�zsdei id�sort reprezent�l.
//az adatokat l�ncolt list�ban t�roljuk.

class TimeSeries
{
	list<Bar> series;
	vector<IndicatorBase*> indicators;
	static int indCount;

	friend IndicatorBase;
public:
	void readFromFile(const char* filename);
	void printData(int n = -1);
	int addInd(IndicatorBase *ind);
	void calculateIndicators();
	void matlabPlot(unsigned int num);
	double * priceToArray(OHLC ohlc_, unsigned int num);
	double* indDataToArray(unsigned id, unsigned int num);
	~TimeSeries();
};
