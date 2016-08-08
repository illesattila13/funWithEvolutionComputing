#include "Indicators.h"

SimpleMovingAverage::SimpleMovingAverage(unsigned int N_, OHLC ohlc_): N(N_), ohlc_param(ohlc_), calculated(0)
{

}


int SimpleMovingAverage::calculate(list<Bar>& series)
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
