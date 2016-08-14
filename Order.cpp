#include "Order.h"

double Order::spread = 0.00050;

Order::Order(double openPrice_, OrderType orderType_, double lotSize_):
	orderType(orderType_),
	lotSize(lotSize_),
	stopLoss(-1),
	takeProfit(-1),
	trailingStop(-1)
{
	if (orderType == SELL)
	{
		openPrice = openPrice_ + spread;
	}
	else if (orderType == BUY)
	{
		openPrice = openPrice_ - spread;
	}
}

bool Order::evalOrder(double price)
{
	if (trailingStop < 0 && stopLoss >=0)
	{
		if (orderType == SELL)
		{
			if (price >= stopLoss && price <= takeProfit)
			{
				return false;
			}
			else 
			{
				return true;
			}
		}
		if (orderType == BUY)
		{
			if (price <= stopLoss && price >= takeProfit)
			{
				return false;
			}
			else 
			{
				return true;
			}
		}
	}
	else
	{
		if (orderType == SELL)
		{
			if ((stopLoss - price) > trailingStop)
			{
				stopLoss = price + trailingStop;
			}
			if (price >= stopLoss)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (orderType == BUY)
		{
			if ((stopLoss - price) > trailingStop)
			{
				stopLoss = price - trailingStop;
			}
			if (price <= stopLoss)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

double Order::closeOrder(double price)
{
	closePrice = price;
	if (orderType == SELL)
	{
		return (openPrice - price) * 1000 * lotSize;
	}
	else if( orderType == BUY)
	{
		return (price - openPrice) * 1000 * lotSize;
	}
}

void Order::setTrailingStop(double tStop_)
{
	trailingStop = tStop_;
}

double Order::getTrailingStop()
{
	return trailingStop;
}

void Order::setStopLoss(double stopLoss_)
{
	stopLoss = stopLoss_;
}

double Order::getStopLoss()
{
	return stopLoss;
}

void Order::setTakeProfit(double takeProfit_)
{
	takeProfit = takeProfit_;
}

double Order::getTakeProfit()
{
	return takeProfit;
}
