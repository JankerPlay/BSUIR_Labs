#include <iostream>            //10 вариант
#include <cmath>
using namespace std;
int main() {	
	long double a, x = -1, shag, min=10000000, e = 2.7182818284, b, c;
	cin >> a;
	shag = 1. / a;
	while (x <= 0)
	{
		b = fabs(pow(e, x) * tan(x) + sin(x*x) + 0.1);
		if (b < min)
		{
			min = b;
			c = x;
		}
	
		x += shag;
	}

	cout << c;

		return 0;
}