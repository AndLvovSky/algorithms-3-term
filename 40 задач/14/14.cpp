#include<iostream>

using namespace std;

template <typename T>
void heapify(T *a, int i, int n){
    int bigger, left, right;
    bigger = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < n && a[bigger] < a[left]) {
    	bigger = left;
    }
    if (right < n && a[bigger] < a[right]) {
        bigger = right;
    }
    if (i != bigmger) {
      	swap(a[i], a[bigger]);
      	heapify(a, bigger, n);
     }
}

template <typename T>
void buildHeap(T *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
    	heapify(a, i, n);
    }
}

template <typename T>
void heapSort(T *a, int n){
    buildHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
	    swap(a[0], a[i]);
	    heapify(a, 0, i);
    }
}

int main() {
	int i, *a, n;
	cin >> n;
	a = new int[n];
	for (i = 0; i < n; i++) {
		cin >> a[i];
	}

	heapSort(a, n);
	
	for (i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}
