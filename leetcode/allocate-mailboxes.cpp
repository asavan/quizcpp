// https://github.com/doocs/leetcode/blob/main/solution/1400-1499/1478.Allocate%20Mailboxes/README_EN.md
#include <algorithm>
#include <vector>

class Solution {
  public:
    int minDistance(std::vector<int>& houses, int k) {
        int n = houses.size();
        auto g = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                g[i][j] = g[i + 1][j - 1] + houses[j] - houses[i];
            }
        }
        const int inf = 1 << 30;
        auto f = std::vector<std::vector<int>>(n, std::vector<int>(k + 1, inf));
        for (int i = 0; i < n; ++i) {
            f[i][1] = g[0][i];
            for (int j = 2; j <= k && j <= i + 1; ++j) {
                for (int p = 0; p < i; ++p) {
                    f[i][j] = std::min(f[i][j], f[p][j - 1] + g[p + 1][i]);
                }
            }
        }
        return f[n - 1][k];
    }
};
