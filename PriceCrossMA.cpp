#include "PriceCrossMA.h"
#include "timeSeries.h"

PriceCrossMA::PriceCrossMA(int MAPer_, list<Bar>& series_, double money_):
	MAPeriod(MAPer_),
	series(series_),
	money(money_),
	actOrder(nullptr),
	isOrder(false)
{
	Indicator::SimpleMovingAverage sma(MAPeriod);
	sma.calculate(series, MA);
}

double PriceCrossMA::trade()
{
	list<Bar>::iterator it = series.begin();
	advance(it, MAPeriod);
	for (it; it != series.end(); ++it)
	{

	}

	return 0.0;
}
