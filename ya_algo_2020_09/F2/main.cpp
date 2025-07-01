// https://contest.yandex.ru/contest/19811/problems/F/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace {

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int solve(int n, int m) {
    if (n > m) {
        return solve(m, n);
    }
    if (n == 1) {
        if ((m - 1) % 3 == 0) {
            return (m - 1) / 3 + 1;
        }
        return m;
    }
    if (n == 2) {
        if (m == 2 || m == 4) {
            return m*n;
        }
        if (m == 3) {
            return 2;
        }
        if (m == 6) {
            return 4;
        }
        if (m == 5) {
            return 3;
        }
        return solve(n, m - 2) + 1;
    }
    if (n == 3) {
        if (m == 3) {
            return 3;
        }
        if (m == 4) {
            return 4;
        }
        if (m == 5) {
            return 4;
        }
        if (m == 6) {
            return 6;
        }
        return solve(n, m - 4) + 3;
    }
    if (n == 4) {
        if (m == 4) {
            return 4;
        }
        if (m == 5) {
            return 6;
        }
        if (m == 6) {
            return 7;
        }
        if (m == 7) {
            return 7;
        }
        return solve(n, m - 4) + 4;
    }
    if (n == 5) {
        if (m == 5) {
            return 7;
        }
    }
    if (n == 6) {
        if (m == 6) {
            return 10;
        }
    }
    if (n == 7) {
        if (m == 7) {
            return 6 * 2;
        }
        if (m == 8) {
            return 7 * 2;
        }
    }
    int res = n * m;
    return res;
}

} // namespace

void test1() {
    assert(solve(1, 1) == 1);
    assert(solve(1, 2) == 2);
    assert(solve(1, 3) == 3);
    assert(solve(1, 4) == 2);
    assert(solve(1, 5) == 5);
    assert(solve(1, 7) == 3);
    assert(solve(2, 1) == 2);
    assert(solve(3, 1) == 3);
    assert(solve(4, 1) == 2);
    assert(solve(5, 1) == 5);
    assert(solve(7, 1) == 3);

    assert(solve(1, 100) == 34);
}

void test2() {
    assert(solve(2, 2) == 4);
    assert(solve(2, 3) == 2);
    assert(solve(2, 4) == 8);
    assert(solve(2, 5) == 3);
    assert(solve(2, 6) == 4);
    assert(solve(2, 7) == 4);
    assert(solve(2, 8) == 5);
    assert(solve(2, 11) == 6);
    assert(solve(2, 12) == 7);
    assert(solve(2, 10) == 6);
    assert(solve(2, 100) == 51);
}

void test3() {
    assert(solve(3, 3) == 3);
    assert(solve(3, 4) == 4);
    assert(solve(3, 5) == 4);
    assert(solve(3, 6) == 6);
    assert(solve(3, 7) == 6);
    assert(solve(3, 15) == 12);
    assert(solve(3, 16) == 13);
}

void test4() {
    assert(solve(4, 4) == 4);
    assert(solve(4, 5) == 6);
    assert(solve(4, 7) == 7);
    assert(solve(4, 8) == 8);
    assert(solve(4, 9) == 10);
    assert(solve(4, 10) == 11);
}

void test5() {
    assert(solve(5, 5) == 7);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}

int main1() {
    int n = readInt();
    int m = readInt();
    std::cout << solve(n, m) << std::endl;
    return 0;
}
