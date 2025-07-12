#include <iostream>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int main() {
    int a = readInt();
    int b = readInt();
    std::cout << a + b << std::endl;
}
