// https://contest.yandex.ru/contest/19811/problems/E/

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
struct Node {
    std::vector<int> child;
};

struct Stats {
    int manual;
    int cascade;
    int on;
};

Stats solve_rec(int p, const std::vector<Node> &parents, int k) {
    const Node &node = parents[p];
    std::vector<Stats> sts;
    sts.reserve(node.child.size());
    for (int ch : node.child) {
        sts.push_back(solve_rec(ch, parents, k));
    }
    int manual = 1;
    int n = sts.size();
    for (const auto &s : sts) {
        manual += s.manual;
    }

    if (k > n) {
        return Stats{.manual = manual, .cascade = manual, .on = manual - 1};
    }

    std::sort(sts.begin(), sts.end(), [](const auto &l, const auto &r) {
        return (l.manual - l.on) < (r.manual - r.on);
    });
    /*
    std::nth_element(sts.begin(), sts.end() - k + 1, sts.end(), [](const auto&
    l, const auto& r) { return (l.manual - l.on) < (r.manual - r.on);
    });

    std::nth_element(sts.begin(), sts.end() - k, sts.end() - k + 1, [](const
    auto& l, const auto& r) { return (l.manual - l.on) < (r.manual - r.on);
        });
    */
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
        const auto &s = sts[i];
        int candidatescore = 1 + on + s.cascade;
        if (i < n - k + 1) {
            candidatescore -= s.on;
        } else {
            candidatescore -= s.manual;
            candidatescore -= sts[n - k].on;
            candidatescore += sts[n - k].manual;
        }
        if (cascade < candidatescore) {
            cascade = candidatescore;
        }
    }
    return Stats{.manual = manual, .cascade = cascade, .on = on};
}

int solve(const std::vector<Node> &parents, int k) {
    int rootIndex = parents.size() - 1;
    Stats s = solve_rec(rootIndex, parents, k);
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

}  // namespace

int main() {
    int t = readInt();
    for (int i = 0; i < t; ++i) {
        std::cout << solveTest() << std::endl;
    }
    return 0;
}
