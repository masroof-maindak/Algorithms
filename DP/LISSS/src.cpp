// longest increasing subsequence's size
#include <iostream>
#include <vector>

using namespace std;

int LISSS (vector<int> a) {
    int n = a.size();
    vector<int> lisss (n, 0);
    lisss[n] = 1;   // last index' size is going to be 1 unconditionally
    int ret = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n; j > i ; j--)
            if (a[i] < a[j])
                lisss[i] = max(lisss[i], lisss[i] + lisss[j]);
        ret = max(ret, lisss[i]);
    }
    
    return ret;
}

int main() {
    cout << findLISSS({10, 22, 9, 33, 21, 50, 41, 60, 80}) << "\n";
    return 0;
}
