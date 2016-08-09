#include "timeSeries.h"
#include "Indicators.h"

int main()
{
	TimeSeries ts;
	//ts.readFromFile("EURUSD1.csv");
	ts.readFromFile("test.csv");
	ts.addInd(new Indicator::SimpleMovingAverage(3));
	ts.addInd(new Indicator::ExponentialMovingAverage(0.8));
	ts.addInd(new Indicator::SmoothedMovingAverage(3));
	ts.calculateIndicators();
	ts.printData(-3);
}