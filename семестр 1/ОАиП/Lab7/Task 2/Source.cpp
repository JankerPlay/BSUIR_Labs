#include <iostream>
#include <string>
using namespace std;
#define ll long long
int main() {
	ll a, b;
	bool znaka = 1, znakb = 1;
	cin >> a >> b;
	string sa, sb;
	if (a < 0)
		znaka = 0;
	if (b < 0)
		znakb = 0;
	a = fabs(a);
	b = fabs(b);
		while (a)
		{
			if (a % 2 == 1)
				sa.push_back('1');
			else if (a % 2 == 0)
				sa.push_back('0');
			a /= 2;
		}
		reverse(sa.begin(), sa.end());
		while (sa.size() < 32)
		{
			sa.insert(0, "0");
		}
		if (znaka == 0)
		{
			for (ll i = 0; i < 32; i++)
			{
				if (sa[i] == '1')
					sa[i] = '0';
				else if (sa[i] == '0')
					sa[i] = '1';

			}
		}
		while (b)
		{
			if (b % 2 == 1)
				sb.push_back('1');
			else if (b % 2 == 0)
				sb.push_back('0');
			b /= 2;
		}
		reverse(sb.begin(), sb.end());
		while (sb.size() < 32)
		{
			sb.insert(0, "0");
		}
		if (znakb == 0)
		{
			for (ll i = 0; i < 32; i++)
			{
				if (sb[i] == '1')
					sb[i] = '0';
				else if (sb[i] == '0')
					sb[i] = '1';
			}
		}
		reverse(sa.begin(), sa.end());
		reverse(sb.begin(), sb.end());
		string sc;
		ll x=0;
		ll y=0;
		ll z=0;
		for (ll i = 0; i < 32; i++)
		{
				if (sa[i] == '1')
					x = 1;
				if (sa[i] == '0')
					x = 0;
				if (sb[i] == '1')
					y = 1;
				if (sb[i] == '0')
					y = 0;
				if (x + y + z == 3)
				{
					sc.push_back('1');
					z = 1;
				}
				else if (x + y + z == 2)
				{
					sc.push_back('0');
					z = 1;
				}
				else if (x + y + z == 1)
				{
					sc.push_back('1');
					z = 0;
				}
				else if (x + y + z == 0)
				{
					sc.push_back('0');
					z = 0;
				}
		}
		ll ans = 0;
		y = 1;
		if (sc[sc.size() - 1] == '1')
		{
			ans = 1;
			for (ll i = 0; i < sc.size(); i++)        
			{
				if (sc[i] == '0')
				{
					ans += y;
				}
				y *= 2;
			}
			ans *= -1;
		}
		else
		{
			for (ll i = 0; i < sc.size() - 1; i++)       
			{
				if (sc[i] == '1')
				{
					ans += y;
				}
				y *= 2;
			}
		}
		if (znaka == 0 or znakb == 0)
		{
			sc.push_back('.');
			sc.push_back('1');
			cout << ans + 1;
		}
		else
			cout << ans;
		cout << endl;
		reverse(sa.begin(), sa.end());
		reverse(sb.begin(), sb.end());
		reverse(sc.begin(), sc.end());
	cout << sa;
	cout << endl << sb;
	cout << endl << sc;

	return 0;
}