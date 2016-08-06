#pragma once
#include "time.h"
#include <iostream>
#include <iomanip>

using namespace std;

/*bar:
-d�tum, id�
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
