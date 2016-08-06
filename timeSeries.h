#pragma once
#include <list>
#include "Bar.h"
#include <iostream>

using namespace std;

//ez az oszt�ly egy t�zsdei id�sort reprezent�l.
//az adatokat l�ncolt list�ban t�roljuk.

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
