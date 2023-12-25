#include <iostream>          //////    ax^4 + bx^2 + c	
#include <cmath>             //        ax^4 + bx^3 + cx^2 + bx + a
using namespace std;                   //////   x^3 + px + q
int main() {
	setlocale(LC_ALL, "russian");
	long double a, b, c, p, q, n, x1, x2, x3, x4;
	cout << "Выберерите уравнение\n" << "ax^4 + bx^2 + c\n" << "ax^4 + bx^3 + cx^2 + bx + a\n" << "x^3 + px + q\n";
	cin >> n;
	if (n == 1)
	{
		cout << "ax^4 + bx^2 + c\n"<< "Введите a, b, c\n";
		cin >> a >> b >> c;
		if (a != 0 and b != 0 and c != 0)
		{
			x1 = sqrt((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
			x2 = sqrt((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
			x3 = -sqrt((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
			x4 = -sqrt((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
			if (-b + sqrt(b * b - 4 * a * c) >= 0 and -b + sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x1 << " " << x3 << " " << x2 << " " << x4;
			else if (-b + sqrt(b * b - 4 * a * c) >= 0 and -b + sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x1 << " " << x3;
			else if (-b - sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x2 << " " << x4;
			else
				cout << "Нельзя решить первое уравнение";
		}
		else if (a == 0 and b != 0 and c != 0 and -c >= 0)
		{
			if (-c / b >= 0)
			{
				x1 = sqrt(-c / b);
				x2 = -sqrt(-c / b);
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x1 << " " << x2;
			}
			else 
			{
				cout << "Нельзя решить первое уравнение";
			}
		}
		else if (a == 0 and b == 0 and c != 0)
		{
			cout << "Нет корней";
		}
		else if (a == 0 and b == 0 and c == 0)
		{
			cout << "Уравнение умеет бесконечное множество решений";
		}
		else if (a != 0 and b == 0 and c != 0)
		{
			if (-c / a >= 0)
			{
				x1 = sqrt(sqrt(-c / a));
				x2 = -sqrt(sqrt(-c / a));
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x1 << " " << x2;
			}
			else
			{
				cout << "Нельзя решить первое уравнение";
			}
		}
		else if ((a == 0 and b != 0 and c == 0) or (a != 0 and b == 0 and c == 0))
		{
			cout << "Корень уравнения ax^4 + bx^2 + c\n" << "0";
		}
		else if (a != 0 and b != 0 and c == 0)
		{
			x1 = 0;
			if (-b / a >= 0)
			{
				x2 = sqrt(-c / b);
				x3 = -sqrt(-c / b);
				cout << "Корни уравнения ax^4 + bx^2 + c\n" << x1 << " " << x2 << " " << x3;
			}
			else
			{
				cout << "Корень уравнения ax^4 + bx^2 + c\n" << x1;
			}

		}
		else
		{
			cout << "Нельзя решить первое уравнение";
		}
	}
	long double y10, y20, y1, y2, y3, y4;
	if (n == 2)                               //        ax^4 + bx^3 + cx^2 + bx + a
	{
		cout << "ax^4 + bx^3 + cx^2 + bx + a\n" << "Введите a, b, c\n";
		cin >> a >> b >> c;
		if ((a != 0 and b != 0 and c != 0) or (a != 0 and b != 0 and c == 0))
		{
			y10 = (-b + sqrt(b * b - 4 * a * (c - 2 * a))) / (2 * a);
			y20 = (-b - sqrt(b * b - 4 * a * (c - 2 * a))) / (2 * a);
			y1 = (y10 + sqrt(y10 * y10 - 4)) / 2;
			y2 = (y10 - sqrt(y10 * y10 - 4)) / 2;
			y3 = (y20 + sqrt(y20 * y20 - 4)) / 2;
			y4 = (y20 - sqrt(y20 * y20 - 4)) / 2;
			if ((b * b - 4 * a * (c - 2 * a)) / (2 * a)>=0 and y10 * y10 - 4>=0 and y20 * y20 - 4>=0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << y1 << " " << y2 << " " << y3 << " " << y4;
			else if ((b * b - 4 * a * (c - 2 * a)) / (2 * a)>=0 and y10 * y10 - 4>=0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << y1 << " " << y2;
			else if ((b * b - 4 * a * (c - 2 * a)) / (2 * a) >= 0 and y20 * y20 - 4 >= 0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << y3 << " " << y4;
			else
				cout << "Нельзя решить второе уравнение";
		}
		else if (a == 0 and b != 0 and c != 0)
		{
			y1 = 0;
			y2 = -c + sqrt(c * c - 4 * b * b)/(2 * b);
			y3 = -c - sqrt(c * c - 4 * b * b)/(2*b);
			if (c * c - 4 * b * b >= 0)
			{
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << y1 << " " << y2 << " " << y3;
			}
			else
			{
				cout << "Корень уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << y1;
			}
		}
		else if (a == 0 and b == 0 and c != 0)
		{
			cout << "Корень уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << "0";	
		}
		else if (a == 0 and b == 0 and c == 0)
		{
			cout << "Уравнение умеет бесконечное множество решений";
		}
		else if (a != 0 and b == 0 and c != 0)
		{
			b = c;
			c = a;
			x1 = sqrt((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
			x2 = sqrt((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
			x3 = -sqrt((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
			x4 = -sqrt((-b - sqrt(b * b - 4 * a * c)) / (2 * a));
			if (-b + sqrt(b * b - 4 * a * c) >= 0 and -b + sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << x1 << " " << x3 << " " << x2 << " " << x4;
			else if (-b + sqrt(b * b - 4 * a * c) >= 0 and -b + sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << x1 << " " << x3;
			else if (-b - sqrt(b * b - 4 * a * c) >= 0 and -b - sqrt(b * b - 4 * a * c) >= 0)
				cout << "Корни уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << x2 << " " << x4;
			else
				cout << "Нельзя решить второе уравнение";
		}
		else if (a == 0 and b != 0 and c == 0)
		{
			cout << "Корень уравнения ax^4 + bx^3 + cx^2 + bx + a\n" << "0";
		}
		else if (a != 0 and b == 0 and c == 0)
		{
			cout << "Нельзя решить второе уравнение";
		}
		else
		{
			cout << "Нельзя решить второе уравнение";
		}
	}
	long double z1, z2, z3, E, Pi = acos(-1), L;
	if (n == 3)        //////   x^3 + px + q
	{
		cout << "x^3 + px + q\n" << "Введите p, q\n";
		cin >> p >> q;
		if (p == 0 and q == 0)
		{
			cout << "Корень уравнения x^3 + px + q\n" << "0";
		}
		else if (p == 0 and q != 0)
		{
			z1 = pow(q, 1 / 3);
			cout << "Корень уравнения x^3 + px + q\n" << z1;
		}
		else if (p != 0 and q == 0)
		{
			z1 = 0;
			z2 = sqrt(p);
			z3 = -sqrt(p);
			if (p < 0)
			{
				cout << "Корни уравнения x^3 + px + q\n" << z1 << " " << z2 << " " << z3;
			}
			else 
				cout << "Корень уравнения x^3 + px + q\n" << z1;
		}
		else
		{
			E = p * p * p / 27 + q * q / 4;
			if (E > 0)
			{
				E = powl(-q / 2 + sqrtl(E), 1.0 / 3) + (-q / 2 - sqrtl(E) > 0 ? powl(-q / 2 - sqrtl(E), 1.0 / 3) : -powl(q / 2 + sqrtl(E), 1.0 / 3));
				cout << "Корень уравнения x^3 + px + q\n";
				cout << E << "\n";
			}
			else
			{
				L = acos(-(q / 2) * powl(3 / -p, 1.5));
				z1 = 2 * sqrtl(-p / 3) * cos(L / 3);
				z2 = 2 * sqrtl(-p / 3) * cos(L / 3 + 2 * Pi / 3);
				z3 = 2 * sqrtl(-p / 3) * cos(L / 3 - 2 * Pi / 3);
				cout << "Корни уравнения x^3 + px + q\n";
				cout << z1 << " " << z2 << " " << z3;
			}
		}
	}
	return 0;
}