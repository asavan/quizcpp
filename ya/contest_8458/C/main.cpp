#include <string>
#include <iostream>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

std::string readStr() {
    std::string x;
    std::cin >> x;
    return x;
}

int main() {
    int n = readInt();
	if (n <= 0) {
		return 0;
	}
	auto prev = readStr();
    for (int i = 1; i < n; i++) {
        auto curr = readStr();
		if (prev != curr) {
			std::cout << prev << std::endl;
			prev = curr;
		}
    }
	std::cout << prev << std::endl;
    return 0;
}
