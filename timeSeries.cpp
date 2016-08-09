#include "timeSeries.h"
#include <fstream>

#include "engine.h"


using namespace std;

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

void TimeSeries::matlabPlot()
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
	mxArray *high = mxCreateDoubleMatrix(1, series.size(), mxREAL);
	mxArray *low = mxCreateDoubleMatrix(1, series.size(), mxREAL);
	mxArray *close = mxCreateDoubleMatrix(1, series.size(), mxREAL);
	mxArray *open = mxCreateDoubleMatrix(1, series.size(), mxREAL);

	memcpy((void*)mxGetPr(high),	(void*)priceToArray(H), series.size()*sizeof(double));
	memcpy((void*)mxGetPr(low),		(void*)priceToArray(L), series.size()*sizeof(double));
	memcpy((void*)mxGetPr(close),	(void*)priceToArray(C), series.size()*sizeof(double));
	memcpy((void*)mxGetPr(open),	(void*)priceToArray(O), series.size()*sizeof(double));



	/*delete[] open;
	delete[] high;
	delete[] close;
	delete[] low;*/

	/*
	* Place the variable data into the MATLAB workspace
	*/
	engPutVariable(ep, "high", high);
	engPutVariable(ep, "low",low );
	engPutVariable(ep, "close",close );
	engPutVariable(ep, "open",open );


	engEvalString(ep, "candle(high', low', close', open','red' )");
	engEvalString(ep, "zoom xon");
	engEvalString(ep, "zoom yon");
}

/*
@return: a pointer to a array in the heap
THE CALLER MUST FREE IT!!!!!!!!!!!!!!!!!!!!!!!
*/
double * TimeSeries::priceToArray(OHLC ohlc_)
{
	double *prices = new double[series.size()];
	int i = 0;
	for (list<Bar>::iterator it = series.begin(); it != series.end(); ++it, ++i)
	{
		prices[i] = it->ohlc[ohlc_];
	}
	return prices;
}

TimeSeries::~TimeSeries()
{
	for (IndicatorBase* inds : indicators)
	{
		delete inds;
	}
}
