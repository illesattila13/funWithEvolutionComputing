#pragma once
#include <list>
#include "Bar.h"
#include <iostream>

using namespace std;

//ez az osztály egy tõzsdei idõsort reprezentál.
//az adatokat láncolt listában tároljuk.

class TimeSeries
{
	list<Bar> series;
public:
	void readFromFile(const char* filename);
	void printData()
	{
		list<Bar>::iterator it;
		for (it = series.begin(); it != series.end(); ++it)
		{
			cout << *it << endl;
		}
	}
};
