#include <algorithm>
#include <iostream>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int main() {
    int n = readInt();
    int maxLen = 0;
    int currLen = 0;
    for (int i = 0; i < n; i++) {
        int curr = readInt();
        if (curr == 1) {
            ++currLen;
        } else {
            maxLen = std::max(currLen, maxLen);
            currLen = 0;
        }
    }
    maxLen = std::max(currLen, maxLen);
    std::cout << maxLen << std::endl;
    return 0;
}
