#include <vector>
class Solution {
public:
    void rotate(std::vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        reverse(nums, 0, n);
        reverse(nums, 0, k);
        reverse(nums, k, n);
    }

    void reverse(std::vector<int>& nums, int begin, int end) {
        for (int i = 0; i < (end-begin)/2; ++i) {
            int tmp = nums[i+begin];
            nums[i+begin] = nums[end-i-1];
            nums[end-i-1] = tmp;
        }
    }
};
