#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int bfs(const std::vector<std::pair<int, int>>& cities, int k, int s, int t) {
    std::queue<int> q;
    std::vector<int> visited(cities.size(), -1);
    q.push(s);
    visited[s] = 0;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        if (c == t) {
            return visited[c];
        }
        const auto& cc = cities[c];
        for (int j = 0; j < cities.size(); ++j) {
            if (c != j && visited[j] < 0) {
                const auto& ccc = cities[j];
                long long len = (long long)abs(cc.first - ccc.first) + (long long)abs(cc.second - ccc.second);
                if (len > k) {
                    continue;
                }
                q.push(j);
                visited[j] = visited[c] + 1;
            }
        }
    }
    return -1;
}

int main() {
    int n = readInt();
    std::vector<std::pair<int, int>> cities;
    for (int i = 0; i < n; ++i) {
        int x = readInt();
        int y = readInt();
        cities.emplace_back(x, y);
    }
    int k = readInt();
    int s = readInt() - 1;
    int t = readInt() - 1;
    std::cout << bfs(cities, k, s, t) << std::endl;
    return 0;
}
