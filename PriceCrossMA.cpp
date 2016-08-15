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
	double prevMA, prevPrice;
	int MAidx = MAPeriod;
	prevMA = MA[MAidx++];
	prevPrice = it->ohlc[C];
	++it;
	for (; it != series.end(); ++it, ++MAidx)
	{
		if (prevMA > prevPrice && MA[MAidx] < it->ohlc[C])
		{
			if (actOrder != nullptr)
			{

				actOrder = new Order(it->ohlc[C], SELL, 0.1);
			}
		}
	}

	return 0.0;
}
