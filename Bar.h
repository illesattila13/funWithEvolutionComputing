#pragma once
#include "time.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/*bar:
-dátum, idõ
-open
-high
-low
-close
*/

struct Bar
{
	Time t;
	/*double open;
	double high;
	double low;
	double close;*/
	double ohlc[4];
	int vol;
	vector<double> indDatas;
};

ostream& operator<<(ostream& os, Bar& b);
