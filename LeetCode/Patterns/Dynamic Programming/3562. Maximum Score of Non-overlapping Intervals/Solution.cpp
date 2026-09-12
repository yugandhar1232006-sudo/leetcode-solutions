class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];
            return x[0] < y[0];
        });

        vector<long long> ends(n);
        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

        const long long NEG = -(1LL << 60);

        vector<vector<long long>> dp(n + 1, vector<long long>(5, NEG));
        vector<vector<vector<int>>> path(n + 1, vector<vector<int>>(5));

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int k = 0; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
                path[i][k] = path[i - 1][k];
            }

            long long l = a[i - 1][0];
            long long w = a[i - 1][2];
            int idx = (int)a[i - 1][3];

            int p = lower_bound(ends.begin(), ends.begin() + i - 1, l) - ends.begin();

            for (int k = 1; k <= 4; k++) {
                if (dp[p][k - 1] == NEG)
                    continue;

                long long score = dp[p][k - 1] + w;

                vector<int> candidate = path[p][k - 1];
                candidate.push_back(idx);
                sort(candidate.begin(), candidate.end());

                if (score > dp[i][k] ||
                    (score == dp[i][k] && candidate < path[i][k])) {
                    dp[i][k] = score;
                    path[i][k] = candidate;
                }
            }
        }

        vector<int> ans;

        for (int k = 0; k <= 4; k++) {
            if (dp[n][k] > dp[n][ans.size()] ||
                (dp[n][k] == dp[n][ans.size()] && path[n][k] < ans)) {
                ans = path[n][k];
            }
        }

        return ans;
    }
};