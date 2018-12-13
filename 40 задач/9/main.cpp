#include "graph.h"


int main() {
	graph myGraph("graph.txt");
	myGraph.printMatrix();
	myGraph.permute();
	
	system("Pause");
	return 0;
};