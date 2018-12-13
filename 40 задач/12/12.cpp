#include <iostream>
#include <utility>

using namespace std;

struct Node {
	int num;
	int row, column;
	Node *r, *b;
	
	Node(int number, int row, int column, Node* right, Node* bottom) {
		this->num = number;
		this->row = row;
		this->column = column;
		this->r = right;
		this->b = bottom;
	}
};

const int INFINITY = 1e9, N = 4;
Node *rows[N], *columns[N];

void generateSparseMatrixInMultiList() {
	rows[3] = new Node(1, 3, 0, new Node(2, 3, 2, new Node(3, 3, 3, NULL, NULL), NULL), NULL);
	rows[2] = new Node(1, 2, 0, new Node(4, 2, 1, new Node(3, 2, 3, NULL, rows[3]->r->r->r), NULL), rows[3]);
	rows[1] = new Node(2, 1, 1, NULL, rows[2]->r);
	rows[0] = new Node(1, 0, 0, new Node(2, 0, 3, NULL, NULL), NULL);
	columns[3] = rows[0]->r;
	columns[2] = rows[3]->r;
	columns[1] = rows[1];
	columns[0] = rows[0];
}

pair <int, int> findMaxPos() {
	int maxEl = -INFINITY;
	pair <int, int> maxElPos;
	for (int i = 0; i < N; i++) {
		for (Node* it = rows[i]; it != NULL; it = it->r) {
			if (it->num > maxEl) {
				maxEl = it->num;
				maxElPos = make_pair(it->row, it->column);
			}	
		}
	}
	return maxElPos;
}

void erase(pair <int, int> pos) {
	if (pos.first != 0) {
		for (Node* it = rows[pos.first - 1]; it != NULL; it = it->r) {
			if (!(it->b != NULL && it->b->b == NULL)) {
				it->b = it->b->b;				
			}
		}
	}
	if (pos.second != 0) {
		for (Node* it = columns[pos.second - 1]; it != NULL; it = it->b) {
			if (!(it->r != NULL && it->r->r == NULL)) {
				it->r = it->r->r;				
			}
		}
	}
	rows[pos.first] = NULL;
	columns[pos.second] = NULL;
}

void print() {
	for (int i = 0; i < N; i++) {
		if (rows[i] == NULL) {
			cout << "NULL" << endl;
			continue;
		}
		for (Node* it = rows[i]; it != NULL; it = it->r) {
			cout << it->num << ", (" << it->row << ", " << it->column << ") "; 
		}
		cout << endl;
	}
}

int main() {
	generateSparseMatrixInMultiList();
	cout << "Start matrix: " << endl;
	print();
	pair <int, int> maxPos = findMaxPos();
	cout << "Max element at position: (" << maxPos.first << ", " << maxPos.second << ")" << endl; 
	erase(maxPos);
	cout << "Result matrix: " << endl;
	print();
}
