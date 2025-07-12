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

std::vector<int> TwoSum(const std::vector<int>& arr, int targetSum) {
    for (size_t i = 0, j = arr.size() - 1; i < j;) {
        int left = arr[i];
        int right = arr[j];
        if ((left + right) == targetSum) {
            return {left, right};
        }
        if ((left + right) < targetSum) {
            ++i;
        } else {
            --j;
        }
    }
    return {};
}

void print(const std::vector<int>& result) {
    if (result.size() != 2) {
        std::cout << "None" << std::endl;
    } else {
        std::cout << result[0] << " " << result[1] << std::endl;
    }
}

int main() {
    int n = readInt();
    auto sortedArr = readVec(n);
	int targetSum = readInt();
    print(TwoSum(sortedArr, targetSum));
    return 0;
}
