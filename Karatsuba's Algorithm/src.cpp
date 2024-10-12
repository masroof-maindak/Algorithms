#include <iostream>
#include <stdint.h>
#include <vector>

void printVec(std::vector<uint8_t> a) {
	for (int x : a)
		std::cout << x;
	std::cout << std::endl;
}

std::vector<uint8_t> add(std::vector<uint8_t> a, std::vector<uint8_t> b) {
	int n = std::max(a.size(), b.size());
	std::vector<uint8_t> ret(n);
	int carry = 0;

	for (int i = 0; i < n; i++) {
		int sum = carry;
		if (i < a.size())
			sum += a[a.size() - i - 1];
		if (i < b.size())
			sum += b[b.size() - i - 1];

		ret[n - i - 1] = sum % 2;
		carry		   = sum / 2;
	}

	if (carry > 0)
		ret.insert(ret.begin(), carry);

	return ret;
}

std::vector<uint8_t> sub(std::vector<uint8_t> a, std::vector<uint8_t> b) {
	int n = std::max(a.size(), b.size());
	std::vector<uint8_t> ret(n);
	int borrow = 0;

	for (int i = 0; i < n; i++) {
		int diff = borrow;

		if (i < a.size())
			diff += a[a.size() - i - 1];
		if (i < b.size())
			diff -= b[b.size() - i - 1];

		if (diff < 0) {
			diff += 2;
			borrow = -1;
		} else {
			borrow = 0;
		}

		ret[n - i - 1] = diff;
	}

	/* Remove leading zeros */
	while (ret.size() > 1 && ret.front() == 0)
		ret.erase(ret.begin());

	return ret;
}

/* Shifts a binary number left n times */
std::vector<uint8_t> shift(std::vector<uint8_t> a, int n) {
	for (int i = 0; i < n; i++)
		a.push_back(0);
	return a;
}

/* Returns the size of the larger number */
uint8_t makeSizeEqual(std::vector<uint8_t> &x, std::vector<uint8_t> &y) {
	if (x.size() == y.size())
		return x.size();

	uint8_t ret = std::max(x.size(), y.size());

	while (x.size() < ret)
		x.insert(x.begin(), 0);
	while (y.size() < ret)
		y.insert(y.begin(), 0);

	return ret;
}

std::vector<uint8_t> rec3(std::vector<uint8_t> x, std::vector<uint8_t> y) {

	uint8_t n = makeSizeEqual(x, y);
	/* essential as x.size is not necessarily equal to y.size. This is because
	 * of the recursive call made in P3, where we have to (possibly) multiply an
	 * n bit number with an n+1 bit number. */

	/* Base case */
	if (n == 1)
		return {static_cast<uint8_t>(x[0] * y[0])};

	int half  = n / 2;
	int uhalf = n - half;

	std::vector<uint8_t> xl(x.begin(), x.begin() + uhalf);
	std::vector<uint8_t> xr(x.begin() + uhalf, x.end());
	std::vector<uint8_t> yl(y.begin(), y.begin() + uhalf);
	std::vector<uint8_t> yr(y.begin() + uhalf, y.end());

	std::vector<uint8_t> P1 = rec3(xl, yl);
	std::vector<uint8_t> P2 = rec3(xr, yr);
	std::vector<uint8_t> P3 = rec3(add(xl, xr), add(yl, yr));

	/*
	 * p1 = xl * yl
	 * p2 = xr * yr
	 * p3 = (xl + xr) * (yl + yr)

	 * return (p1 * 2^n) + ((P3 - P1 - P2) * 2^(n/2)) + P2
	 * return first      + second                     + P2;

	 * second = middle * 2^(n/2)
	 * middleTerm = P3 - P1 - P2
	 * middleTerm = P3 - (P1 + P2)

	 * first = P1 x 2^n
	 */

	std::vector<uint8_t> first	= shift(P1, half * 2);
	std::vector<uint8_t> middle = sub(P3, add(P1, P2));
	std::vector<uint8_t> second = shift(middle, half);

	return add(first, add(second, P2));
}

std::vector<uint8_t> rec4(std::vector<uint8_t> x, std::vector<uint8_t> y) {
	int n = x.size();
	/* x.size *will* equal y.size in the 4multEquation, because for the very
	 * first call, x.size = y.size and every recursive multiplication call
	 * afterwards will be made PRIOR to addition */

	int half = n / 2;

	if (n == 1)
		return {static_cast<uint8_t>(x[0] * y[0])};

	std::vector<uint8_t> xl(x.begin(), x.begin() + half);
	std::vector<uint8_t> xr(x.begin() + half, x.end());
	std::vector<uint8_t> yl(y.begin(), y.begin() + half);
	std::vector<uint8_t> yr(y.begin() + half, y.end());

	/*
	 * return 2^n * Xl * Yl + 2^(n/2) * (xl * yr + xr * yl) + xr * yr
	 * return first         + second                        + third
	 */

	std::vector<uint8_t> first	= shift(rec4(xl, yl), n);
	std::vector<uint8_t> second = shift(add(rec4(xl, yr), rec4(xr, yl)), half);
	std::vector<uint8_t> third	= rec4(xr, yr);

	return add(first, add(second, third));
}

int main() {
	printVec(rec3({1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 0, 0, 0}));
	printVec(rec4({1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 0, 0, 0, 0}));
	return 0;
}
