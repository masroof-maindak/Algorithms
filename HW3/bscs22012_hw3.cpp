#include <iostream>
#include <vector>

void printVec(std::vector<int> a) {
    for (int x : a)
        std::cout << x;
    std::cout << std::endl;
}

std::vector<int> addTwoBin(std::vector<int> a, std::vector<int> b) {
    int n = std::max(a.size(), b.size());
    std::vector<int> ret(n);
    int carry = 0;

    for (int i = 0; i < n; i++) {
        int sum = carry;
        if (i < a.size())
            sum += a[a.size() - i - 1];
        if (i < b.size())
            sum += b[b.size() - i - 1];

        ret[n - i - 1] = sum % 2;
        carry = sum / 2;
    }

    if (carry > 0)
        ret.insert(ret.begin(), carry);

    return ret;
}

std::vector<int> subTwoBin(std::vector<int> a, std::vector<int> b) {
    int n = std::max(a.size(), b.size());
    std::vector<int> ret(n);
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

    // remove leading zeros
    while (ret.size() > 1 && ret.front() == 0)
        ret.erase(ret.begin());

    return ret;
}

std::vector<int> shiftNtimes(std::vector<int> a, int n) {
    for (int i = 0; i < n; i++)
        a.push_back(0);
    return a;
}

int makeSizeEqual(std::vector<int>& x, std::vector<int>& y) {
    if (x.size() == y.size())
        return x.size();

    int ret = std::max(x.size(), y.size());

    while (x.size() < ret)
        x.insert(x.begin(), 0);
    while (y.size() < ret)
        y.insert(y.begin(), 0);
        
    return ret;
}

std::vector<int> multRec3 (std::vector<int> x, std::vector<int> y) {
    int n = makeSizeEqual(x, y); //essential as x.size is not necessarily
    //                             equal to y.size. This is because of the
    //                             recursive call made in P3, where we have
    //                             to (possibly) multiply an n bit number
    //                             with an n+1 bit number.

    // base case
    if (n == 1)
        return {x[0] * y[0]};

    int half = n/2, ceilHalf = n - half;

    std::vector<int> xl(x.begin(), x.begin() + ceilHalf);
    std::vector<int> xr(x.begin() + ceilHalf, x.end());
    std::vector<int> yl(y.begin(), y.begin() + ceilHalf);
    std::vector<int> yr(y.begin() + ceilHalf, y.end());

    std::vector<int> P1 = multRec3(xl, yl);
    std::vector<int> P2 = multRec3(xr, yr);
    std::vector<int> P3 = multRec3(addTwoBin(xl, xr), addTwoBin(yl, yr));

    //p1 = xl * yl
    //p2 = xr * yr
    //p3 = (xl + xr) * (yl + yr)

    // return (p1 x 2^n) + ((P3 - P1 - P2) x 2^(n/2)) + P2
    // return first + second + P2;
    // second = middleTerm * 2^(n/2)
    // middleTerm = P3 - P1 - P2 
    // middleTerm = P3 - (P1 + P2)

    // first = P1 x 2^n
    std::vector<int> first = shiftNtimes(P1, half * 2);
    std::vector<int> middleTerm = subTwoBin(P3, addTwoBin(P1, P2));
    std::vector<int> second = shiftNtimes(middleTerm, half);

    //therefore, return first + second + P2;
    return addTwoBin(first, addTwoBin(second, P2));
}

std::vector<int> multRec4 (std::vector<int> x, std::vector<int> y) {
    int n = x.size(); //x.size *will* equal y.size in the 4multEquation,
    //                  because for the very first call, x.size = y.size
    //                  and every recursive multiplication call afterwards 
    //                  will be made PRIOR to addition
    int half = n / 2;

    if (n == 1)
        return {x[0] * y[0]};

    std::vector<int> xl(x.begin(), x.begin() + half);
    std::vector<int> xr(x.begin() + half, x.end());
    std::vector<int> yl(y.begin(), y.begin() + half);
    std::vector<int> yr(y.begin() + half, y.end());

    // return 2^n.Xl.Yl + 2^(n/2).(xl.yr + xr.yl) + xr.yr
    // return first + second + third;
    std::vector<int> frst = shiftNtimes(multRec4(xl, yl), n);
    std::vector<int> scnd = shiftNtimes(addTwoBin(multRec4(xl,yr), multRec4(xr,yl)), half);
    std::vector<int> thrd = multRec4(xr, yr);

    return addTwoBin(frst, addTwoBin(scnd, thrd));
}

int main() {
    printVec(multRec3({1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0}));
    printVec(multRec4({1,1,1,1,1,1,1,1},{1,1,1,1,0,0,0,0}));
    return 0;
}
