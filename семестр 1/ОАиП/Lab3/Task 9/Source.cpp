#include <iostream>    
using namespace std;
int main(){
	long long s = 0, a0, d, n, i = 1, an, a;
	cin >> n >> a0 >> d;
	an = a0;
	while (n >= i)
	{	
		a = pow(2, i - 1) * pow(-1, i - 1) * an;
		s += a;
		an = a0 + d * i;
		i++;
	}
	cout << s;
	return 0;
}