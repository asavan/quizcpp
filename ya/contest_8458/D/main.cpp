#include <iostream>
#include <string>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

void pss(std::string s, int l, int r, int pairs) {
    if (l == pairs && r == pairs) {
        std::cout << s << std::endl;
        return;
    }
    if (l < pairs) {
        pss(s + '(', l + 1, r, pairs);
    }
    if (r < l) {
        pss(s + ')', l, r + 1, pairs);
    }
}

int main() {
    int n = readInt();
    pss("", 0, 0, n);
    return 0;
}
