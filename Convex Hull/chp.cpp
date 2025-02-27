#include <algorithm>

#include "chp.hpp"

using namespace chp;

void chp::print(const pset &h) {
	for (auto v : h)
		std::cout << v.x << " " << v.y << "\n";
	std::cout << std::endl;
}

bool chp::left_hand_turn(const Point &P, const Point &Q, const Point &R) {

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

pset chp::graham_scan(const pset &P) {
	if (P.size() < 3)
		return {};

	pset upper_h = {}, lower_h = {}, s_p = P, s_lower_p = {}, s_upper_p = {};

	std::sort(s_p.begin(), s_p.end(),
			  [](const Point &a, const Point &b) { return a.x < b.x; });

	for (auto x : s_p)
		x.y < 0 ? s_lower_p.emplace_back(x) : s_upper_p.emplace_back(x); 

	// NOTE: the first two points must not be collinear w/ other points on the
	// y-axis
	upper_h.emplace_back(s_upper_p[0]);
	upper_h.emplace_back(s_upper_p[1]);

	lower_h.emplace_back(s_lower_p[0]);
	lower_h.emplace_back(s_lower_p[1]);

	/* Upper hull */
	for (size_t i = 2; i < s_upper_p.size(); i++) {
		while (left_hand_turn(upper_h[upper_h.size() - 2],
							  upper_h[upper_h.size() - 1], s_upper_p[i]))
			upper_h.pop_back();
		upper_h.emplace_back(s_upper_p[i]);
	}

	/* Lower hull */
	for (size_t i = 2; i < s_lower_p.size(); i++) {
		while (!left_hand_turn(lower_h[lower_h.size() - 2],
							   lower_h[lower_h.size() - 1], s_lower_p[i]))
			lower_h.pop_back();
		lower_h.emplace_back(s_lower_p[i]);
	}

	pset ret;
	ret.reserve(upper_h.size() + lower_h.size());
	ret.insert(ret.end(), upper_h.begin(), upper_h.end());
	ret.insert(ret.end(), lower_h.begin(), lower_h.end());
	return ret;
}

pset chp::gift_wrapping(pset &P) {
	if (P.size() < 3)
		return {};

	pset CH = {};
	CH.reserve(P.size() / 4);

	/* Find right-most point */
	pset::iterator max = std::max_element(
		P.begin(), P.end(),
		[](const Point &a, const Point &b) { return a.x < b.x; });

	/* Jarvis' March */
	Point end = *max;
	do {
		CH.emplace_back(end);
		end = P[0] == CH.back() ? P[1] : P[0];
		for (size_t i = 1; i < P.size(); i++)
			if (left_hand_turn(CH.back(), end, P[i]))
				end = P[i];
	} while (end != CH[0]);

	return CH;
}
