#pragma once
#include <list>
#include "Bar.h"
#include <iostream>
#include "IndicatorBase.h"
#include <vector>

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
	void printData();
	int addInd(IndicatorBase *ind);
	void calculateIndicators();
	~TimeSeries();
};
