#pragma once
#include <vector>

using namespace std;

class TradingRuleBase
{
	vector<int> myIndIDs;
public:
	TradingRuleBase() : myIndIDs(5) {}
	virtual double runTrade() = 0;
};