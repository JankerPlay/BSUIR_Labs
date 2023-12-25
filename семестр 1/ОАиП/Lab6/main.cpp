#include <iostream>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#define ll long long
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите номер задани€(1-4) ";
	ll a = 1;
	while (true) {
		bool Input = true;
		do
		{
			cin >> a;
			Input = false;
			if (cin.peek() != ' ' and cin.peek() != '\n' or a <= -1 or a >= 5)
			{
				cin.clear();
				cin.ignore(80, '\n');
				Input = true;
				cout << "¬ведите число от 1 до 4 ";
			}
		} while (Input);
		if (a == 0)
		{
			return 0;
		}
		else if (a == 1)
		{
			Task1();
		}
		else if (a == 2)
		{
			Task2();
		}
		else if (a == 3)
		{
			Task3();
		}
		else if (a == 4)
		{
			Task4();
		}
	}
	return 0;
}