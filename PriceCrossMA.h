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
	double deposit;
	int MAPeriod;
	vector<double> MA;
	list<Bar> &series;
	Order* actOrder;
	double takeProfit;
	double stopLoss;
	double trailingStop;
	double profit;


public:
	PriceCrossMA(list<Bar>& series_, double deposit_, int MAPer_, double takeProfit_, double stopLoss_, double trailingStop_);
	double trade();
};