#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <graphics.h>

using namespace std;

const int MAXX = 500, MAXY = 500;

struct Segment {
	int xa, ya, xb, yb, color;
};

int n;
vector <Segment> segments;

void rasterize(int xa, int ya, int xb, int yb, int color) {
	int dx = abs(xb - xa), dy = abs(yb - ya);
	int dev = 0;
	if (dx >= dy) {
		if (xa > xb) {
			swap(xa, xb);
			swap(ya, yb);
		}
		for (int x = xa, y = ya; x <= xb; x++) {
			putpixel(x, y, color);
			dev += dy;
			if (2 * dev >= dx) {
				y += (yb < ya ? -1 : 1);
				dev -= dx;
			}
		}
	} else {
		if (ya > yb) {
			swap(xa, xb);
			swap(ya, yb);
		}
		for (int y = ya, x = xa; y <= yb; y++) {
			putpixel(x, y, color);
			dev += dx;
			if (2 * dev >= dy) {
				x += (xb < xa ? -1 : 1);
				dev -= dy;
			}
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		Segment s;
		cin >> s.xa >> s.xb >> s.ya >> s.yb >> s.color;
		segments.push_back(s);
	}
	initwindow(MAXX, MAXY);
	setfillstyle(1, WHITE);
	bar(0 , 0, MAXX, MAXY);
	for (int i = 0; i < segments.size(); i++) {
		rasterize(segments[i].xa, segments[i].xb,
			segments[i].ya, segments[i].yb, segments[i].color);
	}
	getch();
}
