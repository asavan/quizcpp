#include <array>
#include <iostream>
#include <string>

std::string readStr() {
    std::string x;
    std::cin >> x;
    return x;
}

std::array<int, 26> calcHash(const std::string& s) {
    std::array<int, 26> array{};
    for (char c : s) {
        ++array[c - 'a'];
    }
    return array;
}

int main() {
    auto arr1 = calcHash(readStr());
    auto arr2 = calcHash(readStr());
    bool areEqual = arr1 == arr2;
    std::cout << (int)areEqual << std::endl;
    return 0;
}
