#include "PriceCrossMA.h"
#include "timeSeries.h"
#include <iostream>
#include <fstream>
using namespace std;

PriceCrossMA::PriceCrossMA(list<Bar>& series_, double deposit_, int MAPer_, double takeProfit_, double stopLoss_, double trailingStop_):
	MAPeriod(MAPer_),
	series(series_),
	deposit(deposit_),
	actOrder(nullptr),
	takeProfit(takeProfit_),
	stopLoss(stopLoss_),
	trailingStop(trailingStop_),
	profit(0.0)
{
	Indicator::SimpleMovingAverage sma(MAPeriod);
	sma.calculate(series, MA);
}

double PriceCrossMA::trade()
{
	ofstream file("out.txt");

	list<Bar>::iterator it = series.begin();
	advance(it, MAPeriod);
	double prevMA, prevPrice, ret;
	int MAidx = MAPeriod;
	prevMA = MA[MAidx++];
	prevPrice = it->ohlc[C];
	++it;
	for (; it != series.end(); ++it, ++MAidx)
	{
		if (actOrder != nullptr)
		{
			if (actOrder->evalOrder(it->ohlc[C]) == false)
			{
				profit += actOrder->closeOrder(it->ohlc[C]);
				cout << profit << endl;
				delete actOrder;
				actOrder = nullptr;
			}
		}
		if (prevMA < prevPrice && MA[MAidx] > it->ohlc[C]) // SELL signal
		{
			if (actOrder != nullptr)
			{
				profit += ret = actOrder->closeOrder(it->ohlc[C]);
				file << it->t.y << " " << it->t.m << " " << it->t.d << " " << it->t.h << " " << it->t.min << " | " << "CLOSE " << it->ohlc[C] <<" profit: "<<ret<< endl;
				cout << profit << endl;
				delete actOrder;
			}
				actOrder = new Order(it->ohlc[C], SELL, 1, takeProfit, stopLoss, trailingStop);
				file << it->t.y << " " << it->t.m << " " << it->t.d << " " << it->t.h << " " << it->t.min << " | " << "SELL " << it->ohlc[C] << endl;
		}
		else if (prevMA > prevPrice && MA[MAidx] < it->ohlc[C]) // BUY signal
		{
			if (actOrder != nullptr)
			{
				profit +=ret = actOrder->closeOrder(it->ohlc[C]);
				file << it->t.y << " " << it->t.m << " " << it->t.d << " " << it->t.h << " " << it->t.min << " | " << "CLOSE " << it->ohlc[C] << " profit: " << ret << endl;
				cout << profit << endl;
				delete actOrder;
			}
			actOrder = new Order(it->ohlc[C], BUY, 1, takeProfit, stopLoss, trailingStop);
			file << it->t.y << " " << it->t.m << " " << it->t.d << " " << it->t.h << " " << it->t.min << " | " << "BUY " << it->ohlc[C] << endl;
		}
		prevMA = MA[MAidx];
		prevPrice = it->ohlc[C];
	}
	int a;
	a = 3 + 5;

	return profit;
}
