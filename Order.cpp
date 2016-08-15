#include "Order.h"

double Order::spread = 0.00020;

Order::Order(double openPrice_, OrderType orderType_, double lotSize_, double takeProfit_ , double stopLoss_ , double trailingStop_ ):
	orderType(orderType_),
	lotSize(lotSize_),
	trailingStop(trailingStop_)
{
	if (orderType == SELL)
	{
		openPrice = openPrice_ - spread;
		takeProfit = openPrice - takeProfit_;
		stopLoss = openPrice + stopLoss_;
	}
	else if (orderType == BUY)
	{
		openPrice = openPrice_ + spread;
		takeProfit = openPrice + takeProfit_;
		stopLoss = openPrice - stopLoss_;
	}
	if (trailingStop_ > 0)
	{
		if (orderType == SELL)
		{
			stopLoss = openPrice + trailingStop;
		}
		else if (orderType == BUY)
		{
			stopLoss = openPrice - trailingStop;
		}
	}
	else
	{
		
	}
}

bool Order::evalOrder(double price)
{
	//nem vesszük figyelembe
	return true;///////////////////////////////////////////////////////////////////////////////////
	if (trailingStop < 0 )
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

OrderType Order::getOrderTyoe()
{
	return orderType;
}
