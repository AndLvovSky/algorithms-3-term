#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
	string a, b;
	cin >> a >> b;
	map <char, int> la, lb;
	for (auto ch : a) {
		la[ch]++;
	}
	for (auto ch : b) {
		lb[ch]++;
	}
	string x = "";
	for (auto el : la) {
		int minC = min(el.second, lb[el.first]);
		for (int i = 0; i < minC; i++) {
			x += el.first;
		}
	}
	cout << x << endl;
}
