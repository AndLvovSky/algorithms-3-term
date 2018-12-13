#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node {
	int w;
	char c;
	Node* l, *r;
	
	Node(int w, char c, Node* l, Node* r) {
		this->w = w;
		this->c = c;
		this->l = l;
		this->r = r;
	}
};

class Comparator {
	public:
	bool operator () (Node* a, Node* b) {
		return a->w > b->w;
	}		
};

string s;
priority_queue <Node*, vector <Node*>, Comparator> ht;
map <char, string> hc;
map <char, int> fr;

void traversal(Node* cur, string code) {
	if (cur == NULL) {
		return;
	}
	if (cur->c != 0) {
		hc[cur->c] = code;
		return;
	}
	traversal(cur->l, code + "0");
	traversal(cur->r, code + "1");
}

int main() {
	getline(cin, s);
	for (auto ch : s) {
		fr[ch]++;
	}
	for (auto it : fr) {
		ht.push(new Node(it.second, it.first, NULL, NULL));
	}
	if (ht.size() == 1) {
		Node* top = ht.top();
		ht.pop();
		ht.push(new Node(top->w, 0, top, NULL));
	}
	while (ht.size() != 1) {
		Node *f, *s;
		f = ht.top();
		ht.pop();
		s = ht.top();
		ht.pop();
		ht.push(new Node(f->w + s->w, 0, f, s)); 
	}
	traversal(ht.top(), "");
	for (auto ch : s) {
		cout << hc[ch] << " ";
	}
	cout << endl;
}
