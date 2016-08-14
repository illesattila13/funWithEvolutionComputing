#pragma once

#include "IndicatorBase.h"
#include "Enums.h"
#include <list>
#include "Bar.h"


using namespace std;

namespace Indicator
{
	class SimpleMovingAverage : public IndicatorBase
	{
		unsigned int N;
		OHLC ohlc_param;
		//unsigned int calculated;
	public:
		SimpleMovingAverage(unsigned int N_, OHLC ohlc_ = C);
		int calculate(list<Bar>& series);
		int calculate(list<Bar>& series, vector<double>& indData);
	};

	class ExponentialMovingAverage : public IndicatorBase
	{
		double P;
		double pre;
		OHLC ohlc_param;
	public:
		ExponentialMovingAverage(double P_, OHLC ohlc_ = C);
		int calculate(list<Bar>& series);
		int calculate(list<Bar>& series, vector<double>& indData);
	};

	class SmoothedMovingAverage : public IndicatorBase
	{
		unsigned int N;
		OHLC ohlc_param;
		double pre;
	public:
		SmoothedMovingAverage(unsigned int N_, OHLC ohlc_ = C);
		int calculate(list<Bar>& series);
		int calculate(list<Bar>& series, vector<double>& indData);
	};
}