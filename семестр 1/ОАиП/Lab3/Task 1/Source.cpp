#include <iostream>
using namespace std;
int main() {
	int i=1, n=1;
	long double a, b, N, sum=0;
	while (n<=29)
	{
		n++;
		i++;
	if (i % 2 == 0)
	{
		b = i * i * i;
		a = i / 2;
	}
	else
	{
		b = i * i;
		a = i;
	}
	N = (a - b) * (a - b);
	sum += N;
	}
	cout << sum;
	return 0;
}