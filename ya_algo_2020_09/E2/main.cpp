// https://contest.yandex.ru/contest/19811/problems/E/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

struct Node {
    std::vector<int> child;
};

struct Stats {
    int manual;
    int cascade;
    int on;
};

void printStats(const Stats& s, int index) {
    std::cerr << "index " << index << " manual " << s.manual << " cascade " << s.cascade << " on " << s.on << std::endl;
}

Stats solve_rec(int p, const std::vector<Node>& parents, int k) {
    const Node& node = parents[p];
    std::vector<Stats> sts;
    sts.reserve(node.child.size());
    for (int ch : node.child) {
        sts.push_back(solve_rec(ch, parents, k));
    }
    int manual = 1;
    int n = sts.size();
    for (auto& s : sts) {
        manual += s.manual;
    }

    if (k > n) {
        auto res = Stats{.manual = manual, .cascade = manual, .on = manual - 1};
        // printStats(res, p);
        return res;
    }

    std::nth_element(sts.begin(), sts.end() - k + 1, sts.end(), [](const auto& l, const auto& r) {
        return (l.manual - l.on) < (r.manual - r.on);
    });

    std::nth_element(sts.begin(), sts.end() - k, sts.end() - k + 1, [](const auto& l, const auto& r) {
        return (l.manual - l.on) < (r.manual - r.on);
        });

    int on = 0;
    for (int i = 0; i < n; ++i) {
        if (i < n - k + 1) {
            on += sts[i].on;
        } else {
            on += sts[i].manual;
        }
    }

    int cascade = 0;
    for (int i = 0; i < n; ++i) {
        auto& s = sts[i];        
        int candidatescore = 1 + on + s.cascade;
        if (i < n - k + 1) {
            candidatescore -= s.on;
        }
        else {
            candidatescore -= s.manual;
            candidatescore -= sts[n - k].on;
            candidatescore += sts[n - k].manual;
        }
        if (cascade < candidatescore) {
            cascade = candidatescore;
        }

    }
    auto res = Stats{ .manual = manual, .cascade = cascade, .on = on };
    // printStats(res, p);
    return res;
}

int solve(const std::vector<Node>& parents, int k) {
    int rootIndex = parents.size() - 1;
    auto s = solve_rec(rootIndex, parents, k);
    return s.cascade - 1;
}

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int solveTest() {
    int n = readInt();
    int k = readInt() - 1;
    std::vector<Node> parents(n);
    for (int i = 0; i < n - 1; ++i) {
        int p = readInt() - 1;
        parents[p].child.push_back(i);
    }
    return solve(parents, k);
}

int main() {
    int t = readInt();
    for (int i = 0; i < t; ++i) {
        std::cout << solveTest() << std::endl;
    }
    return 0;
}
