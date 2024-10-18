#include "chp.hpp"

int main() {
	/* CHECK: constructor overhead? */
	chp::pset s1 = {{5, 8}, {6, 6}, {10, 3}, {1, 1}};
	chp::pset s2 = {{8, 7}, {7, 7}, {7, 9}, {0, -9}, {1, -4}, {9, 0}, {-7, -7}};

	/* print(chp::giftWrapping(s1)); */
	/* print(chp::giftWrapping(s2)); */
	chp::grahamScan(s1);
	/* print(chp::grahamScan(s1)); */
	/* print(chp::grahamScan(s2)); */
	return 0;
}
