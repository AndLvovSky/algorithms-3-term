#include <iostream>
#include "avl_tree_demo.h"

using namespace std;

string s[12] = {"abc", "xyz", "sad", "lol", "zyx", "zxx", "rre", "fds", "rew", "saw", "rtr", "lol"};
int n[12] = {56, -67, 49, 56, 77, 24, 0, 1, 2, 3, 4, 5};

int main() {
	AVLTree <string, int> t;
	for (int i = 0; i < 12; i++) {
		t.insert(s[i], n[i]);
	}
	t.print();
	t.draw();
}
