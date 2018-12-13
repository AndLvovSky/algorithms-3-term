#include <iostream>

using namespace std;

string maxPol(string s) {
	if (s.size() <= 1) {
		return s;
	}
	if (s[0] == s[s.size() - 1]) {
		string res = "";
		res += s[0];
		res += maxPol(s.substr(1, s.size() - 2));
		res += s[s.size() - 1];
		return res;
	}
	string res1, res2, res3;
	res1 = maxPol(s.substr(0, s.size() - 1));
	res2 = maxPol(s.substr(1, s.size() - 1));
	res3 = maxPol(s.substr(1, s.size() - 2));
	if (res1.size() >= res2.size() && res1.size() >= res3.size()) {
		return res1;
	} else if (res2.size() >= res1.size() && res2.size() > res3.size()) {
		return res2;
	}
	return res3;
}

int main() {
	string s;
	cin >> s;
	cout << maxPol(s) << endl;
}
