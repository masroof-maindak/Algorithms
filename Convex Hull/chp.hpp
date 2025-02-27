#ifndef CHP_H
#define CHP_H

#include <iostream>
#include <vector>

namespace chp {
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
using pset = std::vector<Point>;

void print(const pset &h);
bool left_hand_turn(const Point &P, const Point &Q, const Point &R);

pset graham_scan(const pset &P);
pset gift_wrapping(pset &P);
} // namespace chp

#endif // CHP_H
