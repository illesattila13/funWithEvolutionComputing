#pragma once
#include "time.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;



struct Bar
{
	Time t;
	
	double ohlc[4];
	int vol;
	vector<double> indDatas;
};

ostream& operator<<(ostream& os, Bar& b);
