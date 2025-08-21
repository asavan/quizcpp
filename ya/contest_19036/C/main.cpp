// problems/C/

#include <iostream>
#include <vector>

int solve(const std::vector<int>& cards, int k) {
    int V = 0;
    int P = 0;
    for (int card : cards) {
        bool mod3 = card % 3 == 0;
        bool mod5 = card % 5 == 0;
        if (mod3 == mod5) {
            continue;
        } else if (mod3) {
            ++P;
        } else {
            ++V;
        }
        if (V == k) {
            return 1;
        }
        if (P == k) {
            return -1;
        }
    }
    return V - P;
}

void print(int res, std::ostream& out) {
    if (res > 0) {
        out << "Vasya";
    }
    else if (res < 0) {
        out << "Petya";
    }
    else {
        out << "Draw";
    }
    out << std::endl;
}


void func(std::istream& f, std::ostream& out) {
    int n, k;
    f >> k;
    f >> n;
    std::vector<int> cards(n);

    for (int i = 0; i < n; ++i) {
        f >> cards[i];
    }

    int res = solve(cards, k);
    print(res, out);
}

int main() {
    //std::ifstream f("input.txt");
    //std::ofstream out("output.txt");
    // func(f, out);
    func(std::cin, std::cout);
    return 0;
}
