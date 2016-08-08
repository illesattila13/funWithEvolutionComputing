#pragma once
#include <list>
#include "Bar.h"
#include <iostream>
#include "IndicatorBase.h"
#include <vector>

using namespace std;

//ez az osztály egy tõzsdei idõsort reprezentál.
//az adatokat láncolt listában tároljuk.

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
