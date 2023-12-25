#include <iostream>            //10 вариант
using namespace std;
int main() {
	long double k, x, n, s, y, sum=0;
	int i=1,a=0;
	cin >> n >> k;
	while (i <= k)
	{
		cin >> x;
		if (x >= 0.1 and x <= 1)
		{
			i++;
			y = atan(x);
			
			while (a < n)

			{
				
				s = pow(-1, a) * pow(x, 2 * a + 1) / (2 * a + 1);
				sum += s;
				a++;
			}
			x = 0;
			cout << y << " " << sum << "\n";
			sum = 0;
			a = 0;
		}
		else
			cout << "ERROR\n";
	}
	return 0;
}