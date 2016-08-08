#include "timeSeries.h"
#include "Indicators.h"

int main()
{
	TimeSeries ts;
	ts.readFromFile("EURUSD1.csv");
	ts.addInd(new SimpleMovingAverage(3));
	ts.calculateIndicators();
	ts.printData();
}