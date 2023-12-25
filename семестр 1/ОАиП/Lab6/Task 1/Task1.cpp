#include <iostream>
using namespace std;
#define ll long long
int Task1() {
	cout << "Введите строку ";
	char a[80];
	ll x=0;
	ll q;
	cin >> q;
	for (ll i = 0; (a[i] = getchar()) != '\n'; i++);
	for (ll q = 0; q < 80; q++)
	{
		if (a[q] == '{' or a[q] == '}' or a[q] == '[' or a[q] == ']' or a[q] == '(' or a[q] == ')' or a[q] == '<' or a[q] == '>')
			x++;
	}
	cout << "Количество скобок различного вида " << x << endl;
	return 0;
}