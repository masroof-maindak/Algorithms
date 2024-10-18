#ifndef CHP_H
#define CHP_H

#include <iostream>
#include <vector>

namespace chp {

struct Point;
using pset = std::vector<Point>;

struct Point {
	double x, y;

	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}
	friend bool operator==(const Point &a, const Point &b) {
		return a.x == b.x and a.y == b.y;
	}
	friend bool operator!=(const Point &a, const Point &b) { return !(a == b); }
	friend std::ostream &operator<<(std::ostream &out, const Point &a) {
		out << a.x << ", " << a.y;
		return out;
	}
};

void print(const pset &h);
bool leftHandTurn(const Point &P, const Point &Q, const Point &R);

pset grahamScan(const pset &P);
pset giftWrapping(pset &P);

} // namespace chp

#endif // CHP_H
