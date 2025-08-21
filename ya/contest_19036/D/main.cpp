// problems/D/

#include <iostream>
#include <vector>
#include <stdexcept>


int readInt() {
    int x;
    std::cin >> x;
    return x;
}

void print(int res) {
    std::cout << "! " << res << std::endl;
}

void bisect() {
    int n = readInt();
    int lb = 1;
    int ub = n;
    while (ub != lb) {
        int curr = (lb + ub) / 2;
        std::cout << curr << std::endl;
        int res = readInt();
        if (res == 1) {
            lb = curr + 1;
        } else if (res == 0) {
            ub = curr;
        } else {
            throw std::runtime_error("bad responce");
        }

    }
    print(ub);
}

int main() {
    bisect();
    return 0;
}
