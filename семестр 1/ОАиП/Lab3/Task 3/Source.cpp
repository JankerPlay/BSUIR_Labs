#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int i;
	long double y, X=0, A = 0, B, H, M = 20, Pi;
	Pi = acos(-1);
	B = Pi / 2;
	H = (B - A) / M;
	for (i = 0; X < Pi / 2; i++)
	{
		X = A + i * H;
		y = sin(X) - cos(X);
		cout << y << "\n";
	}
	return 0;
}