#pragma once
#include <list>
#include "Bar.h"

/*
Base class for indicators. 
*/

class IndicatorBase
{
protected:
	unsigned int id;
	unsigned int calculated;
public:
	IndicatorBase();
	/**
	Calculate the indicator data.
	@return: the number of calculated data. 
	*/
	
	virtual int calculate(list<Bar>& series) = 0;
	
	void setId(unsigned int id_);

};
