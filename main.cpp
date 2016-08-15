#include "timeSeries.h"
#include "Indicators.h"
#include "PriceCrossMA.h"
#include <iostream>

using namespace std;

int main()
{
	TimeSeries ts;
	ts.readFromFile("EURUSD60.csv");
	//ts.readFromFile("test.csv");
	/*ts.addInd(new Indicator::SimpleMovingAverage(10));
	ts.addInd(new Indicator::ExponentialMovingAverage(0.8));
	ts.addInd(new Indicator::SmoothedMovingAverage(3));
	ts.calculateIndicators();
	ts.matlabPlot(50);
	ts.printData(50);*/

	//	PriceCrossMA(list<Bar>& series_, double deposit_, int MAPer_, double takeProfit_, double stopLoss_, double trailingStop_);

	PriceCrossMA simulation(ts.getSeries(), 100, 100, -1, -1, -1);
	double profit = simulation.trade();
	cout << profit << endl;
}