#include <iostream>
#include <string>
#define ll long long
using namespace std;
int Task4() {
	string str="1", str1, strc;
	while (str!="0")
	{
		cin >> str1;
		getline(cin, str);
		str = str1 + str;
		strc = str;
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'C' or str[i] == 'Q' or str[i] == 'W' or str[i] == 'X')
			{
				str.erase(i, 1);
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'c')
			{
				if (str[i + 1] == 'e' or str[i + 1] == 'i' or str[i + 1] == 'y')
				{
					str.replace(i, 1, "s");
				}
				else
				{
					str.replace(i, 1, "k");
				}
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'q')
			{
				if (str[i + 1] == 'u')
				{
					str.replace(i, 1, "k");
					str.replace(i + 1, 1, "v");
				}
				else
				{
					str.replace(i, 1, "k");
				}
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'x')
			{
				str.replace(i, 1, "ks");
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'w')
			{
				str.replace(i, 1, "v");
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'p')
			{
				if (str[i + 1] == 'h')
				{
					str.replace(i, 1, "f");
					str.erase(i + 1, 1);
					i--;
				}
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'y' and str[i + 1] == 'o' and str[i + 2] == 'u')
			{
				str.replace(i, 1, "u");
				str.erase(i + 1, 1);
				str.erase(i + 2, 1);
				i--;
			}
			else if (str[i] == 'o' and str[i + 1] == 'o')
			{
				str.replace(i, 1, "u");
				str.erase(i + 1, 1);
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'e' and str[i + 1] == 'e')
			{
				str.replace(i, 1, "i");
				str.erase(i + 1, 1);
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 't' and str[i + 1] == 'h')
			{
				str.replace(i, 1, "z");
				str.erase(i + 1, 1);
				i--;
			}
		}
		for (ll i = 0; i < size(str); i++)
		{
			if (str[i] == 'p' and str[i + 1] == 'p')
			{
				str.replace(i, 1, "p");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'b' and str[i + 1] == 'b')
			{
				str.replace(i, 1, "b");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'k' and str[i + 1] == 'k')
			{
				str.replace(i, 1, "k");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'f' and str[i + 1] == 'f')
			{
				str.replace(i, 1, "f");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'v' and str[i + 1] == 'v')
			{
				str.replace(i, 1, "v");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'm' and str[i + 1] == 'm')
			{
				str.replace(i, 1, "m");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'z' and str[i + 1] == 'z')
			{
				str.replace(i, 1, "z");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'h' and str[i + 1] == 'h')
			{
				str.replace(i, 1, "h");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 't' and str[i + 1] == 't')
			{
				str.replace(i, 1, "t");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'd' and str[i + 1] == 'd')
			{
				str.replace(i, 1, "d");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'l' and str[i + 1] == 'l')
			{
				str.replace(i, 1, "l");
				str.erase(i + 1, 1);
				i--;
			}
			else if (str[i] == 'n' and str[i + 1] == 'n')
			{
				str.replace(i, 1, "n");
				str.erase(i + 1, 1);
				i--;
			}
		}
		char temp = strc[0];
		for (ll i = 1; i < size(strc); i++)
		{
			if (temp > 65 and temp < 90 and str[i]>97 and str[i]<122)
			{
				toupper(str[i]);
				temp = 0;
				continue;
			}
			if (strc[i] == ' ')
			{
				temp = strc[i+1];
			}
		}
		cout << str << endl;
	}
	return 0;
}