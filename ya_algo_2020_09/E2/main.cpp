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

Stats solve_rec(int p, const std::vector<Node> &parents, int k);

std::vector<Stats> makeStats(int p, const std::vector<Node> &parents, int k) {
    const Node &node = parents[p];
    std::vector<Stats> sts;
    sts.reserve(node.child.size());
    for (int ch : node.child) {
        sts.push_back(solve_rec(ch, parents, k));
    }
    return sts;
}

int calcManual(const std::vector<Stats> &sts) {
    int manual = 1;
    int n = sts.size();
    for (const auto &s : sts) {
        manual += s.manual;
    }
    return manual;
}

int calcOn(const std::vector<Stats> &sts, int criticalIndex) {
    int on = 0;
    for (size_t i = 0; i < sts.size(); ++i) {
        if (i < criticalIndex) {
            on += sts[i].on;
        } else {
            on += sts[i].manual;
        }
    }
    return on;
}

int calcCascade(const std::vector<Stats> &sts, int criticalIndex, int on) {
    int prevCriticalIndex = criticalIndex - 1;
    const Stats& subsCand = sts[prevCriticalIndex];
    int cascade = 0;
    for (int i = 0; i < sts.size(); ++i) {
        const auto &s = sts[i];
        int candidatescore = 1 + on + s.cascade;
        if (i < criticalIndex) {
            candidatescore -= s.on;
        } else {
            candidatescore -= s.manual;
            candidatescore -= subsCand.on;
            candidatescore += subsCand.manual;
        }
        if (cascade < candidatescore) {
            cascade = candidatescore;
        }
    }
    return cascade;
}

Stats solve_rec(int p, const std::vector<Node> &parents, int k) {
    std::vector<Stats> sts = makeStats(p, parents, k);
    int manual = calcManual(sts);
    if (sts.size() < k) {
        return Stats{.manual = manual, .cascade = manual, .on = manual - 1};
    }

    std::sort(sts.begin(), sts.end(), [](const auto &l, const auto &r) {
        return (l.manual - l.on) < (r.manual - r.on);
    });
    /*
        std::nth_element(sts.begin(), sts.end() - k + 1, sts.end(),
                         [](const auto &l, const auto &r) {
                             return (l.manual - l.on) < (r.manual - r.on);
                         });

        std::nth_element(sts.begin(), sts.end() - k, sts.end() - k + 1,
                         [](const auto &l, const auto &r) {
                             return (l.manual - l.on) < (r.manual - r.on);
                         });
    */
    int criticalIndex = sts.size() + 1 - k;
    int on = calcOn(sts, criticalIndex);
    int cascade = calcCascade(sts, criticalIndex, on);
    return Stats{.manual = manual, .cascade = cascade, .on = on};
}

int solve(const std::vector<Node> &parents, int k) {
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

}  // namespace

int main() {
    int t = readInt();
    for (int i = 0; i < t; ++i) {
        std::cout << solveTest() << std::endl;
    }
    return 0;
}
