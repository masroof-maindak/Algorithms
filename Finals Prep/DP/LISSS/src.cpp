// longest increasing subsequence's size
#include <iostream>
#include <vector>

using namespace std;

int findLISSS (vector<int> a) {
    int n = a.size(), ret = 1;
    vector<int> lisss (n, 1);

    // no reason to do it in reverse, this just popped into my head first
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n; j > i; j--)
            if (a[i] < a[j])
                lisss[i] = max(lisss[i], 1 + lisss[j]);
        ret = max(ret, lisss[i]);
    }
    
    return ret;
}

int main() {
    cout << findLISSS({10, 22, 9, 33, 21, 50, 41, 60, 80}) << "\n";
    return 0;
}
