#pragma once
#include <list>
#include "Bar.h"
#include <iostream>
#include "IndicatorBase.h"
#include <vector>
#include "Enums.h"

using namespace std;

//ez az osztály egy tõzsdei idõsort reprezentál.
//az adatokat láncolt listában tároljuk.

class TimeSeries
{
	list<Bar> series;
	vector<IndicatorBase*> indicators;
	static int indCount;
	int barCount;

	friend IndicatorBase;
public:
	TimeSeries();
	int getBarCount();
	void readFromFile(const char* filename);
	void printData(int n = -1);
	int addInd(IndicatorBase *ind);
	void calculateIndicators();
	void matlabPlot(unsigned int num);
	double * priceToArray(OHLC ohlc_, unsigned int num);
	double* indDataToArray(unsigned id, unsigned int num);
	const list<Bar>& getSeries();
	~TimeSeries();
};
