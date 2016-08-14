#include "PriceCrossMA.h"

PriceCrossMA::PriceCrossMA(int MAPer_, list<Bar>& series_, double money_):
	MAPeriod(MAPer_),
	series(series_),
	money(money_)
{
	Indicator::SimpleMovingAverage sma(MAPeriod);
	sma.calculate(series, MA);
}

double PriceCrossMA::trade()
{
	return 0.0;
}
