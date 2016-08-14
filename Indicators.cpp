#include "Indicators.h"
///////////////////////////////////////////////////////////////////////////////////////////
Indicator::SimpleMovingAverage::SimpleMovingAverage(unsigned int N_, OHLC ohlc_): N(N_), ohlc_param(ohlc_)
{

}

int Indicator::SimpleMovingAverage::calculate(const list<Bar>& series)
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

int Indicator::SimpleMovingAverage::calculate(const list<Bar>& series, vector<double>& indData)
{
	list<Bar>::iterator back, front;
	back = front = series.begin();
	double Nsum = 0.0;
	double avg;
	int idx = 0;

	while (front != series.end())
	{
		Nsum += front->ohlc[ohlc_param];
		indData.resize(series.size());


		if (calculated > (N - 1))
		{
			Nsum -= back->ohlc[ohlc_param];
			++back;
			avg = Nsum / N;
			indData[idx] = avg;

		}
		else if (calculated == (N - 1))
		{
			avg = Nsum / N;
			indData[idx] = avg;


		}
		++idx;
		++front;
		++calculated;

	}
	return calculated;
}

/////////////////////////////////////////////////////////////////////////////////////////////
Indicator::ExponentialMovingAverage::ExponentialMovingAverage(double P_, OHLC ohlc_): P(P_),ohlc_param(ohlc_), pre(0.0)
{

}

int Indicator::ExponentialMovingAverage::calculate(const list<Bar>& series)
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

int Indicator::ExponentialMovingAverage::calculate(const list<Bar>& series, vector<double>& indData)
{
	indData.resize(series.size());
	int idx = 0;
	for (list<Bar>::iterator it = series.begin(); it != series.end(); ++it)
	{
		
		if (calculated == 0)
		{
			pre = it->ohlc[ohlc_param];
			indData[idx++] = pre;
			++calculated;
			continue;

		}


		pre = indData[idx++] = ((it->ohlc[ohlc_param] * P) + pre*(1 - P));
		++calculated;
	}
	return calculated;
}

////////////////////////////////////////////////////////////////////////////////////////////////
Indicator::SmoothedMovingAverage::SmoothedMovingAverage(unsigned int N_, OHLC ohlc_): N(N_), ohlc_param(ohlc_), pre(0.0)
{
}

int Indicator::SmoothedMovingAverage::calculate(const list<Bar>& series)
{
	double Nsum = 0.0;

	for (list<Bar>::iterator it = series.begin(); it != series.end(); ++it)
	{
		it->indDatas.resize(id + 1);
		if (calculated > (N - 1))
		{
			pre = it->indDatas[id] = (pre * (N - 1) + it->ohlc[ohlc_param]) / N;
		}
		else if (calculated < (N - 1))
		{
			Nsum += it->ohlc[ohlc_param];
		}
		else if (calculated == (N - 1))
		{
			Nsum += it->ohlc[ohlc_param];
			pre = it->indDatas[id] = Nsum / N;
		}
		++calculated;
	}


	return 0;
}

int Indicator::SmoothedMovingAverage::calculate(const list<Bar>& series, vector<double>& indData)
{
	double Nsum = 0.0;
	int idx = 0;
	for (list<Bar>::iterator it = series.begin(); it != series.end(); ++it)
	{
		indData.resize(series.size());
		if (calculated > (N - 1))
		{
			pre = indData[idx] = (pre * (N - 1) + it->ohlc[ohlc_param]) / N;
		}
		else if (calculated < (N - 1))
		{
			Nsum += it->ohlc[ohlc_param];
		}
		else if (calculated == (N - 1))
		{
			Nsum += it->ohlc[ohlc_param];
			pre = indData[idx] = Nsum / N;
		}
		++idx;
		++calculated;
	}
	return calculated;
}
