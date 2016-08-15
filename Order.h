#pragma once
#include <list>
#include "Bar.h"
#include "Enums.h"

using namespace std;
class Order
{
	OrderType orderType;
	double lotSize;
	double openPrice;
	double closePrice;
	double stopLoss;
	double takeProfit;
	double trailingStop;
	static double spread;
public:
	Order(double openPrice_, OrderType orderType_, double lotSize_, double takeProfit_ = -1, double stopLoss_ = -1, double trailingStop_ = -1);
	bool evalOrder(double price);
	double closeOrder(double price);
	void setTrailingStop(double tStop_);
	double getTrailingStop();
	void setStopLoss(double stopLoss_);
	double getStopLoss();
	void setTakeProfit(double takeProfit_);
	double getTakeProfit();
	OrderType getOrderTyoe();

};
