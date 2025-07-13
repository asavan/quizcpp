// https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/
#include <vector>

constexpr int MODULO = (int) 1e9 + 7;
using namespace std;

class PathsInMatrix {

    vector<int> newArrShifted(const vector<int>& prev, int diff) {
        int k = prev.size();
        vector<int> cur(k);
        for (int i = 0; i < k; ++i) {
            cur[(i + diff) % k] = prev[i];
        }
        return cur;
    }

    vector<int> mergeArr(const vector<int>& l1, const vector<int>& l2) {
        int k = l1.size();
        vector<int> cur(k);
        for (int i = 0; i < k; ++i) {
            cur[i] = (l1[i] + l2[i]) % MODULO;
        }
        return cur;
    }

    vector<vector<int>> fillLine(const vector<vector<int>>& levelPrev, const vector<int>& grid_level) {
        int n = grid_level.size();
        vector<vector<int>> levelCur;
        levelCur.reserve(n);
        levelCur.push_back(newArrShifted(levelPrev[0], grid_level[0]));
        for (int in = 1; in < n; ++in) {
            int diff = grid_level[in];
            auto tmp1 = newArrShifted(levelCur[in - 1], diff);
            auto tmp2 = newArrShifted(levelPrev[in], diff);
            levelCur.push_back(mergeArr(tmp1, tmp2));
        }
        return levelCur;
    }

public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> level = vector<vector<int>>(n, vector<int>(k));
        level[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            level = fillLine(level, grid[i]);
        }
        return level[n - 1][0];
    }
};
