#include <iostream>

using namespace std;

class Point {
	
	private:
		float x, y;
		
	public:
		Point() {
			x = y = 0;
		}	
		
		Point(float x, float y) {
			this->x = x;
			this->y = y;
		}
		
		float getX() {
			return x; 
		}
		
		float getY() {
			return y;
		}
		
		void setX(float x) {
			this->x = x;
		}
		
		void setY(float y) {
			this->y = y;
		}	
		
		void print() {
			cout << "(" << x << ", " << y << ")";
		}
		
		Point operator = (Point p) {
			this->setX(p.getX());
			this->setY(p.getY());
			return *this;
		}
};

class Line {
	
	private:
		Point a, b;
		
	public:
		Line() {
		}
		
		Line(Point a, Point b) {
			this->a = a;
			this->b = b;
		}
		
		Point getFirstPoint() {
			return a;
		}
		
		Point getSecondPoint() {
			return b;
		}
		
		void setFirstPoint(Point p) {
			a = p;
		}
		
		void setSecondPoint(Point p) {
			b = p;
		}
		
		void print() {
			a.print();
			cout << " - ";
			b.print();
		}
		
		static bool isLine(Point a, Point b) {
			return a.getX() != b.getX() || a.getY() != b.getY();
		}
		
		static bool parallel(Line la, Line lb) {
			return (la.getSecondPoint().getX() - la.getFirstPoint().getX()) * 
				   (lb.getSecondPoint().getY() - lb.getFirstPoint().getY()) ==
				   (la.getSecondPoint().getY() - la.getFirstPoint().getY()) * 
				   (lb.getSecondPoint().getX() - lb.getFirstPoint().getX());
		}
		
};

class Parallelogram {
	private:
		Point p[4];
		
	public:
		Parallelogram() {
		}
		
		Parallelogram(Point p[4]) {
			for (int i = 0; i < 4; i++) {
				this->p[i] = p[i];
			}
		}
		
		void setPoint(int i, Point p) {
			this->p[i] = p;
		}
		
		Point getPoint(int i) {
			return p[i];
		}
		
		void print() {
			for (int i = 0; i < 3; i++) {
				p[i].print();
				cout << " - ";
			}
			p[3].print();
		}
		
		static bool isParallelogram(Point p[4]) {
			if (!(Line::isLine(p[0], p[1]) && Line::isLine(p[2], p[3]) &&
			      Line::isLine(p[1], p[2]) && Line::isLine(p[0], p[3]))) {
				return false;
			}
			Line la(p[0], p[1]), lb(p[2], p[3]), lc(p[1], p[2]), ld(p[0], p[3]);
			return Line::parallel(la, lb) && Line::parallel(lc, ld);
		}
};

int main() {
	Point p[4];
	p[0].setX(0);
	p[0].setY(0);
	p[1].setX(2);
	p[1].setY(3);
	p[2].setX(6);
	p[2].setY(3);
	p[3].setX(4);
	p[4].setY(0);
	cout << "Points ";
	for (int i = 0; i < 4; i++) {
		p[i].print();
		cout << " ";
	}
	if (Parallelogram::isParallelogram(p)) {
		cout << "form parallelogram" << endl;
	} else {
		cout << "don't form parallelogram" << endl;
	}
}
