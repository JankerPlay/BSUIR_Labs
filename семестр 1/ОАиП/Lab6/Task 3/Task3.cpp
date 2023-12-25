#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
int Task3() {
	char a[100], b[100];
	cout << "Введите первое слово ";
	ll w;
	cin >> w;
	for (ll i = 0; i < 100; i++)
	{
		a[i] = getchar();
		if (a[i] == '\n')
			break;
	}
	ll q;
	cout << "Введите второе слово ";
	cin >> q;
	for (ll i = 0; i < 100; i++)
	{
		b[i] = getchar();
		if (b[i] == '\n')
			break;
	}
	ll size = 100;
	ll code;
	char temp;
	for (ll n = 1; n < size; n++)
	{
		for (ll m = 0; m < size - n; m++)
		{
			if (a[m + 1] - a[m] < 0)
			{
				temp = a[m];
				a[m] = a[m + 1];
				a[m + 1] = temp;
			}
		}
	}
	for (ll n = 1; n < size; n++)
	{
		for (ll m = 0; m < size - n; m++)
		{
			if (b[m + 1] - b[m] < 0)
			{
				temp = b[m];
				b[m] = b[m + 1];
				b[m + 1] = temp;
			}
		}
	}
	for (ll i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			cout << "Не анаграммамы" << endl;
			return 0;
		}
	}
	cout << "Анаграммамы" << endl;
	return 0;
}