#include <iostream>

using namespace std;

template <typename T>
struct Node {
	T* val;
	Node *next;
	
	Node(T* val, Node* next) {
		this->val = val;
		this->next = next;
	}
};

template <typename T>
class List {
	private:
		
	int count;
	Node <T> *head;
	
	public:
		
	List() {
		count = 0;
		head = NULL;
	}
	
	~List() {
		while (count) {
			erase(0);
		}
	}
	
	Node <T>* elementAt(int pos) {
		Node <T>* it = head;
		for (int i = 0; i < pos; i++) {
			it = it->next;
		}
		return it;
	}
	
	bool insert(int pos, T* val) {
		if (pos > count) {
			return false;
		}
		if (count == 0 && pos == 0) {
			head = new Node <T>(val, NULL);
		} else if (pos == 0) {
			Node <T>* node = new Node <T>(val, head);
			head = node;
		} else {
			Node <T>* prevNode = elementAt(pos - 1);
			Node <T>* node = new Node <T>(val, prevNode->next);
			prevNode->next = node;
		} 
		count++;
		return true;
	}
	
	bool erase(int pos) {
		if (pos >= count) {
			return false;
		}
		if (pos == 0) {
			Node <T>* oldHead = head;
			head = head->next;
			delete oldHead;
		} else {
			Node <T>* prevNode = elementAt(pos - 1);
			Node <T>* oldNode = prevNode->next;
			prevNode->next = prevNode->next->next;
			delete oldNode;
		}
		count--;
		return true;
	}
	
	int size() {
		return count;
	}
	
	Node <T>* begin() {
		return head;
	}
	
	void print() {
		cout << "size = " << count << endl;
		for (Node <T>* it = head; it != NULL; it = it->next) {
			cout << *(it->val) << " ";
		} 
		cout << endl;
	}
};

template <typename T>
void separate(List <T>& a, List <T>& gr, List <T>& ls, int n) {
	for (Node <T>* it = a.begin(); it != NULL; it = it->next) {
		if (*(it->val) > n) {
			gr.insert(gr.size(), it->val);
		} else {
			ls.insert(ls.size(), it->val);
		}
	}
}

int x[7] = {1, 2, 3, 4, 5, 6, 7};

int main() {
	List <int> list;
	list.insert(0, x);
	list.insert(1, x + 1);
	list.insert(1, x + 2);
	list.insert(2, x + 3);
	list.insert(4, x + 4);
	list.insert(5, x + 5);
	list.insert(5, x + 6);
//	list.print();
//	list.erase(0);
//	list.print();
//	list.erase(5);
//	list.print();
//	list.erase(1);
//	list.print();
	int n;
	cin >> n;
	List <int> gr, ls;
	separate(list, gr, ls, n);
	cout << "Start list: " << endl;
	list.print();
	cout << "List of greater elements then " << n << ": " << endl;
	gr.print();
	cout << "List of less equal elements then " << n << ": " << endl;
	ls.print();
}
