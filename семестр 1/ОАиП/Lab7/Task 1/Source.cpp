#include <iostream>
#include <string>
using namespace std;
#define ll long long
int main() {
	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	ll ans = 0;
	ll y = 1;
	if (s[s.size() - 1] == '1')
	{
		ans = 1;
		for (ll i = 0; i < s.size(); i++)        //O(n)
		{
			if (s[i] == '0')
			{
				ans += y;
			}
			y *= 2;
		}
		ans *= -1;
	}
	else
	{
		for (ll i = 0; i < s.size()-1; i++)        //O(n)
		{
			if (s[i] == '1')
			{
				ans += y;
			}
			y *= 2;
		}
	}

	cout << ans;
	return 0;
}