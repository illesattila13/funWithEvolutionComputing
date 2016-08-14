#include "timeSeries.h"
#include <fstream>

#include "engine.h"


using namespace std;

TimeSeries::TimeSeries(): barCount(0)
{
}

int TimeSeries::getBarCount()
{
	return barCount;
}

void TimeSeries::readFromFile(const char * filename)
{
	ifstream ifile(filename);
	Bar bar;
	char c;
	while (ifile >> bar.t.y >> c
		>> bar.t.m >> c
		>> bar.t.d >> c
		>> bar.t.h >> c
		>> bar.t.min >> c
		>> bar.ohlc[0] >> c
		>> bar.ohlc[1] >> c
		>> bar.ohlc[2] >> c
		>> bar.ohlc[3] >> c >> bar.vol)
	{
		
		series.push_back(bar);
		++barCount;
	}
}

void TimeSeries::printData(int n)
{
	list<Bar>::iterator it;
	if (n >= 0)
	{
		it = series.end();
		advance(it, -n);
	}
	else
	{
		it = series.begin();
	}
	for (it ; it != series.end(); ++it)
	{
		cout << *it << endl;
	}
}

int TimeSeries::indCount = 0;

int TimeSeries::addInd(IndicatorBase * ind)
{
	ind->setId(indCount++);
	indicators.push_back(ind);
	return indCount;
}

void TimeSeries::calculateIndicators()
{
	for (IndicatorBase* inds : indicators)
	{
		inds->calculate(series);
	}
}

void TimeSeries::matlabPlot(unsigned int num)
{

	Engine *ep;

	/*
	* Call engOpen with a NULL string. This starts a MATLAB process
	* on the current host using the command "matlab".
	*/
	if (!(ep = engOpen(""))) 
	{
		cerr<< "\nCan't start MATLAB engine\n";
		return;
	}
	mxArray *high = mxCreateDoubleMatrix(1, num, mxREAL);
	mxArray *low = mxCreateDoubleMatrix(1, num, mxREAL);
	mxArray *close = mxCreateDoubleMatrix(1, num, mxREAL);
	mxArray *open = mxCreateDoubleMatrix(1, num, mxREAL);
	mxArray *indicator = mxCreateDoubleMatrix(1, num, mxREAL);

	double *h, *l, *o, *c, *ind;

	h=priceToArray(H, num);
	l=priceToArray(L, num);
	c=priceToArray(C, num);
	o=priceToArray(O, num);
	ind = indDataToArray(0, num);


	memcpy((void*)mxGetPr(high),	(void*)h, num*sizeof(double));
	memcpy((void*)mxGetPr(low),		(void*)l, num*sizeof(double));
	memcpy((void*)mxGetPr(close),	(void*)c, num*sizeof(double));
	memcpy((void*)mxGetPr(open),	(void*)o, num*sizeof(double));
	memcpy((void*)mxGetPr(indicator),(void*)ind, num * sizeof(double));

	delete[] h;
	delete[] l;
	delete[] c;
	delete[] o; 
	delete[] ind;
	/*
	* Place the variable data into the MATLAB workspace
	*/
	engPutVariable(ep, "high", high);
	engPutVariable(ep, "low",low );
	engPutVariable(ep, "close",close );
	engPutVariable(ep, "open",open );
	engPutVariable(ep, "indicator", indicator);


	engEvalString(ep, "candle(high', low', close', open','green' )");
	engEvalString(ep, "hold on");
	engEvalString(ep, "grid on");
	engEvalString(ep, "plot(indicator,'Linewidth',2)");
	engEvalString(ep, "set(gca,'Color','black')");

}

/*
@return: a pointer to a array in the heap
THE CALLER MUST FREE IT!!!!!!!!!!!!!!!!!!!!!!!
*/
double * TimeSeries::priceToArray(OHLC ohlc_, unsigned int num)
{
	double *prices = new double[num];
	int i = 0;
	list<Bar>::iterator it = series.end(); 
	int n = num;
	advance(it, -n);
	for (; it != series.end(); ++it, ++i)
	{
		prices[i] = it->ohlc[ohlc_];
	}
	return prices;
}

double * TimeSeries::indDataToArray(unsigned id, unsigned int num)
{

	double *values = new double[num];
	int i = 0;
	list<Bar>::iterator it = series.end();
	int n = num;
	advance(it, -n);
	for (; it != series.end(); ++it, ++i)
	{
		values[i] = it->indDatas[id];
	}
	return values;
}

 list<Bar>& TimeSeries::getSeries()
{
	return series;
}



TimeSeries::~TimeSeries()
{
	for (IndicatorBase* inds : indicators)
	{
		delete inds;
	}
}
