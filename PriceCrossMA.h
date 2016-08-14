#pragma once
#include "Order.h"
#include <vector>
#include <list>
#include "Bar.h"
#include "Enums.h"
#include "Indicators.h"

using namespace std;

class PriceCrossMA
{
	double money;
	int MAPeriod;
	vector<double> MA;
	list<Bar> &series;
	Order* actOrder;
	bool isOrder;

public:
	PriceCrossMA(int MAPer_, list<Bar>& series_, double money_);
	double trade();
};