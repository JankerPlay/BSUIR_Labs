#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <sstream>
#include <iterator>
#include <functional>
using namespace std;
#define ll long long
int Task2() {
	cout << "¬ведите строку ";
	string q;
	cin >> q;
	string x;	
	getline(cin, x);
	x = q + x;
	set<string> find_words;
	stringstream ss(x);
	copy_if(istream_iterator<string>(ss),
		istream_iterator<string>(),
		inserter(find_words, find_words.end()),
		bind([](const string& str)->bool {return *str.begin() == *prev(str.end()); }, placeholders::_1));
	copy(find_words.cbegin(), find_words.cend(), ostream_iterator<string>(cout, "\xA"));
	return 0;
}