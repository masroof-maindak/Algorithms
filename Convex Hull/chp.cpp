#include <algorithm>

#include "chp.hpp"

using namespace chp;

void chp::print(const pset &h) {
	for (auto &v : h)
		std::cout << v.x << " " << v.y << "\n";
	std::cout << std::endl;
}

bool chp::leftHandTurn(const Point &P, const Point &Q, const Point &R) {

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

pset chp::grahamScan(const pset &P) {
	if (P.size() < 3)
		return {};

	pset uCH = {}, lCH = {}, sortP = P;

	std::sort(sortP.begin(), sortP.end(),
			  [](const Point &a, const Point &b) { return a.x < b.x; });

	uCH.push_back(sortP[0]);
	uCH.push_back(sortP[1]);

	/* TODO */
	/* Upper hull */
	for (size_t i = 2; i < P.size(); i++) {
		while (leftHandTurn(uCH[uCH.size() - 2], uCH[uCH.size() - 1], P[i]))
			uCH.pop_back();
		uCH.push_back(P[i]);
	}

	print(uCH);

	return uCH;
}

pset chp::giftWrapping(pset &P) {
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
			if (leftHandTurn(CH.back(), end, P[i]))
				end = P[i];
	} while (end != CH[0]);

	return CH;
}
