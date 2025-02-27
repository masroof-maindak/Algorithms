#include "chp.hpp"

int main() {
	chp::pset s1 = {{5, 8}, {6, 6}, {10, 3}, {1, 1}};
	chp::pset s2 = {{8, 7},	 {7, 7},  {6, 9},	{0, -9},
					{1, -4}, {19, 0}, {-7, -7}, {-9, 0}};

	/* print(chp::gift_wrapping(s1)); */
	/* print(chp::gift_wrapping(s2)); */
	/* print(chp::graham_scan(s1)); */
	print(chp::graham_scan(s2));
	return 0;
}
