#include <algorithm>
#include <vector>

// using namespace std;

class Solution {
  public:
    int leastInterval(std::vector<char>& tasks, int n) {
        size_t counts[26] = {};
        for (auto task : tasks) {
            ++counts[task - 'A'];
        }
        size_t maxVal = *std::max_element(std::begin(counts), std::end(counts));
        size_t maxCount = std::count(std::begin(counts), std::end(counts), maxVal);
        return std::max((maxVal - 1) * (n + 1) + maxCount, tasks.size());
    }
};
