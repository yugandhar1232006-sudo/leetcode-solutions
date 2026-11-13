class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 18;

        vector<int> nxt(n, n), st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i])
                st.pop_back();

            if (!st.empty())
                nxt[i] = st.back();

            st.push_back(i);
        }

        vector<vector<int>> jump(LOG, vector<int>(n + 1, n));
        vector<vector<long long>> sum(LOG, vector<long long>(n + 1, 0));

        for (int i = 0; i < n; i++) {
            jump[0][i] = nxt[i];
            sum[0][i] = 1LL * (nxt[i] - i) * nums[i];
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                int mid = jump[j - 1][i];
                jump[j][i] = jump[j - 1][mid];
                sum[j][i] = sum[j - 1][i] + sum[j - 1][mid];
            }
        }

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++)
            pref[i + 1] = pref[i] + nums[i];

        auto getCost = [&](int l, int r) -> long long {
            int cur = l;
            long long total = 0;

            for (int j = LOG - 1; j >= 0; j--) {
                if (jump[j][cur] <= r + 1) {
                    total += sum[j][cur];
                    cur = jump[j][cur];
                }
            }

            if (cur <= r)
                total += 1LL * (r - cur + 1) * nums[cur];

            return total - (pref[r + 1] - pref[l]);
        };

        long long ans = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {
            while (left <= right && getCost(left, right) > k)
                left++;

            ans += right - left + 1;
        }

        return ans;
    }
};