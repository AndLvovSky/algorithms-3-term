#include<thread>

const int MAXST = 3;

void sort(int l, int r, int st) {
	if (st == MAXST) {
		mergeSort(l, r);
		return;
	}
	
	int mid = (l + r) / 2;
	thread t1 = new thread(sort, l, mid, st + 1);
	thread t2 = new thread(sort, mid + 1, r, st + 1);
	
	t1.join();
	t2.join();
	//merge...
}

sort(0, n - 1, 0);
