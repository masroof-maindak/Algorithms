// longest increasing subsequence's size
#include <iostream>
#include <vector>
using namespace std;

int findLISSS (vector<int> a) {
    int n = a.size(), ret = 1;
    vector<int> lisss (n, 1);

    // no reason to do it in reverse, this just popped into my head first
    for (int i = n - 1; i >= 0; i--) { // start from n-1 because lisss[n] is trivially 1
        for (int j = n; j > i; j--) // start from the end and check every element until i
            if (a[i] < a[j]) // iff a[i] < a[j] (i.e increasing subsequence)
                lisss[i] = max(lisss[i], 1 + lisss[j]);
        ret = max(ret, lisss[i]);   // update global max
    }
    
    return ret;
}

int main() {
    cout << findLISSS({10, 22, 9, 33, 21, 50, 41, 60, 80}) << "\n";
    return 0;
}
