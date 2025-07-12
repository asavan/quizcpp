#include <iostream>
#include <vector>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

std::vector<int> readVec(int n) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
    }
    return a;
}

void print(const std::vector<int>& result) {
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Zip(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> c;
    c.reserve(a.size() + b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }
    return c;
}

int main() {
    int n = readInt();
    auto a = readVec(n);
    auto b = readVec(n);
    print(Zip(a, b));
    return 0;
}
