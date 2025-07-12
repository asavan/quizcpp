#include <iostream>
#include <numeric>
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

void print(const std::vector<double>& result) {
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

std::vector<double> MovingAverage(const std::vector<int>& arr, int K) {
    std::vector<double> result;
    result.reserve(arr.size() + 1 - K);
    long long current_sum = std::accumulate(arr.begin(), arr.begin() + K, 0);
    result.push_back((double)current_sum / K);
    for (size_t i = 0; i < arr.size() - K; ++i) {
        current_sum -= arr[i];
        current_sum += arr[i + K];
        double current_avg = (double)current_sum / K;
        result.push_back(current_avg);
    }
    return result;
}

int main() {
    int n = readInt();
    auto arr = readVec(n);
    int windowSize = readInt();
    print(MovingAverage(arr, windowSize));
    return 0;
}
