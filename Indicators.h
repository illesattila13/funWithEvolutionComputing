#pragma once

#include "IndicatorBase.h"
#include "PriceEnums.h"
#include <list>
#include "Bar.h"


using namespace std;

class SimpleMovingAverage : public IndicatorBase
{
	unsigned int N;
	OHLC ohlc_param;
	unsigned int calculated;
public:
	SimpleMovingAverage(unsigned int N_, OHLC ohlc_ = C);

    
	int calculate(list<Bar>& series);
};