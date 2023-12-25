#include <iostream>
using namespace std;
int main() {
	int n=1;
	long double d=0, E=0.001,sum=0;
	do {
	
		d = 1 / pow(2, n) + 1 / pow(3, n);
		sum += d;
		n++;
	} while (abs(d)>E);

	cout << sum;
	return 0;
}