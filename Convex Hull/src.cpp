#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <vector>

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

using Pset = std::vector<Point>;

void print(const Pset h) {
	for (auto &v : h)
		std::cout << v.x << " " << v.y << "\n";
	std::cout << std::endl;
}

bool leftHandTurn(const Point &P, const Point &Q, const Point &R) {

	/*
	 * | Px Py 1 |
	 * | Qx Qy 1 |
	 * | Rx Ry 1 |
	 *
	 * Sign of determinant == sign of area (shoelace theorem)
	 *
	 * The aforementioned can be used to determine whether the three points
	 * (p->q->r) are making a left hand turn, right hand turn, or are collinear.
	 */

	return (Q.x - P.x) * (R.y - P.y) - (Q.y - P.y) * (R.x - P.x) > 0;
}

Pset giftWrapping(Pset &P) {
	if (P.size() < 3)
		return {};

	Pset CH = {};

	/* Find right-most point */
	Pset::iterator max = std::max_element(
		P.begin(), P.end(),
		[](const Point &a, const Point &b) { return a.x < b.x; });

	/* Jarvis' March */
	Point end = *max;
	do {
		CH.push_back(end);
		end = P[0] == CH.back() ? P[1] : P[0];
		for (size_t i = 1; i < P.size(); i++)
			if (leftHandTurn(CH.back(), end, P[i]))
				end = P[i];
	} while (end != CH[0]);

	return CH;
}

int main() {
	Pset s1 = {Point(5, 8), Point(6, 6), Point(10, 3), Point(1, 1)};
	Pset s2 = {Point(8, 7),	 Point(7, 7), Point(7, 9),	Point(0, -9),
			   Point(1, -4), Point(9, 0), Point(-7, -7)};

	print(giftWrapping(s1));
	print(giftWrapping(s2));
	return 0;
}
