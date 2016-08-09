#include "Indicators.h"

Indicator::SimpleMovingAverage::SimpleMovingAverage(unsigned int N_, OHLC ohlc_): N(N_), ohlc_param(ohlc_)
{

}


int Indicator::SimpleMovingAverage::calculate(list<Bar>& series)
{
	list<Bar>::iterator back, front;
	back = front = series.begin();
	double Nsum = 0.0;
	double avg;


	while (front != series.end())
	{
		Nsum += front->ohlc[ohlc_param];
		front->indDatas.resize(id+1);

		
		if(calculated > (N - 1) )
		{
			Nsum -= back->ohlc[ohlc_param];
			++back;
			avg = Nsum / N;
			front->indDatas[id] = avg;
			
		}
		else if (calculated == (N - 1))
		{
			avg = Nsum / N;
			front->indDatas[id] = avg;
			
			
		}
		++front;
		++calculated;
		
	}
	return calculated;
}

Indicator::ExponentialMovingAverage::ExponentialMovingAverage(double P_, OHLC ohlc_): P(P_),ohlc_param(ohlc_), pre(0.0)
{

}


int Indicator::ExponentialMovingAverage::calculate(list<Bar>& series)
{
	for (list<Bar>::iterator it = series.begin(); it != series.end(); ++it)
	{
		it->indDatas.resize(id + 1);
		if (calculated == 0)
		{
			pre = it->ohlc[ohlc_param];
			it->indDatas[id] = pre;
			++calculated;
			
		}

		
		pre = it->indDatas[id] = ( (it->ohlc[ohlc_param] * P) + pre*(1 - P) );
		++calculated;
	}
	return calculated;
}
