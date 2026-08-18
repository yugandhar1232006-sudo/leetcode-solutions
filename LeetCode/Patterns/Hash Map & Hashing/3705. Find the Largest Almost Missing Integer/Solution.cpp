class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = -1;

        for (int x : nums) {
            int count = 0;

            for (int i = 0; i + k <= n; i++) {
                for (int j = i; j < i + k; j++) {
                    if (nums[j] == x) {
                        count++;
                        break;
                    }
                }
            }

            if (count == 1)
                ans = max(ans, x);
        }

        return ans;
    }
};