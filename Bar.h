#pragma once
#include "time.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*bar:
-dátum, idõ
-open
-high
-low
-close
*/

struct Bar
{
	Time t;
	double open;
	double high;
	double low;
	double close;
};

ostream& operator<<(ostream& os, Bar& b);
