#include "timeSeries.h"

int main()
{
	TimeSeries ts;
	ts.readFromFile("EURUSD1.csv");
	ts.printData();
}