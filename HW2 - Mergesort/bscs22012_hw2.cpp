#include <iostream>
#include <vector>
#include <queue>
#include <list>

std::list<int> mergeLL(std::list<int>& a, std::list<int>& b) {

    std::list<int> ret;
    
    while (!a.empty() and !b.empty()) {
        if (a.front() < b.front()) {
            ret.push_back(a.front());
            a.pop_front();
        } else {
            ret.push_back(b.front());
            b.pop_front();
        }
    }

    while (!a.empty()) {
        ret.push_back(a.front());
        a.pop_front();
    }

    while (!b.empty()) {
        ret.push_back(b.front());
        b.pop_front();
    }

    return ret;
}

void mergeSortLL(std::list<int>& l) {
    if (l.size() <= 1)
        return;

    std::list<int> left, right;
    int middle = l.size() / 2;
    for (auto it = l.begin(); it != l.end(); it++) {
        if (std::distance(l.begin(), it) < middle) {
            left.push_back(*it);
        } else {
            right.push_back(*it);
        }
    }

    mergeSortLL(left);
    mergeSortLL(right);
    l = mergeLL(left, right);
}

std::vector<int> merge(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> ret;
    int i = 0, j = 0;

    while (i < a.size() and j < b.size()) {
        if (a[i] < b[j])
            ret.push_back(a[i++]);
        else
            ret.push_back(b[j++]);
    }

    while (i < a.size())
        ret.push_back(a[i++]);

    while (j < b.size())
        ret.push_back(b[j++]);

    return ret;
}

void iterativeMergeSortWithQueue(std::vector<int>& v) {
    // Essentially a bottom up approach, I think.
    std::queue<std::vector<int>> q;
    
    for (auto x : v)
        q.push({x});

    while (q.size() > 1) {
        std::vector<int> a = q.front();
        q.pop();
        std::vector<int> b = q.front();
        q.pop();
        q.push(merge(a, b));
    }
    
    v = q.front();
}

void q1(), q2();

int main() {
    q1();
    q2();
    return 0;
}

void q1() {
    std::cout << "Merge Sort with List:\n";
    std::list<int> l = {5, 3, 2, 1, 4, 10, 8, 6, 7, 9};
    mergeSortLL(l);
    for (auto it = l.begin(); it != l.end(); it++)
        std::cout << *it << " ";
}

void q2() {
    std::cout << "\n\nIterative Merge Sort with Queue:\n";
    std::vector<int> v = {5, 3, 2, 1, 4, 10, 8, 6, 7, 9};
    iterativeMergeSortWithQueue(v);
    for (auto x : v)
        std::cout << x << " ";
}
