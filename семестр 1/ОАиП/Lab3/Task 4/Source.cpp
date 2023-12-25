#include <iostream>
using namespace std;
int main() {
	long double b, sum = 0, Sum, A;
	long long a = 1, B;
	cin >> b;
	B = b;
	while (a < b)
	{
		a++;
		if (a % 2 == 0)
			sum += a;

	}
	cout << sum << "\n";            //с циклом

	A = 2;

	if (B % 2 != 0)
		B -= 1;
	if (B % 4 == 0)
		Sum = (A + B) / 4 * B + B / 2;
	else
		Sum = (A + B) / 4 * B;
	cout << Sum;
	return 0;
}