// problems/B/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <limits>

int64_t count(const std::unordered_map<int, int>& map, int64_t T, int X) {
    int64_t c = 0;
    for (const auto& ti : map) {
        c += std::max((T - ti.second + X) / X, (int64_t)0);
    }
    return c;
}

void func(std::istream& f, std::ostream& out) {
    int n, x, k;
    f >> n;
    f >> x;
    f >> k;

    std::unordered_map<int, int> m_unique;
    for (int i = 0; i < n; ++i) {
        int t;
        f >> t;
        int key = t % x;
        auto it = m_unique.find(key);
        if (it != m_unique.end()) {
            it->second = std::min(it->second, t);
        }
        else {
            m_unique[key] = t;
        }
    }

    int64_t left = 0;
    int64_t right = std::numeric_limits<int64_t>::max()/2;
    while (right > left) {
        int64_t mid = (right + left) / 2;
        int64_t c = count(m_unique, mid, x);
        if (c < k) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    out << left << std::endl;
}

int main() {
    func(std::cin, std::cout);
    return 0;
}
